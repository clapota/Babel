#ifndef BABEL_DATABASESERVICE_HPP
#define BABEL_DATABASESERVICE_HPP

class DataBaseService : public IService {
    public:
        std::string getName() override { return "DataBaseService"; }
        explicit DataBaseService() = default;
};

#endif //BABEL_DATABASESERVICE_HPP