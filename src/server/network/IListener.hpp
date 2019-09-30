#ifndef BABEL_INETWORKABSTRACTION_H
#define BABEL_INETWORKABSTRACTION_H

#define LISTENER_DEFAULT_PORT 4444

class IListener
{
    public:
        virtual void stop() = 0;
        virtual void accept() = 0;
};

#endif //BABEL_INETWORKABSTRACTION_H
