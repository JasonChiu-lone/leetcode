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
    int minCut(string s) {
        int n = s.size();
        vector<vector<int>> isPalindrome(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            isPalindrome[i][i] = 1;
        for (int i = 0; i < n-1; i++)
            isPalindrome[i][i+1] = s[i] == s[i+1];
        for (int span = 3; span <= n; span++){
            for (int i = 0; i <= n-span; i++){
                isPalindrome[i][i+span-1] = isPalindrome[i+1][i+span-2] * s[i] == s[i+span-1];
            }
        }
        vector<int> dp(n, 0); // dp[i]=将s[0...i]切割为回文子串的最少切割次数
        for (int i = 0; i < n; i++){
            if (!isPalindrome[0][i]){
                dp[i] = i;
            }
        }
        for (int i = 1; i < n; i++){
            for (int j = 1; j <= i; j++){
                if (isPalindrome[j][i]){
                    dp[i] = min(dp[i], dp[j-1]+1);
                }
            }
        }
        return dp[n-1];
    }
};

int main(){
    Solution s;
    s.minCut("abcccb");
    return 0;
}