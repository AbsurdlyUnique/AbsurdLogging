#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
    enum class Lvl {
        Error,
        Warning,
        Info,
        Debug,
        Fatal,
        Emergency
    };

    static Logger& getInstance();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void init(Lvl logLevel = Lvl::Info, bool enableDebug = false, bool logToFile = false, const std::string& filepath = "");
    void log(const std::string& message, Lvl level);


private:
    Logger() = default;
    ~Logger();

    Lvl Clvl = Lvl::Info;
    bool debugEnabled = false;
    bool toFile = false;
    std::ofstream logFile;
};

#endif
