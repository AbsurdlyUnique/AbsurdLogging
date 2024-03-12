#include "logger.h"
#include <iostream>
#include <ctime>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::init(Lvl logLevel, bool enableDebug, bool logToFile, const std::string& filePath) {
    Clvl = logLevel;
    debugEnabled = enableDebug;
    toFile = logToFile;
    if (toFile && !filePath.empty()) {
        logFile.open(filePath, std::ofstream::out | std::ofstream::app);
        if (logFile.is_open()) {
            logFile << "[Logger] Logger initialized and logging to file: " << filePath << std::endl;
        }
    }
    // Generate the initialization message
    std::time_t result = std::time(nullptr);
    std::string timeStr = std::asctime(std::localtime(&result));
    // pop back just to delete the new line
    timeStr.pop_back();

    // output to the console
    std::string initMessage = "[" + timeStr + "] INFO: Logger initialized";
}

void Logger::log(const std::string& message, Lvl level) {
    if (level > Clvl) return;
    if (level == Lvl::Debug && !debugEnabled) return;

    std::time_t result = std::time(nullptr);
    std::string timeStr = std::asctime(std::localtime(&result));
    timeStr.pop_back(); // Remove newline

    std::string logMessage = "[" + timeStr + "] ";

    switch (level) {
        case Lvl::Error: logMessage += "ERROR: "; break;
        case Lvl::Warning: logMessage += "WARNING: "; break;
        case Lvl::Info: logMessage += "INFO: "; break;
        case Lvl::Debug: logMessage += "DEBUG: "; break;
        case Lvl::Fatal: logMessage += "FATAL: "; break;
        case Lvl::Emergency: logMessage += "EMERGENCY: "; break;
    }

    logMessage += message;

    // Always log to console.
    std::cout << logMessage << std::endl;

    // Additionally, log to file if enabled.
    if (toFile && logFile.is_open()) {
        logFile << logMessage << std::endl;
    }
}



Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
