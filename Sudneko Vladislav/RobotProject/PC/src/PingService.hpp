#ifndef PINGSERVICE
#define PINGSERVICE

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdlib>
#include <sstream>

class PingService {
public:
    // Constructor accepts an IP address with port (e.g., "http://192.168.76.84:5000")
    PingService(const std::string& url)
        : stop_flag(false), ping_time("N/A") {
        ip_address = extractIpAddress(url);

        ping_thread = std::thread(&PingService::pingLoop, this);
    }

    ~PingService() {
        stop_flag = true;
        if (ping_thread.joinable()) {
            ping_thread.join();
        }
    }

    std::string getPingTime() {
        std::lock_guard<std::mutex> lock(ping_mutex);
        return ping_time;
    }

private:
    std::string ip_address;
    std::string ping_time;
    bool stop_flag;
    std::thread ping_thread;
    std::mutex ping_mutex;

    void pingLoop() {
        while (!stop_flag) {
            std::string command = "ping -c 1 -W 1 " + ip_address + " | grep 'time='";
            std::string result = executeCommand(command);

            std::string extracted_ping = parsePingTime(result);

            {
                std::lock_guard<std::mutex> lock(ping_mutex);
                ping_time = extracted_ping;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    std::string executeCommand(const std::string& command) {
        char buffer[128];
        std::string result = "";
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) return "Error";
        try {
            while (fgets(buffer, sizeof buffer, pipe) != nullptr) {
                result += buffer;
            }
        } catch (...) {
            pclose(pipe);
            return "Error";
        }
        pclose(pipe);
        return result;
    }

    std::string parsePingTime(const std::string& ping_output) {
        std::string time_label = "time=";
        std::size_t pos = ping_output.find(time_label);
        if (pos != std::string::npos) {
            std::size_t start = pos + time_label.length();
            std::size_t end = ping_output.find(" ms", start);
            if (end != std::string::npos) {
                return ping_output.substr(start, end - start) + " ms";
            }
        }
        return "Timeout";
    }

    std::string extractIpAddress(const std::string& url) {
        std::size_t start_pos = url.find("://");
        if (start_pos != std::string::npos) {
            start_pos += 3;
        } else {
            start_pos = 0; 
        }

        std::size_t colon_pos = url.find(':', start_pos);
        if (colon_pos != std::string::npos) {
            return url.substr(start_pos, colon_pos - start_pos);
        }

        return url.substr(start_pos);
    }
};

#endif // PINGSERVICE