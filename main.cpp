#include <iostream>
#include "include/httptools.h"
#include <vector>

int main()
{
    std::cout << "Search engine 1.0.1 by oldscripter\n";

    std::string requestStatusCode {""};
    std::string html = getHTML("https://httpbin.org/html", requestStatusCode);


    std::cout << "response status code -\t" << requestStatusCode << "\n";
    std::cout << html << "\n";

    std::cout << "HTML after parsing:\n";
    std::string cleanedHtml{""};
    GumboOutput* output = gumbo_parse(html.c_str());
    cleanedHtml += cleantext(output->root) + " "; //may be split heml into words right here?
    //Need to delete all symbols except letters.
    gumbo_destroy_output(&kGumboDefaultOptions, output);


    //split in words:
    
    std::vector<std::string> words;
    std::string word{""};
    for (auto s : cleanedHtml)
    {
        if (s == ' ')
        {
            if (word != "")
            {
                words.push_back(word);
            }
            word = "";
        }
        else if (   (s >= '0' && s <= '9') || 
                    (s >= 'A' && s <= 'Z') ||
                    (s >= 'a' && s <= 'z') ||
                    (s >= 'А' && s <= 'Я') ||
                    (s >= 'а' && s <= 'я')
                )
        {
            // use normalize words here:
            // ...
            word += s;
        }

    }

    //printing vector:
    for (auto word : words)
    {
        std::cout << word << "\n";
    }



    return 0;
} 