#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

    string word = convToLower(rawWords);

    stringstream ss(word);

    
    std::set<std::string> currentSet;

    string str; // current string
    
    while (ss >> str)
    {
        str = trim(str);
        int start = 0;
        for (unsigned int i = 0; i < str.size(); i++)
        {
            if (str[i] < 'a' || str[i] > 'z')
            {
                string newstr = str.substr(start, i - start);
                if (newstr.size() >= 2)
                    currentSet.insert(newstr);
                start = i + 1;
            }
        }

        if (start > 0)
        {
            currentSet.insert(str.substr(start, str.size() - start));
        }
        else
        {
            currentSet.insert(str);
        }

    }
    return currentSet;


}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
