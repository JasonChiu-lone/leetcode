#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <bitset>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
public:
    void break_down(string to_break, vector<string> splits, set<string> &dict, vector<vector<string>> &ans){
        if (to_break.length() == 0){
            ans.push_back(splits);
            return;
        }
        for (int len = 1; len <= to_break.size(); len++){
            string split = to_break.substr(0, len);
            if (dict.count(split)){
                vector<string> new_splits = splits;
                new_splits.push_back(split);
                break_down(to_break.substr(len), new_splits, dict, ans);
            }
        }
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        set<string> set;
        for (string str: wordDict)
            set.insert(str);
        vector<vector<string>> ans;
        vector<string> splits;
        break_down(s, splits, set, ans);
        vector<string> ret;
        for (vector<string> a: ans){
            vector<string>::iterator iter = a.begin();
            string r = *iter;
            iter++;
            while(iter != a.end()){
                r.append(" ");
                r.append(*iter);
                iter++;
            }
            ret.push_back(r);
        }
        return ret;
    }
};

int main(){
    Solution s;
    string d[] = {"cat","cats","and","sand","dog"};
    vector<string> dict(d, d+5);
    string str = "catsanddog";
    s.wordBreak(str, dict);
    return 0;
}