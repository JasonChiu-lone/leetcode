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
    int maxProfit(int k, vector<int>& prices) {
        const int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));
        // dp[i][j][k] 第i个交易日已完成j笔交易（包含尚未sell的），且最后一笔交易为sell(k==0)或buy(k==1)所能达到的最大利润
        // dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1] + prices[i]) (rest or sell)
        // dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0] - prices[i]) (rest or buy)
        const int max_k = n / 2;
        int profit = 0;
        if (k >= max_k){
            for (int i = 0; i < n-1; i++){
                profit += max(0, prices[i+1]-prices[i]);
            }
            return profit;
        }
        
        for (int i = 0; i < n; i++){
            dp[i][1][1] = -prices[i];
        }
        for (int j = 0; j < n; j++){
            dp[0][j][1] = -prices[0];
        }
        for (int i = 1; i < n; i++){
            for (int j = 1; j <= k; j++){
                dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1] + prices[i]);
                dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0] - prices[i]);
            }
        }
        return dp[n-1][k][0];
    }
};

int main(){
    Solution s;
    int a[] = {1,2,4,2,5,7,2,4,9,0};
    vector<int> v(a, a+10);
    cout << s.maxProfit(4, v) << endl;
    return 0;
}