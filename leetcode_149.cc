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
            friend bool operator < (const Point &p, const Point &q){
                return p.x < q.x || (p.x == q.x && p.y < q.y);
            }
        };
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        map<Point, int> shared_pts;
        int ans = 1;
        for (vector<int> &p: points){
            shared_pts = map<Point, int>();

            for (vector<int> &q: points){
                if (p == q)
                    continue;
                int dy = q[1] - p[1];
                int dx = q[0] - p[0];

                if (dx == 0){
                    shared_pts[Point(0, 0)]++;
                    ans = max(ans, shared_pts[Point(0, 0)]+1);
                    continue;
                }
                if (dy == 0){
                    shared_pts[Point(0, 1)]++;
                    ans = max(ans, shared_pts[Point(0, 1)]+1);
                    continue;
                }
                // 约分，并确保dx>0
                if (dx < 0){
                    dy *= -1;
                    dx *= -1;
                }
                for (int factor = min(dx, abs(dy)); factor > 1; factor--){
                    if (abs(dy) % factor == 0 && dx % factor == 0){
                        dy /= factor;
                        dx /= factor;
                        break;
                    }
                }
                shared_pts[Point(dy, dx)]++;
                ans = max(ans, shared_pts[Point(dy, dx)]+1);
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    return 0;
}