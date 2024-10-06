#ifndef CONSOLEHISTORYSAVER
#define CONSOLEHISTORYSAVER

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>

class ConsoleHistorySaver {
public:
    ConsoleHistorySaver(const std::string& filename) : stopThread(false), filename(filename) {
        originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(coutStream.rdbuf());
        
        savingThread = std::thread(&ConsoleHistorySaver::saveHistoryLoop, this);
    }

    ~ConsoleHistorySaver() {
        stopThread = true;
        if (savingThread.joinable()) {
            savingThread.join();
        }
        std::cout.rdbuf(originalCoutBuffer);
    }

private:
    std::stringstream coutStream; 
    std::mutex historyMutex;
    std::atomic<bool> stopThread;
    std::thread savingThread;
    std::string filename;
    std::streambuf* originalCoutBuffer;

    void saveHistoryLoop() {
        while (!stopThread) {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::lock_guard<std::mutex> lock(historyMutex);

            std::ofstream outFile(filename, std::ios::app); 
            if (outFile.is_open()) {
                outFile << coutStream.str();
                coutStream.str(""); 
                outFile.close();
            }
        }
    }
};

#endif // CONSOLEHISTORYSAVER