#include "stand_manager.hpp"

#include <boost/bind/bind.hpp>

using namespace boost::placeholders;
using namespace Message;

StandManager::StandManager(std::initializer_list<WorkerBase *> l) : workers(l), bs(8080, sizeof(ClientPacket))
{
    auto first = bs.create(sizeof(ClientPacket), this);

    bs.acc->async_accept(first->sock, boost::bind(&ByteStormBoost::handle_accept, &bs, first, _1, this));
    for (auto worker : workers)
    {
        worker->setBuffer(&buffer);
        worker->start();
    }
}

void StandManager::append(WorkerBase *worker)
{
    if (!worker)
    {
        return;
    }
    workers.push_back(worker);
}

void StandManager::onSingleShotCompleted(const float *mean)
{
    std::lock_guard<std::mutex> lock(interfaceMutex);

    if (!mean)
    {
        std::cout << "[err] | StandManager: Error occured on I2C" << std::endl;
        this->sendErrorMessage(Message::Status::I2CError);
        return;
    }

    packet.common.instance = Instance::ADS;
    std::cout << "[info] | StandManager: single shot completed " << std::endl;

    auto pPacket = std::make_unique<std::uint8_t[]>(sizeof(ServerPacket));
    std::memcpy(pPacket.get(), &packet, sizeof(ServerPacket));

    buffer.get(&packet.load);

    this->ptr->send(pPacket, sizeof(ServerPacket));
}

void StandManager::onAngleSet(const Message::Instance &instance)
{
    static int counter = 0;
    if (instance == Instance::Error)
    {
        this->sendErrorMessage(Message::Status::StepperError);
        return;
    }
    std::cout << "[info] | StandManager: Angle is set on " << instance << std::endl;

    std::lock_guard<std::mutex> lock(interfaceMutex);

    buffer.get(&packet.load);
    packet.common.instance = instance;
    packet.load.query = Query::StepperCompleted;

    auto pPacket = std::make_unique<std::uint8_t[]>(sizeof(ServerPacket));
    std::memcpy(pPacket.get(), &packet, sizeof(ServerPacket));

    this->ptr->send(pPacket, sizeof(ServerPacket));
}

void StandManager::processCommand(Commands::Common command)
{
    std::cout << "[info] | StandManager: Received command - " << command << std::endl;

    switch (command)
    {
    case Commands::Common::GetData:
    {
        std::lock_guard<std::mutex> lock(interfaceMutex);
        buffer.get(&packet.load);

        packet.common.instance = Instance::Common;
        packet.load.query = Query::ResponseDataRequest;

        auto pPacket = std::make_unique<std::uint8_t[]>(sizeof(ServerPacket));
        std::memcpy(pPacket.get(), &packet, sizeof(ServerPacket));

        this->ptr->send(pPacket, sizeof(ServerPacket));

        break;
    }

    default:
        break;
    }
}

void StandManager::sendErrorMessage(Message::Status err)
{
    if (!ptr->isConnected())
    {
        return;
    }

    std::cout << "\n[err] | StandManager: sending error message with code: " << static_cast<int>(err) << std::endl;

    Message::ServerPacket errorPacket;
    errorPacket.common.instance = Instance::Error;
    errorPacket.common.err = err;

    auto pPacket = std::make_unique<std::uint8_t[]>(sizeof(ServerPacket));
    std::memcpy(pPacket.get(), &errorPacket, sizeof(ServerPacket));
    std::memset(pPacket.get() + sizeof(Common), 1, sizeof(ServerData));
    this->ptr->send(pPacket, sizeof(ServerPacket));
}

void StandManager::process(std::unique_ptr<uint8_t[]> &p, const size_t size)
{
    const uint8_t *data = p.release();
    for (size_t received = 0; received <= size; received += sizeof(ClientPacket))
    {
        auto newPacket = reinterpret_cast<const ClientPacket *>(data + received);
        auto instance = newPacket->common.instance;

        if (instance == Instance::Common)
        {
            this->processCommand(newPacket->load.command.commonCommand);
            return;
        }

        for (auto worker : workers)
        {
            if (!worker->at(instance))
            {
                continue;
            }
            auto payload = std::make_unique<ClientData>(newPacket->load);
            worker->handle(payload);
            return;
        }
    }
}
