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
    bool check(vector<string> &board, int row, int col){
        // no Q's in the same row
        for (int j = 0; j < board.size(); j++){
            if (board[row][j] == 'Q' && j != col) return false;
        }
        // no Q's in the same col
        for (int i = 0; i < board.size(); i++){
            if (board[i][col] == 'Q' && i != row) return false;
        }
        // no Q's in the diagonal direction
        int n = board.size();
        for (int offset = 1; (row-offset >= 0 || row+offset < n || col-offset >= 0 || col+offset < n); offset++){
            if (row-offset >= 0 && col-offset >= 0 && board[row-offset][col-offset] == 'Q') return false;
            if (row+offset < n && col-offset >= 0 && board[row+offset][col-offset] == 'Q') return false;
            if (row-offset >= 0 && col+offset < n && board[row-offset][col+offset] == 'Q') return false;
            if (row+offset < n && col+offset < n && board[row+offset][col+offset] == 'Q') return false;
        }
        return true;
    }
    vector<vector<string> > solveNQueens(int n) {
        typedef vector<string> Board;
        typedef pair<Board, int> Node; // depth
        Node root = make_pair(Board(n, string(n, '.')), 0);
        queue<Node> q;
        q.push(root);
        while(!q.empty() && q.front().second < n){
            Node node = q.front();
            q.pop();
            int depth = node.second;
            for (int j = 0; j < n; j++){
                Node child = node;
                child.first[depth][j] = 'Q';
                child.second++;
                if (check(child.first, depth, j)){
                    q.push(child);
                }
            }
        }
        vector<Board> ans;
        while(q.size()){
            ans.push_back(q.front().first);
            q.pop();
        }
        return ans;
    }
};

ostream &operator<< (ostream &os, const vector<vector<string> > &ans){
    for (auto it = ans.begin(); it != ans.end(); it++){
        cout << "-----------------------" << endl;
        for (auto jt = it->begin(); jt != it->end(); jt++){
            cout << *jt << endl;
        }
    }
    return os;
}

int main(){
    Solution s;
    cout << s.solveNQueens(1).size() << endl;
    cout << s.solveNQueens(2).size() << endl;
    cout << s.solveNQueens(3).size() << endl;
    cout << s.solveNQueens(4).size() << endl;
    cout << s.solveNQueens(5).size() << endl;
    cout << s.solveNQueens(6).size() << endl;
    cout << s.solveNQueens(7).size() << endl;
    cout << s.solveNQueens(8).size() << endl;
    cout << s.solveNQueens(9).size() << endl;
    return 0;
}