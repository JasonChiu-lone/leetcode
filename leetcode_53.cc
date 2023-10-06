#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        string seq;
        for (int i = 1; i <= n; i++)
            seq.push_back('0'+i);
        for (int i = 1; i < k; i++){
            next_permutation(seq.begin(), seq.end());
        }
        return seq;
    }
};

int main(){
    
    return 0;
}