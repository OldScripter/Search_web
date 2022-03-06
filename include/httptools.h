#pragma once
#ifndef HTTP_TOOLS_H
#define HTTP_TOOLS_H

#include <iostream>
#include <string>
#include <vector>
#include <cpr/cpr.h>
#include "../gumbo-parser/src/gumbo.h"
#include "../snowball/include/libstemmer.h"

class HttpTools
{
    private:

    long int lastResponseStatusCode {0};

    /**
     * @brief Cleaning html response text from tags
     * 
     * @param[in] node pointer parent html node to start cleaning from  
     * @return std::string cleaned text 
     */
    std::string cleantext(GumboNode* node);

    public:

    /**
     * @brief  Get the HTML code from URL
     * @param[in] url url for request
     * @param[out] status_code string for response status code writing
     * @return html code in string format
     **/
    std::string getHTML(std::string url, long status_code);
    
    /**
     * @brief  Get the HTML code from URL
     * @param[in] url url for request
     * @return html code in string format
     **/
    std::string getHTML(std::string url);

    /**
     * @brief Get the Last Response Status Code in string format
     * @return long status code or \"n/a\" if there were 
     * now responses
     */
    long getLastResponseStatusCode() const
    {
        return lastResponseStatusCode;
    }

    /**
     * @brief Get the Cleaned Text from the Html response.
     * 
     * @param[in] htmlResponse source html response as text
     * @return std::string text without tags
     */
    std::string getCleanedText(std::string htmlResponse);

    /**
     * @brief Get the Normalised Words vector
     * 
     * @param[in] cleanedHtml Html response text without tags 
     * @return std::vector<std::string>* pointer to container for normalized words 
     */
    std::vector<std::string> getNormalisedWordsEng(std::string cleanedHtml);

    /**
     * @brief Print the vector of string values
     * 
     */
    void printVector(std::vector<std::string>& v);


};

#endif //HTTP_TOOLS_H