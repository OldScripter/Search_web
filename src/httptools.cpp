#include "../include/httptools.h"

std::string HttpTools::getHTML(std::string url, long status_code)
{
    if (url.find("https://") != std::string::npos)
    {
        auto httpsPosition = url.find("https://");
        url.erase(httpsPosition + 4, 1);
    }
    cpr::Response response = cpr::Get(cpr::Url(url));
    status_code = response.status_code;
    this->lastResponseStatusCode = response.status_code;

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

std::string HttpTools::getHTML(std::string url)
{
    if (url.find("https://") != std::string::npos)
    {
        auto httpsPosition = url.find("https://");
        url.erase(httpsPosition + 4, 1);
    }
    url.append("/html");
    cpr::Response response = cpr::Get(cpr::Url(url));

    this->lastResponseStatusCode = response.status_code;

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

std::string HttpTools::cleantext(GumboNode* node) 
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

std::string HttpTools::getCleanedText(std::string htmlResponse)
{
    std::string cleanedHtml{""};
    GumboOutput* output = gumbo_parse(htmlResponse.c_str());
    cleanedHtml += cleantext(output->root) + " ";
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    return cleanedHtml;
}

std::vector<std::string> HttpTools::getNormalisedWordsEng(std::string cleanedHtml)
{
    // init stemmer------------------------------
    struct sb_stemmer* stemmer_ENG = sb_stemmer_new("english", NULL);
    //Add russian stemmer.
    //-------------------------------------------
    std::vector<std::string> words;
    std::string word{""};
    for (auto s : cleanedHtml)
    {
        if (s == ' ')
        {
            if (word != "")
            {
                sb_symbol* s = (sb_symbol*) malloc (word.length() * sizeof(sb_symbol));
                int i = 0;
                for (auto c: word)
                {
                    c = tolower(c);
                    s[i] = c;
                    ++i;
                }

                const sb_symbol * stemmed_word  = sb_stemmer_stem(stemmer_ENG, s, i);
                
                word = "";
                for (int a = 0; a < sb_stemmer_length(stemmer_ENG); ++a)
                {
                    word += stemmed_word[a];
                }
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

    return words; 
}

void HttpTools::printVector(std::vector<std::string>& v)
{
    for (auto word : v)
    {
        std::cout << word << "\n";
    }
}