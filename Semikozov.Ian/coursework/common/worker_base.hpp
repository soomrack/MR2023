/**
 * @file worker_base.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 01.04.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef WORKER_BASE_HPP_INCLUDED
#define WORKER_BASE_HPP_INCLUDED

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <memory>
#include <mutex>
#include <thread>

#include "protocol.hpp"
#include "rt_data_buffer.hpp"

using ID = Message::Instance;

class WorkerBase
{
public:
    WorkerBase() = delete;
    WorkerBase(ID first, ID second = ID::None) : first(first), second(second) {}

    virtual ~WorkerBase()
    {
        if (!t) { return; }
        enable = false;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (t->joinable()) { t->join(); }
        delete t;
    }

    void start()
    {
        if (t) { return; }
        this->prestart();
        t = new std::thread(&WorkerBase::run, this);
        enable = true;
    }

    [[maybe_unused]] inline void resume()
    {
        m.unlock();
    }
    [[maybe_unused]] inline void stop()
    {
        m.lock();
    }
    [[maybe_unused]] inline bool started() __attribute__((warn_unused_result))
    {
        return enable;
    }
    [[maybe_unused]] virtual void prestart() = 0;

    virtual void handle(std::unique_ptr<Message::ClientData> &payload) = 0;
    virtual void get(std::shared_ptr<std::uint8_t[]> &p) const = 0;

    inline void setBuffer(RTDataBuffer *b)
    {
        buffer = b;
    }

    inline bool at(ID id)
    {
        if ((id == this->first) || (id == this->second)) 
        {
            lastID = id;
            return true;
        }
        return false;
    }

protected:
    Message::Instance lastID;
    RTDataBuffer *buffer;
    std::atomic_bool enable{ false };
    std::thread *t{ nullptr };
    mutable std::mutex m;

protected:
    virtual void run() = 0;

private:
    ID first, second;
};

#endif // WORKER_BASE_HPP_INCLUDED
