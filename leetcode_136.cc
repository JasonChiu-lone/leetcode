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
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> candies(n, 1);
        for (int i = 0; i < n-1; i++){
            if (ratings[i+1] > ratings[i]){
                candies[i+1] = candies[i] + 1;
            }
        }
        int candy = 0;
        for (int i = n - 1; i > 0; i--){
            if (ratings[i-1] > ratings[i]){
                candies[i-1] = max(candies[i-1], candies[i] + 1);
            }
            candy += candies[i];
        }
        candy += candies[0];
        return candy;
    }
};

int main(){
    Solution s;
    int a[] = {1, 3, 4, 5, 2};
    vector<int> v(a, a+5);
    s.candy(v);
    return 0;
}