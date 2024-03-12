#include "logger.h"

int main() {
    // Get the logger instance and initialize it
    Logger& logger = Logger::getInstance();
    logger.init(Logger::Lvl::Debug, true, true, "log.txt");

    // Log messages at different levels
    logger.log("This is an error message", Logger::Lvl::Error);
    logger.log("This is a warning message", Logger::Lvl::Warning);
    logger.log("This is an info message", Logger::Lvl::Info);
    logger.log("This is a debug message", Logger::Lvl::Debug);

    return 0;
}
