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
    void nextPermutation(vector<int>& nums) {
        const int size = nums.size();
        int i = size - 2;
        for (; i >= 0; i--){
            // find the first non-decreasing element from the right
            if (nums[i] < nums[i + 1]){
                break;
            }
        }
        if (i < 0){
            reverse(nums.begin(), nums.end());
            return;
        }
        // find the first element (nums[j]) on the right of nums[i] that is greater than or equal to nums[i], and swap them
        int j = size - 1;
        for (; j > i; j--){
            if (nums[j] > nums[i]){
                break;
            }
        }
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
        // reverse elements right to current nums[j]
        reverse(nums.begin() + i + 1, nums.end());
    }
};

int main(){
    Solution s;
    
    return 0;
}