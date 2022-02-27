#pragma once

#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "../gumbo-parser/src/gumbo.h"

class HttpTools
{
    private:

    std::string lastResponseStatusCode {"n/a"};

    public:

    /**
     * @brief  Get the HTML code from URL
     * @param[in] url url for request
     * @param[out] status_code string for response status code writing
     * @return html code in string format
     **/
    std::string getHTML(std::string url, std::string status_code);

    /**
     * @brief Cleaning html response text from tags
     * 
     * @param[in] node pointer parent html node to start cleaning from  
     * @return std::string cleaned text 
     */
    std::string cleantext(GumboNode* node);

    /**
     * @brief Get the Last Response Status Code in string format
     * @return std::string status code or \"n/a\" if there were 
     * now responses
     */
    std::string getLastResponseStatusCode() const
    {
        return lastResponseStatusCode;
    }

};

