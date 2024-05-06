/**
 * @file steppers_worker.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 04.04.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef STEPPERS_WORKER_HPP_INCLUDED
#define STEPPERS_WORKER_HPP_INCLUDED

#include <atomic>
#include <boost/signals2.hpp>
#include <condition_variable>
#include <memory>
#include <queue>

#include "MotorRequests.h"
#include "worker_base.hpp"

using Request = std::pair<Message::ClientData, Message::Instance>;

class SteppersWorker : public WorkerBase
{
    std::string kDefaultIPAddress{"10.42.0.150"};
    std::string kDefaultGCodePattern{":7125/printer/gcode/script?script="};

public:
    SteppersWorker();
    ~SteppersWorker();

    void handle(std::unique_ptr<Message::ClientData> &payload) override;
    void get(std::shared_ptr<std::uint8_t[]> &p) const override;

    [[maybe_unused]] inline bool isAvailable() { return available; }

    [[maybe_unused]] void prestart() override;

private:
    MotorRequests requester;
    Message::Instance completed;
    std::queue<Request> q;
    std::atomic_bool available;
    std::condition_variable cv;

public:
    boost::signals2::signal<void(const Message::Instance &instance)> signal;

protected:
    void run() override;
};

#endif // STEPPERS_WORKER_HPP_INCLUDED
