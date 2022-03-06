#ifndef SEARCH_ENGINE_CONFIGURATION_H
#define SEARCH_ENGINE_CONFIGURATION_H

#include <forward_list>
#include <iostream>
#include <fstream>

class Configuration {

private:
    static Configuration* instance;
    static int instanceCounter;

    std::forward_list<std::string> startURLs {};
    std::string dbLogin{};
    std::string dbPassword{};
    std::string dbHost{};
    std::string dbName{};
    bool configDataIsLoaded {false};

    Configuration();
    void readConfigurationFile();
    void parseUrlToVector(std::string sourceText);
    void printUrlVector() const;
    std::string getTag(std::string sourceText, std::string tag);

public:
    Configuration(Configuration &other) = delete;
    void operator=(const Configuration &) = delete;

    static Configuration* getInstance();
    void printConfigData();
    std::forward_list<std::string>* getStartUrlSet();
};

#endif //SEARCH_ENGINE_CONFIGURATION_H