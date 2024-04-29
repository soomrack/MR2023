/**
 * @file stand_manager.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 03.04.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef STAND_MANAGER_HPP_INCLUDED
#define STAND_MANAGER_HPP_INCLUDED

#include "bytestorm.hpp"
#include "protocol.hpp"
#include "rt_data_buffer.hpp"
#include "worker_base.hpp"

using namespace ByteStorm;

class StandManager : public Processor
{
    static constexpr size_t kDefaultWorkerCount{3};

public:
    StandManager(std::initializer_list<WorkerBase *> l);

    void append(WorkerBase *worker);
    void process(std::unique_ptr<uint8_t[]> &p, const size_t size) override;

    // slots
public:
    void onSingleShotCompleted(const float *mean);
    void onAngleSet(const Message::Instance &instance);

private:
    void processCommand(Commands::Common command);
    void sendErrorMessage(Message::Status err);

public:
    ByteStormBoost bs;

private:
    std::mutex interfaceMutex;
    std::vector<WorkerBase *> workers;
    Message::ServerPacket packet;
    RTDataBuffer buffer;
}; // class StandManager

#endif // STAND_MANAGER_HPP_INCLUDED
