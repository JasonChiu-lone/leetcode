#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

class Solution {
public:
    bool vge(const vector<int> &l, const vector<int> &r){
        if (l.size() != r.size() || l.size() == 0) return false;
        const int s = l.size();
        for (int i = 0; i < s; i++){
            if (l[i] < r[i]) return false;
        }
        return true;
    }
    string minWindow(const string &s, const string &t) {
        vector<int> alpha_t(128, 0);
        for (int i = 0; i < t.size(); i++)
            alpha_t[t[i]-'A']++;
        // vector<int> alpha_s = cnt_alpha(s);
        vector<int> alpha_s(128, 0);
        set<pair<int, pair<int, int> > > ans;
        int left = 0;
        int right = 0;
        while(right < s.size()){
            // extend right
            for (; right <= s.size(); ){
                if (right == s.size()) break;
                alpha_s[s[right++]-'A']++;
                if (vge(alpha_s, alpha_t)){
                    break;
                }
            }
            // shrink left
            while(left < s.size() && alpha_s[s[left]-'A'] > alpha_t[s[left]-'A']){
                alpha_s[s[left++]-'A']--;
            }
            if (vge(alpha_s, alpha_t))
                ans.insert(make_pair(right-1-left, make_pair(left, right-1)));
            // left = ++right;
            if (right >= s.size()) break;
        }
        if (ans.size() == 0) return "";
        else return s.substr(ans.begin()->second.first, ans.begin()->second.second-ans.begin()->second.first+1);
    }
};

int main(){
    string s, t;
    s = "ADOBECODEBANC", t = "ABC";
    // s = "a"; t = "a";
    // s = "a", t = "aa";
    Solution sol;
    cout << sol.minWindow("ab", "a") << endl;
    cout << sol.minWindow("bdab", "ab") << endl;
    cout << sol.minWindow("a", "b") << endl;
    cout << sol.minWindow("ADOBECODEBANC", "ABC") << endl;
    cout << sol.minWindow("a", "a") << endl;
    cout << sol.minWindow("a", "aa") << endl;
    cout << sol.minWindow("gxkvmymaztebptcdhquxemoowthbmzluwvpivdiuwoxmjzrqrmpyyemwxwylxlhtiwddcnyycvmnxeeoqtmqzbnzznkwyuriqulujjtnhfbejfubahsckhbjwnfwhweaspubbnpivsogxiizrcbdjemfstdzrhzjwwnzjehgwxnvivwzzadkerpyluyebzozxdzhjipficcqzyryauifozdbtdfwfvwcyxlhhbopfsfhtxfttqahrginlqjslhxkektonkdtcjavihrdxrnrxxejnndzvajblepyqvrtgtqobhtabgraevjrlpqipbjaibzyystemkuptnruujvaggrrvkznnlnvoowmjpsxbmmvbdrxooxxxrqudshqfxotnkhwzztbnfyqlpobgladerzhjjyogojtyssxtlagtywgqmhwyibezamkjmarajnabfxuqacjyaponzmnhnriofuzturvfevgjvczvglviamvzykimesalmbfisanwyvhtxjqfulowxlwyygkczmnnnuwixjgvfoqexgmttaptnnrludpvpfiezemwqttxjjbirnblpqgfgzqacixtnfxmmmlefebqoeyfuzsjryqxzjzbrwweeusqgdunixdybddv", "eyhvyxvygwb") << endl;
    return 0;
}