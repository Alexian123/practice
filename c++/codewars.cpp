#include <iostream>
#include <string.h>

using std::string;

string encrypt(string text, int n) {;
    if (text.empty() || n <= 0)
        return text;

    string evens = "";
    string odds = "";
    for (size_t i = 0; i < n; ++i) {
        evens.clear();
        odds.clear();
        for (size_t j = 0; j < text.length(); ++j) {
            if ((j+1) % 2 == 0)
                evens.push_back(text[j]);
            else
                odds.push_back(text[j]);
        }
        text.clear();
        text.append(evens);
        text.append(odds);
    } 

    return text;
}

string decrypt(string text, int n) {
    if (text.empty() || n <= 0)
        return text;

    string evens = "";
    string odds = "";    
    size_t len = text.length();
    for (size_t i = 0; i < n; ++i) {
        evens.clear();
        odds.clear();
        for (size_t j = 0; j < len / 2; ++j) {
            evens.push_back(text[j]);
        }
        for (size_t j = len / 2; j < len; ++j) {
            odds.push_back(text[j]);
        }

        size_t index = 2;
        for (size_t j = 0; j < evens.length(); ++j) {
            text[index - 1] = evens[j];
            index += 2;
        }
        index = 1;
        for (size_t j = 0; j < odds.length(); ++j) {
            text[index - 1] = odds[j];
            index += 2;
        }
    }

    return text;
}