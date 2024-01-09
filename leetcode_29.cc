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
    int divide(int dividend, int divisor) {
        if (divisor == 1)
            return dividend;
        if (dividend == INT_MIN && divisor == -1) 
            return INT_MAX;
        unsigned int m = labs(dividend);
        unsigned int n = labs(divisor);
        unsigned int q = 0;
        bool sign = (dividend < 0) ^ (divisor < 0);
        if (n == 1) return sign ? -m : m;
        while (m >= n){
            unsigned int t = n;
            unsigned int p = 1;
            while ((m >> 1) >= t){
                t = t << 1;
                p = p << 1;
            }
            q += p;
            m -= t;
        }
        return sign ? -q : q;
    }
};

int main(){
    Solution s;
    cout << s.divide(-2147483648, 2) << endl;
    return 0;
}