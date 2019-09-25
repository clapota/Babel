#ifndef BABEL_SERVICELOCATOR_HPP
#define BABEL_SERVICELOCATOR_HPP

#include <iostream>
#include "LogService.hpp"

template <class T>
class ServiceLocator {
    static_assert(std::is_base_of<IService, T>::value, "T must inherit from IService");
    public:
        static T *getService()
        {
                if (_service == nullptr) {
                        _service = new T();
                }
                return _service;
        }

        ~ServiceLocator()
        {
                delete(_service);
        }
    private:
        static T *_service;
};

template <typename T>
T *ServiceLocator<T>::_service = nullptr;

#endif //BABEL_SERVICELOCATOR_HPP
