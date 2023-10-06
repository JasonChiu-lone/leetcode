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
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ans;
        vector<string> line;
        int wordsWidth = 0;
        // find how many words can fit into this line
        auto iter = words.begin();
        while(iter != words.end()){
            line.clear();
            wordsWidth = 0;
            if (iter + 1 == words.end()){
                // *iter is the last word
                line.push_back(*iter);
                wordsWidth = iter->length();
                iter++;
            }
            else{
                while (iter != words.end() && wordsWidth + iter->length() + (wordsWidth > 0) <= maxWidth){
                    // can fit in another word
                    line.push_back(*iter);
                    wordsWidth += iter->length() + (wordsWidth > 0); // and a space between them
                    iter++;
                }
            }
            // recalculate wordsWidth and distribute spaces
            wordsWidth = 0;
            for (int i = 0; i < line.size(); i++)
                wordsWidth += line[i].length();
            int cnt_spaces = maxWidth - wordsWidth;
            if (line.size() == 1){
                // only one word
                ans.push_back(line[0] + string(maxWidth-wordsWidth, ' '));
            }
            else{
                if (iter == words.end()){
                    // For the last line of text, it should be left-justified, and no extra space is inserted between words.
                    string line_s = line[0];
                    for (int i = 1; i < line.size(); i++){
                        line_s += " " + line[i];
                    }
                    line_s += string(maxWidth - line_s.length(), ' ');
                    ans.push_back(line_s);
                    continue;
                }
                int cnt_words = line.size();
                // cnt_words-1 spaces in between
                int least_space = (maxWidth - wordsWidth) / (cnt_words - 1);
                int extra_space = maxWidth - wordsWidth - (cnt_words - 1) * least_space;
                string line_s = line[0];
                int i = 1;
                for (; i <= extra_space; i++){
                    line_s += string(least_space+1, ' ');
                    line_s += line[i];
                }
                for (; i < line.size(); i++){
                    line_s += string(least_space, ' ');
                    line_s += line[i];
                }
                ans.push_back(line_s);
            }
        }
        return ans;
    }
};

void print(vector<string> &a){
    for (auto line:a){
        for (auto ch:line){
            if (ch == ' ') cout << '_';
            else cout << ch;
        }
        cout << endl;
    }
}

int main(){
    Solution s;
    // string str[] = {"This", "is", "an", "example", "of", "text", "justification."};
    // string str[] = {"What","must","be","acknowledgment","shall","be"};
    string str[] = {"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
    vector<string> q(str, str+19);
    vector<string> a = s.fullJustify(q, 20);
    print(a);
    return 0;
}