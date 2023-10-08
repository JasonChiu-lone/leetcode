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
    struct Point{
        int x;
        int y;
        Point(){}
        Point(int x, int y): x(x), y(y){}
        Point operator+(Point &p){
            return Point(x+p.x, y+p.y);
        }
        bool isValid(){
            return x >= 0 && y >= 0;
        }
    };
    Point dir[2] = {Point(-1, 0), Point(0, -1)};
    void dfs(Point pt, int hp, vector<vector<int>> &ans, vector<vector<int>>& dungeon){
        if (dungeon[pt.x][pt.y] < 0){
            if (max(1, hp-dungeon[pt.x][pt.y]) > ans[pt.x][pt.y]) return;
            ans[pt.x][pt.y] = max(1, hp-dungeon[pt.x][pt.y]);
            hp = ans[pt.x][pt.y];
        }
        else{
            hp = max(1, hp-dungeon[pt.x][pt.y]);
            if (hp > ans[pt.x][pt.y]) return;
            ans[pt.x][pt.y] = hp;
        }
        cout << "the minimum hp required to get to (" << pt.x << ", " << pt.y << ") is " << hp << endl;
        Point left = pt + dir[0];
        Point up = pt + dir[1];
        if (left.isValid()) dfs(left, hp, ans, dungeon);
        if (up.isValid()) dfs(up, hp, ans, dungeon);
    }
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        queue<Point> q;
        int m = dungeon.size();
        int n = dungeon[0].size();
        Point princess(m-1, n-1);
        q.push(princess);
        Point knight(0, 0);
        vector<vector<int>> ans(m, vector<int>(n, 0x7fffffff));
        // 最后一个测试点爆了 dfs(princess, 1, ans, dungeon);
        if (dungeon[princess.x][princess.y] > 0){
            ans[princess.x][princess.y] = 1;
        }
        else
            ans[princess.x][princess.y] = 1 - dungeon[princess.x][princess.y];
        int hp_required;
        while(q.size()){
            Point pt = q.front();
            q.pop();
            Point left = pt + dir[0];
            Point up = pt + dir[1];
            if (left.isValid()){
                if (dungeon[left.x][left.y] > 0){
                    hp_required = max(1, ans[pt.x][pt.y] - dungeon[left.x][left.y]);
                    if (hp_required < ans[left.x][left.y]){
                        ans[left.x][left.y] = hp_required;
                        q.push(left);
                    }
                }
                else{
                    hp_required = ans[pt.x][pt.y] - dungeon[left.x][left.y];
                    if (hp_required < ans[left.x][left.y]){
                        ans[left.x][left.y] = hp_required;
                        q.push(left);
                    }
                }
            }
            if (up.isValid()){
                if (dungeon[up.x][up.y] > 0){
                    hp_required = max(1, ans[pt.x][pt.y] - dungeon[up.x][up.y]);
                    if (hp_required < ans[up.x][up.y]){
                        ans[up.x][up.y] = hp_required;
                        q.push(up);
                    }
                }
                else{
                    hp_required = ans[pt.x][pt.y] - dungeon[up.x][up.y];
                    if (hp_required < ans[up.x][up.y]){
                        ans[up.x][up.y] = hp_required;
                        q.push(up);
                    }
                }
            }
        }
        return ans[0][0];
    }
};

int main(){
    Solution s;
    int a[3][3] = {{-2,-3,3} , {-5,-10,1}, {10,30,-5}};
    vector<vector<int>> v(3);
    v[0] = vector<int>(a[0], a[0]+3);
    v[1] = vector<int>(a[1], a[1]+3);
    v[2] = vector<int>(a[2], a[2]+3);
    s.calculateMinimumHP(v);
    return 0;
}