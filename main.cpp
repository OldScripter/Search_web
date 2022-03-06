#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "include/httptools.h"
#include "include/configuraton.h"

std::mutex access_mutex;

void processUrl(std::string url)
{
    HttpTools* httpTools = new HttpTools();
    //std::string requestStatusCode {""};
    std::string html = httpTools->getHTML(url);
    std::cout   << "response status code -\t" 
                << httpTools->getLastResponseStatusCode() << "\n";
    //std::cout << html << "\n";
    std::string cleanedHtml = httpTools->getCleanedText(html);
    //split in words:
    std::vector<std::string> words = httpTools->getNormalisedWordsEng(cleanedHtml);
    //printing vector:
    //httpTools->printVector(words);
    //After insertion to SQL:
    //ToDo: place to SQL;
    words.clear();
}


int main()
{
    
    std::cout << "Search engine 1.0.1 by oldscripter\n";

    std::vector<std::thread> urlProcessingThreads;

    //Read configuration:
    Configuration::getInstance();
    
    //Start new thread"
    std::string url {""};
    std::forward_list<std::string> urls = *Configuration::getInstance()->getStartUrlSet();
    for (auto url : urls)
    {
        std::thread urlProcessing (processUrl, url);
        std::cout << urlProcessing.get_id() << ": thread is started.\n";
        access_mutex.lock();
        urlProcessingThreads.push_back(std::move(urlProcessing));
        std::cout << urlProcessing.get_id() << ": thread is pushed to threads list.\n";
        access_mutex.unlock();
    }

    access_mutex.lock();
    for (std::thread& t : urlProcessingThreads)
    {
        std::cout << t.get_id() << ": is finishing\n";
        if (t.joinable()) t.join();
    }
    access_mutex.unlock();

    return 0;
} 