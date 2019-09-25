#ifndef BABEL_ISERVICE_HPP
#define BABEL_ISERVICE_HPP

#include <string>

class IService {
    public:
        virtual std::string getName() = 0;
};

#endif //BABEL_ISERVICE_HPP
