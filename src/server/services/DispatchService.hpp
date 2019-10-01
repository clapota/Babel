#ifndef BABEL_DISPATCHSERVICE_HPP
#define BABEL_DISPATCHSERVICE_HPP

#include <boost/thread.hpp>
#include "services/IService.hpp"
#include "network/IConnection.hpp"
#include "queue/ConcurrentQueue.hpp"
#include "services/ServiceLocator.hpp"

struct DispatchData {
    /* packet */
    IConnection *connection;
    std::function<void(IConnection &)> func;
};

class DispatchService : public IService {
    public:
        DispatchService() : _thread() {
            _isRunning = true;
            _thread = boost::thread(&DispatchService::loop, this);
        }

        void loop() {
            auto log = ServiceLocator<LogService>::getService();

            while (_isRunning) {
                auto &data = _queue.waitAndPop();

                try { data.func(*(data.connection)); }
                catch (std::exception &ex) { log->writeError(ex.what()); }
            }
        }

        void enqueue(DispatchData &data) {
            _queue.push(data);
        }

        void stop() {
            _isRunning = false;
        }

        ~DispatchService() {
            try { _thread.join(); }
            catch ( const boost::thread_interrupted & ) { /* skip */}
        }
    private:
        bool _isRunning = false;
        ConcurrentQueue<DispatchData> _queue;
        boost::thread _thread;
};

#endif //BABEL_DISPATCHSERVICE_HPP
