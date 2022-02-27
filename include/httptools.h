#pragma once

#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "../gumbo-parser/src/gumbo.h"

/**
 * @brief  Get the HTML code from URL.
 * @param[in] url url for request
 * @param[out] status_code string for response status code writing
 * @return html code in string format
 **/
std::string getHTML(std::string url, std::string status_code);


std::string cleantext(GumboNode* node);