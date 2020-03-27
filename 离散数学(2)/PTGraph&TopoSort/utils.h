#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

vector<string> split(const string& str, const string& pattern){
    vector<string> strvec;
    string::size_type pos;
    string::size_type size = str.size();
    for(string::size_type i = 0; i < size; i++){
        pos = str.find(pattern, i);
        if(pos < size){
            string s = str.substr(i, pos - i);
            strvec.push_back(s);
            i = pos + pattern.size() - 1;
        }else{
            string s = str.substr(i, pos - i);
            strvec.push_back(s);
            break;
        }
    }
    return strvec;
}