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
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        // 分治
        // buildings[i] = {left, right, height}
        deque<vector<vector<int>>> skyline;
        // push all left-top points into skyline
        // should also push floor points!
        vector<vector<int>> pt;
        for (auto &b: buildings){
            pt.clear();
            pt.emplace_back(b[0]);
            pt.emplace_back(b[2]);
            skyline.emplace_back(pt);
            pt.clear();
            pt.emplace_back(b[0] + b[1]);
            pt.emplace_back(0);
            skyline.emplace_back(pt);
        }
        // divide the problem
        while (skyline.size() > 1){
            vector<vector<int>> sil_1 = skyline[0];
            vector<vector<int>> sil_2 = skyline[1];
            skyline.pop_front();
            skyline.pop_front();
            // merge sil_1 and sil_2
            vector<vector<int>> sil_merge = merge(sil_1, sil_2);
        }
    }
    vector<vector<int>> merge(vector<vector<int>> &sil_1, vector<vector<int>> &sil_2){
        vector<vector<int>> merged;
        vector<vector<int>>::iterator iter_1 = sil_1.begin();
        vector<vector<int>>::iterator iter_2 = sil_2.begin();
        vector<int> pt;
        while (iter_1 != sil_1.end() && iter_2 != sil_2.end()){
            pt.clear();
            if (iter_1->at(0) == iter_2->at(0)){
                pt.push_back(iter_1->at(0));
                pt.push_back(iter_1->at(2));
                merged.push_back(pt);
                iter_1++;
                iter_2++;
            }
            else if (iter_1->at(0) < iter_2->at(0)){
                // if iter_1 is higher than the last item in merged, pop_back merged, and push in iter_1
                if (iter_1->at(2) >= merged.rbegin()->at(1)){
                    merged.pop_back();
                }
                pt.push_back(iter_1->at(0));
                pt.push_back(iter_1->at(2));
                merged.push_back(pt);
                iter_1++;
            }
            else if (iter_1->at(0) > iter_2->at(0)){
                if (iter_2->at(2) >= merged.rbegin()->at(1)){
                    merged.pop_back();
                }
                pt.push_back(iter_2->at(0));
                pt.push_back(iter_2->at(2));
                merged.push_back(pt);
                iter_2++;
            }
        }
        while (iter_1 != sil_1.end()){
            pt.clear();
            iter_1++;
        }
    }
};

int main(){
    Solution s;
    
    return 0;
}