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
    int m = 0;
    int n = 0;
    struct TrieNode{
        int type; // -1: root; 0: inner; 1: leaf
        unordered_map<char, TrieNode*> children;
        TrieNode(): type(-1){}
        TrieNode(int type): type(type){}
        void insert(string s){
            if (s.length()){
                if (children.contains(s[0])){
                    if (s.length() == 1){
                        children[s[0]]->type = 1;
                    }
                    else{
                        children[s[0]]->insert(s.substr(1));
                    }
                }
                else{
                    if (s.length() == 1){
                        children[s[0]] = new TrieNode(1);
                    }
                    else{
                        children[s[0]] = new TrieNode(0);
                        children[s[0]]->insert(s.substr(1));
                    }
                }
            }
        }
    };
    struct Point{
        int x, y;
        Point(int x, int y): x(x), y(y){}
        Point operator+(Point &r){
            return Point(x + r.x, y + r.y);
        }
        friend bool operator==(const Point &l, const Point &r){
            return l.x == r.x && l.y == r.y;
        }
    };
    Point directions[4] = {Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1)};
    void dfs(vector<vector<char>> &board, TrieNode *node, vector<vector<Point>> vis, set<string> &ans, string s, vector<string> &words){
        if (node->type == 1){
            ans.insert(s);
        }
        if (node->children.size() == 0)
            return;
        for (char next = 'a'; next <= 'z'; next++){
            if (node->children.contains(next)){
                if (node->type == -1){
                    for (int i = 0; i < m; i++){
                        for (int j = 0; j < n; j++){
                            if (board[i][j] == next){
                                vis.push_back(vector<Point>(1, Point(i, j)));
                                dfs(board, node->children[next], vis, ans, s+next, words);
                                vis.pop_back();
                            }
                        }
                    }
                    continue;
                }
                // find all positions == next and next to points in vis
                for (int i = 0; i < vis.size(); i++){
                    Point pt = *vis[i].rbegin();
                    for (int j = 0; j < 4; j++){
                        Point dir = directions[j];
                        Point neighbor = pt + dir;
                        if (neighbor.x >= 0 && neighbor.x < m && neighbor.y >= 0 && neighbor.y < n && board[neighbor.x][neighbor.y] == next){
                            if (find(vis[i].begin(), vis[i].end(), neighbor) == vis[i].end()){
                                vis[i].push_back(neighbor);
                                dfs(board, node->children[next], vis, ans, s+next, words);
                                vis[i].pop_back();
                            }
                        }
                    }
                }
            }
        }
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode *root = new TrieNode();
        for (string w: words){
            root->insert(w);
        }
        m = board.size();
        n = board[0].size();
        vector<vector<Point>> vis;
        set<string> ans_set;
        dfs(board, root, vis, ans_set, "", words);
        vector<string> ans;
        for (auto iter = ans_set.begin(); iter != ans_set.end(); iter++){
            ans.push_back(*iter);
        }
        return ans;
    }
};

int main(){
    Solution s;
    char a1[4] = {'o', 'a', 'a', 'n'};
    char a2[4] = {'e', 't', 'a', 'e'};
    char a3[4] = {'i', 'h', 'k', 'r'};
    char a4[4] = {'i', 'f', 'l', 'v'};
    vector<char> v1(a1, a1+4);
    vector<char> v2(a2, a2+4);
    vector<char> v3(a3, a3+4);
    vector<char> v4(a4, a4+4);
    vector<vector<char>> v;
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    vector<string> words;
    words.push_back("oath");
    words.push_back("pea");
    words.push_back("eat");
    words.push_back("rain");
    vector<string> ans1 = s.findWords(v, words);
    char a5[2] = {'a', 'b'};
    char a6[2] = {'c', 'd'};
    vector<char> v5(a5, a5+2);
    vector<char> v6(a6, a6+2);
    vector<vector<char>> w;
    w.push_back(v5);
    w.push_back(v6);
    vector<string> wds;
    wds.push_back("abcb");
    vector<string> ans2 = s.findWords(w, wds);
    string s1[] = {"ab","cb","ad","bd","ac","ca","da","bc","db","adcb","dabc","abb","acb"};
    vector<string> w1(s1, s1+13);
    vector<string> ans3 = s.findWords(w, w1);
    return 0;
}