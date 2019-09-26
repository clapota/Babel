//
// Created by abel on 26/09/2019.
//

#ifndef BABEL_AUDIOEXCEPTION_HPP
#define BABEL_AUDIOEXCEPTION_HPP

#include <exception>

class AudioException : public std::exception {
    public:
        explicit AudioException(const char *message);
        const char *what() const noexcept override;

    private:
        const char *message = nullptr;
};


#endif //BABEL_AUDIOEXCEPTION_HPP
