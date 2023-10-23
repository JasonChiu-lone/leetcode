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
    string shortestPalindrome(string &s){
        // KMP algo.
        // s = cacacabc
        // i = 01234567
        // f = 00123401
        // r = cacacabc#cbacacac
        // f = 00123401010012345
        //     cbacacacabc
        //        ^^^^^
        // s = aacecaaa
        // rev = aaacecaa
        // r = aaacecaa#aacecaaa
        // f = 01200012012000123
        const int N = s.length();
        if (N <= 1) return s;
        string rev = s;
        reverse(rev.begin(), rev.end());
        string r = s + "#" + rev;
        const int M = r.length();
        vector<int> f(M, 0);
        for (int i = 1; i < M; i++){ // i = 2
            int t = f[i-1]; // t = 1
            while (t > 0 && r[t] != r[i]){ // 1 > 0 && s[1] == s[2]
                t = f[t-1]; // !
            }
            if (r[i] == r[t]){
                t++;
            }
            // cout << "setting f[" << i << "] to " << t << endl;
            f[i] = t;
        }
        return rev.substr(0, N - f[M-1]) + s;
    }
    /********TLE testcase 200 *********
    string shortestPalindrome(string &s){
        const int N = s.length();
        if (N <= 1) return s;
        vector<vector<bool>> dp(N, vector<bool>(N, false));
        for (int i = 0; i < N; i++){
            dp[i][i] = true;
        }
        // dp[i][j] = dp[i+1][j-1] && s[i] == s[j] if j - i ≥ 2 else s[i+1] == s[j-1]
        int rear = 0;
        for (int i = 0; i < N-1; i++){
            dp[i][i+1] = s[i] == s[i+1];
        }
        for (int offset = 2; offset < N; offset++){
            for (int i = 0; i < N - offset; i++){
                int j = i + offset;
                dp[i][j] = dp[i+1][j-1] && s[i] == s[j];
            }
        }
        for (int j = N - 1; j >= 0; j--){
            if (dp[0][j]){
                rear = j;
                break;
            }
        }
        string pre = s.substr(rear + 1);
        reverse(pre.begin(), pre.end());
        return pre + s;
    }
    ****/
    /****Testcases passed, but took too long.******
    string shortestPalindrome(string &s) {
        int rear = s.length() - 1;
        if (rear == -1) return s;
        for (; rear > 0; --rear){
            int i = 0;
            int j = rear;
            while (i <= j){
                if (s[i] != s[j]){
                    goto next_rear;
                }
                ++i;
                --j;
            }
            break;
            next_rear:
            continue;
        }
        string pre = s.substr(rear + 1);
        reverse(pre.begin(), pre.end());
        return pre + s;
    }
    *******************/
};

int main(){
    Solution s;
    string str1 = "aacecaaa";
    string str2 = "abcd";
    cout << s.shortestPalindrome(str1) << endl;
    cout << s.shortestPalindrome(str2) << endl;
    return 0;
}