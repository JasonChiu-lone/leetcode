#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // monotonous stack
        stack<int> s;
        int ans = 0; int w = 0; int h = 0;
        const int size = (const int) heights.size();
        for (int i = 0; i < size; i++){
            if (s.empty()){
                s.push(i);
                continue;
            }
            while(!s.empty() && heights[i] < heights[s.top()]){
                h = heights[s.top()];
                s.pop();
                if (s.empty()) w = i;
                else w = i - s.top() - 1;
                if (w * h > ans) ans = w * h;
            }
            s.push(i);
        }
        while (!s.empty()){
            h = heights[s.top()];
            s.pop();
            if (s.empty()) w = size;
            else w = size - s.top() - 1;
            if (w * h > ans) ans = w * h;
        }
        return ans;
    }
};

int main(){
    Solution s;
    int a[] = {0, 9};
    vector<int> q(a, a+2);
    cout << s.largestRectangleArea(q) << endl;

    return 0;
}