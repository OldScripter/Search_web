#include "../include/configuraton.h"
Configuration* Configuration::instance = nullptr;
int Configuration::instanceCounter = 0;

/**
 * @method Get the configuration instance (based on singleton pattern).
 * @return [out] Pointer to instance if it was already constructed, if not - makes the instance at first
 */
Configuration* Configuration::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Configuration();
        ++instanceCounter;
    }
    return instance;
}

/**
 * @method Read the configuration data from config.ini.
 */
void Configuration::readConfigurationFile()
{
    configDataIsLoaded = false;
    std::string buffer;
    std::string config_text;
    std::ifstream configReadStream;
    try
    {
        std::cout << "Reading configuration... ";
        configReadStream.open("..//config.ini");
        if (configReadStream.is_open())
            std::cout << "Ok\n";

        while (!configReadStream.eof() && configReadStream)
        {
            std::getline(configReadStream, buffer);
            config_text += buffer;
        }
        configReadStream.close();

        dbHost = getTag(config_text, "host");
        dbName = getTag(config_text, "name");
        dbLogin = getTag(config_text, "login");
        dbPassword = getTag(config_text, "password");
        parseUrlToVector(config_text);
        configDataIsLoaded = true;
        std::cout << "DONE\n";
    }
    catch (...)
    {
        std::cerr << "FAIL\n";
        configDataIsLoaded = false;
        dbHost = "";
        dbName = "";
        dbLogin = "";
        dbPassword = "";
        startURLs.clear();
    }
}

/**
 * @method Read the tag from string.
 * @param [in] sourceText const string to be read from
 * @param [in] tag const string to be looking for in sourceText
 * @return [out] result string
 */
std::string Configuration::getTag(const std::string sourceText, const std::string tag)
{
    auto dbTagStart = sourceText.find("<" + tag + ">") + tag.length() + 2;
    auto dbTagEnd = sourceText.find("</" + tag + ">");
    auto dbTagLength = dbTagEnd - dbTagStart;
    std::string result = sourceText.substr(dbTagStart, dbTagLength);
    return result;
}

/**
 * @method Parse source text with <url> tags and if found - push them into startURLsVector.
 * @param [in] sourceText Where to search for <url> tags
 */
void Configuration::parseUrlToVector(std::string sourceText)
{
    startURLs.clear();
    while (sourceText.find("<url>") != std::string::npos)
    {
        std::string url = getTag(sourceText, "url");
        startURLs.push_front(url);
        sourceText = sourceText.substr(sourceText.find("</url>") + 6);
    }
}

/**
 * @method Prints start Urls vector into console.
 */
void Configuration::printUrlVector() const
{
    if (startURLs.empty())
    {
        std::cerr << "No Urls in the vector.\n";
        return;
    }
    for (auto url : startURLs)
    {
        std::cout << " - " << url << "\n";
    }
}

/**
 * @method Prints the configuration data into console.
 */
void Configuration::printConfigData()
{
    if (configDataIsLoaded)
    {
        std::cout << "---------- Active configuration ----------\n";
        std::cout << "dbHost = " << dbHost << "\n";
        std::cout << "dbName = " << dbName << "\n";
        std::cout << "dbLogin = " << dbLogin << "\n";
        std::cout << "dbPassword = " << dbPassword << "\n";
        std::cout << "Start Urls:\n";
        printUrlVector();
        std::cout << "------------------------------------------\n";
    }
    else
    {
        std::cerr << "Configuration file was not loaded.\n";
    }
}

Configuration::Configuration()
{
    readConfigurationFile();
}

std::forward_list<std::string>* Configuration::getStartUrlSet()
{
    return &startURLs;
}