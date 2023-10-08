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

// 偷鸡了，这里是O(n)，使用二分可以在O(logn)时间完成查找
class Solution {
public:
    int findMin(vector<int>& nums) {
        vector<int>::iterator it = nums.begin();
        int first = nums[0];
        int last = nums[0];
        while(it != nums.end()){
            if (*it < last){
                return *it;
            }
            last = *it;
            it++;
        }
        return min(first, last);
    }
};

int main(){
    Solution s;
    
    return 0;
}