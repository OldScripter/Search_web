#include "../include/httptools.h"

std::string getHTML(std::string url, std::string status_code)
{
    if (url.find("https://") != std::string::npos)
    {
        auto httpsPosition = url.find("https://");
        url.erase(httpsPosition + 4, 1);
    }
    cpr::Response response = cpr::Get(cpr::Url(url));
    status_code = response.status_code;

    if (response.status_code == 200)
    {
        return response.text;
    }
    else
    {
        std::cerr << "Error " << response.status_code << " is ocured.\n";
        return "";
    }
}

std::string cleantext(GumboNode* node) 
{
    if (node->type == GUMBO_NODE_TEXT) 
    {
        return std::string(node->v.text.text);
    } 
    else if (node->type == GUMBO_NODE_ELEMENT &&
            node->v.element.tag != GUMBO_TAG_SCRIPT &&
            node->v.element.tag != GUMBO_TAG_STYLE) 
    {
        std::string contents = "";
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) 
        {
            const std::string text = cleantext((GumboNode*) children->data[i]);
            if (i != 0 && !text.empty()) 
            {
                contents.append(" ");
            }  
        contents.append(text);
        }
        return contents;
    } 
    else
    {
        return "";
    }
}