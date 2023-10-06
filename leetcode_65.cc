#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
public:
    bool is_integer(const string &s){
        /***
        An integer can be split up into these components (in order):

        (Optional) A sign character (either '+' or '-').
        One or more digits.
        */
        if (s.size() == 0) return false;
        // one or zero sign and must be at the first place if any
        if (s == "+" || s == "-") return false;
        int cnt_sign = count(s.begin(), s.end(), '+') + count(s.begin(), s.end(), '-');
        if (cnt_sign > 1) return false;
        if (cnt_sign){
            if (s[0] != '+' && s[0] != '-') return false;
            if (s.size() == 1) return false;
        }
        for (int i = cnt_sign; i < s.size(); i++){
            if (!isdigit(s[i])) return false;
        }
       return true;
    }
    bool is_decimal(const string &s){
        if (s.size() == 0) return false;
        /***
        A decimal number can be split up into these components (in order):

        (Optional) A sign character (either '+' or '-').
        One of the following formats:
        One or more digits, followed by a dot '.'.
        One or more digits, followed by a dot '.', followed by one or more digits.
        A dot '.', followed by one or more digits.
        */
        int cnt_sign = count(s.begin(), s.end(), '-') + count(s.begin(), s.end(), '+');
        if (cnt_sign > 1) return false;
        else if (cnt_sign == 1){
            if (s.size() == 1) return false;
        }
        int cnt_dot = count(s.begin(), s.end(), '.');
        if (cnt_dot != 1) return false;
        if (s.size() == cnt_sign + cnt_dot) return false;
        for (int i = cnt_sign; i < s.size(); i++){
            if ((!isdigit(s[i])) && s[i] != '.') return false;
        }
        return true;
    }
    bool isNumber(string s) {
        string first, second;
        // count 'E' or 'e'
        int e_cnt = count(s.begin(), s.end(), 'e') + count(s.begin(), s.end(), 'E');
        if (e_cnt > 1){
            return false;
        }
        else if (e_cnt == 1){
            // split s based on 'e' or 'E'
            int e_pos = s.find_first_of("eE", 0);
            // if s ends with an 'e' or 'E', return false
            if (e_pos == s.size()-1) return false;
            first = s.substr(0, e_pos); // a decimal or an integer
            second = s.substr(e_pos+1); // a integer
            return (is_decimal(first) || is_integer(first)) && is_integer(second);
        }
        else{ // e_cnt == 0
            return is_decimal(s) || is_integer(s);
        }
    }
};

int main(){
    Solution sol;
    string str[] = {"2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"};
    for (string s:str){
        cout << sol.isNumber(s) << endl;
    }
    cout << endl;
    string str_[] = {"abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"};
    for (string s_:str_){
        cout << sol.isNumber(s_) << endl;
    }
    return 0;
}