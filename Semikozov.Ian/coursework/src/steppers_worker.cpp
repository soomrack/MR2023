#include "steppers_worker.hpp"

SteppersWorker::SteppersWorker() : requester(kDefaultIPAddress, kDefaultGCodePattern), WorkerBase(ID::Azimuth, ID::Elevation) {}

SteppersWorker::~SteppersWorker() {}

void SteppersWorker::handle(std::unique_ptr<Message::ClientData> &payload)
{
    std::cout << "[info] | SteppersWorker: Received command - " << payload->command.stepperCommand << " on " << lastID
              << " with main payload " << payload->main[0] << " and " << payload->main[1] << " and common "
              << static_cast<int>(payload->common) << std::endl;
    std::cout << "[info] | SteppersWorker: Pushing command to fifo for " << lastID << std::endl;

    {
        std::unique_lock<std::mutex> lock(m);
        auto request = std::make_pair(*payload.release(), lastID);
        q.push(request);
    }

    cv.notify_one();
}

void SteppersWorker::get(std::shared_ptr<std::uint8_t[]> &p) const {}

[[maybe_unused]] void SteppersWorker::prestart()
{
    try
    {
        requester.StartSession();
    }
    catch (std::runtime_error err)
    {
        std::cerr << "[err] | SteppersWorker: Couldn't start session. Error message: " << err.what();
    }
}

void SteppersWorker::run()
{
    using namespace Message;
    using namespace Commands;

    while (enable)
    {
        if (q.empty())
        {
            continue;
        }

        Request request;

        {
            std::unique_lock<std::mutex> lock(m);
            // cv.wait(lock, [this] { return !q.empty(); });
            request = q.front();
            q.pop();
        }

        auto payload = request.first;
        auto stepper = request.second;

        try
        {
            switch (payload.command.stepperCommand)
            {
            case Stepper::DecreaseAngle:
            {
                if (stepper == Instance::Azimuth)
                {
                    requester.SetCommand(decrease_azimuth_val, payload.main[0]);
                }
                else
                {
                    requester.SetCommand(decrease_elevation_val, payload.main[0]);
                }
                break;
            }
            case Stepper::IncreaseAngle:
            {
                if (stepper == Instance::Azimuth)
                {
                    requester.SetCommand(increase_azimuth_val, payload.main[0]);
                }
                else
                {
                    requester.SetCommand(increase_elevation_val, payload.main[0]);
                }
                break;
            }
            case Stepper::SetAngle:
            {
                if (stepper == Instance::Azimuth)
                {
                    requester.SetCommand(set_azimuth_val, payload.main[0]);
                }
                else
                {
                    requester.SetCommand(set_elevation_val, payload.main[0]);
                }
                break;
            }
            case Stepper::SetAngles:
            {
                requester.GridCalibration(payload.main[0], payload.main[1]);
                break;
            }
            case Stepper::Park:
            {
                if (stepper == Instance::Azimuth)
                {
                    requester.SetCommand(zero_azimuth);
                }
                else if (stepper == Instance::Elevation)
                {
                    requester.SetCommand(zero_elevation);
                }
                else
                {
                    requester.SetCommand(zero_azimuth);
                    requester.SetCommand(zero_elevation);
                }
                break;
            }
            default:
                break;
            }
            signal(stepper);
        }
        catch (std::runtime_error err)
        {
            std::cerr << "[err] | SteppersWorker: Couldn't complete command. "
                         "Error message: "
                      << err.what();
            signal(Instance::Error);
        }
        float azimuth = requester.GetAzVal(), elevation = requester.GetElVal();

        this->buffer->setAzimuth(azimuth);
        this->buffer->setElevation(elevation);
    }
}
