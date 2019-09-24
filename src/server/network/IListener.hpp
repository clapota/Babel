#ifndef BABEL_INETWORKABSTRACTION_H
#define BABEL_INETWORKABSTRACTION_H

class IListener
{
    public:
        virtual void stop() = 0;
        virtual void accept() = 0;
};

#endif //BABEL_INETWORKABSTRACTION_H
