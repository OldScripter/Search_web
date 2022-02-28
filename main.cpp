#include <iostream>
#include "include/httptools.h"
#include <vector>
#include "snowball/include/libstemmer.h"

int main()
{
    HttpTools* httpTools = new HttpTools();
    std::cout << "Search engine 1.0.1 by oldscripter\n";

    //std::string requestStatusCode {""};
    std::string html = httpTools->getHTML("https://httpbin.org/html");

    std::cout   << "response status code -\t" 
                << httpTools->getLastResponseStatusCode() << "\n";

    std::cout << html << "\n";

    std::cout << "HTML after parsing:\n";
    std::string cleanedHtml{""};
    GumboOutput* output = gumbo_parse(html.c_str());
    cleanedHtml += httpTools->cleantext(output->root) + " "; //may be split heml into words right here?
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

    // stem (snowball):
    struct sb_stemmer* stemmer;
    stemmer = sb_stemmer_new("english", "UTF_8");
    std::string test = "going";
    sb_symbol* s = (sb_symbol*) malloc (test.length() * sizeof(sb_symbol));
    int i = 0;
    for (auto c: test)
    {
        c = tolower(c);
        s[i] = c;
        ++i;
    }

    const sb_symbol * stemmed = sb_stemmer_stem(stemmer, s, i);

    std::cout << stemmed << "\n";


    

    return 0;
} 