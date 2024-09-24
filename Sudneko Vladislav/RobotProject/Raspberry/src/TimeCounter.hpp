#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

class TimeCounter {
private:
    std::atomic<int> counter;
    std::atomic<bool> running;
    std::thread counterThread;

    void run() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            counter++;
        }
    }

public:
    TimeCounter() : counter(0), running(false) {}

    ~TimeCounter() {
        stop();
        if (counterThread.joinable()) {
            counterThread.join();
        }
    }

    void start() {
        if (!running) { 
            running = true;
            counterThread = std::thread(&TimeCounter::run, this);
        }
    }

    void stop() {
        running = false; 
        if (counterThread.joinable()) {
            counterThread.join();
        }
    }

    int getCounter() const {
        return counter.load();
    }

    void reset() {
        counter = 0;
    }
};