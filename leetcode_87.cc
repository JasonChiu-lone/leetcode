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
    bool isScramble(string s1, string s2) {
        if (s1 == s2) return true;
        if (s1.length() != s2.length()) return false;
        const int n = s1.length();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n+1, 0)));
        // dp[i][j][k]表示s1从i开始的长度为k的子串是否能由s2从j开始的长度为k的子串scramble而来
        // 初始化k=1的情况
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                dp[i][j][1] = (s1[i]==s2[j]);
            }
        }
        // 枚举k=2..n
        for (int k = 2; k <= n; k++){
            for (int i = 0; i <= n-k; i++){
                for (int j = 0; j <= n-k; j++){
                    // 枚举截断位置，前l个字符为一段
                    for (int l = 1; l < k; l++){
                        // Case 1: S1 <-> T1, S2 <-> T2
                        if (dp[i][j][l] && dp[i+l][j+l][k-l]){
                            dp[i][j][k] = true;
                            break;
                        }
                        // Case 2: S1 <-> T2, S2 <-> T1
                        if (dp[i][j+k-l][l] && dp[i+l][j][k-l]){
                            dp[i][j][k] = true;
                            break;
                        }
                    }
                }
            }
        }
        return dp[0][0][n];
    }
};

int main(){
    cout << __cplusplus << endl;
    Solution s;
    cout << s.isScramble("great", "rgeat") << endl;
    return 0;
}