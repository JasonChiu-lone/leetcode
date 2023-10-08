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
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
public:
    bool isAdj(string &s1, string &s2){
        int n = s1.size();
        if (n != s2.size()) return false;
        int diff = 0;
        for (int i = 0; i < n; i++)
            diff += s1[i] != s2[i];
        return diff == 1;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) return 0;
        unordered_map<string, vector<string>> adj;
        for (int i = 0; i < n; i++){
            if (isAdj(beginWord, wordList[i])){
                adj[beginWord].push_back(wordList[i]);
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (isAdj(wordList[i], wordList[j])){
                    adj[wordList[i]].push_back(wordList[j]);
                }
            }
        }
        // bfs
        unordered_map<string, int> dist; // dist to beginWord
        queue<string> q;
        q.push(beginWord);
        while(q.size()){
            if (dist[endWord]) break;
            string s = q.front();
            q.pop();
            for (string adjWord: adj[s]){
                if (!dist[adjWord]){
                    q.push(adjWord);
                    dist[adjWord] = dist[s] + 1;
                }
            }
        }
        if (!dist[endWord]) return 0;
        return dist[endWord]+1;
    }
};

int main(){
    Solution s;
    
    return 0;
}