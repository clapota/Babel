#ifndef BABEL_SERVICELOCATOR_HPP
#define BABEL_SERVICELOCATOR_HPP

#include <iostream>
#include "LogService.hpp"

template <class T>
class ServiceLocator {
    public:
        static T *getService() { return _service; } const
        static void registerService(T &service)
        {
            _service = &service;

            auto logService = ServiceLocator<LogService>::getService();
            logService->writeHour("Service '" + std::string(typeid(service).name()) + "' registered");
        }

    private:
        static T *_service;
};

template <typename T>
T *ServiceLocator<T>::_service = nullptr;

#endif //BABEL_SERVICELOCATOR_HPP
