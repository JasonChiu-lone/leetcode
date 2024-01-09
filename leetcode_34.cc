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
    int binary_search(vector<int> &nums, int target, int i, int j){
        if (i > j) return -1;
        if (i == j) return nums[i] == target ? i : -1;
        int mid = (i + j) / 2;
        if (nums[mid] == target){
            return mid;
        }
        else if (nums[mid] > target){
            return binary_search(nums, target, i, mid-1);
        }
        else{
            return binary_search(nums, target, mid+1, j);
        }
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int size = nums.size();
        if (size == 0) return vector<int>{-1, -1};
        int k = binary_search(nums, target, 0, size - 1);
        cout << "k=" << k;
        int pos[2] = {k, k};
        if (k == -1) return vector<int>(pos, pos+2);
        while (pos[0] > 0 && nums[pos[0]-1] == nums[pos[0]]) pos[0]--;
        while (pos[1] < size-1 && nums[pos[1]+1] == nums[pos[1]]) pos[1]++;
        return vector<int>(pos, pos+2);
    }
};

int main(){
    Solution s;
    vector<int> nums{5,7,7,8,8,10};
    s.searchRange(nums, 8);
    s.searchRange(nums, 6);
    return 0;
}