#ifndef BABEL_LOGSERVICE_HPP
#define BABEL_LOGSERVICE_HPP

#include <string>
#include <iostream>

class LogService {
    public:
        void writeHour(std::string message) {
            time_t now = time(nullptr);
            tm *ltm = localtime(&now);

            std::cout << "[" << 1 + ltm->tm_hour << ":";
            std::cout << 1 + ltm->tm_min << ":";
            std::cout << 1 + ltm->tm_sec << "] " << message << std::endl;
        }
};

#endif //BABEL_LOGSERVICE_HPP
