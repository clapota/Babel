#ifndef BABEL_LOGSERVICE_HPP
#define BABEL_LOGSERVICE_HPP

#include <iostream>

class LogService : public IService {
    public:
        std::string getName() override { return "LogService"; }

        void writeHour(std::string message)
        {
            time_t now = time(nullptr);
            tm *ltm = localtime(&now);

            std::cout << "[" << 1 + ltm->tm_hour << ":";
            std::cout << 1 + ltm->tm_min << ":";
            std::cout << 1 + ltm->tm_sec << "] " << message << std::endl;
        }

        void writeError(std::string message)
        {
            std::string errorMessage = "[ERROR] ";
            errorMessage.append(message);

            writeHour(errorMessage);
        }

};

#endif //BABEL_LOGSERVICE_HPP
