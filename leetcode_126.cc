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
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> ans;
        unordered_set<string> set;
        for (auto &s: wordList)
            set.insert(s);
        if (!set.count(endWord))
            return ans;
        set.insert(beginWord);
        unordered_map<string, vector<string>> adj;
        unordered_map<string, int> dist; // # length of path to endWord
        dist[endWord] = 0;
        queue<string> q;
        q.push(endWord);
        while(q.size()){ // bfs to find the shortest path
            auto s = q.front();
            q.pop();
            auto t = s; // backup untransformed word
            for (int i = 0; i < s.size(); i++){
                char old = s[i];
                for (char trans = 'a'; trans <= 'z'; trans++){
                    if (trans == old) continue;
                    // else
                    s[i] = trans;
                    if (set.count(s)){ // transformed s is in wordList or is beginWord
                        if (!dist.count(s) || dist[s] == dist[t] + 1){ // ?
                            adj[s].push_back(t); // t is a transforamtion of s
                            if (!dist.count(s))
                                q.push(s);
                            dist[s] = dist[t] + 1;
                            if (s == beginWord)
                                break;
                        }
                    }
                }
                s = t; // restore s
            }
        }
        if (!dist.count(beginWord))
            return ans;
        vector<string> v;
        dfs(beginWord, dist, v, ans, adj);
        return ans;
    }
    void dfs(
        const string beginWord, 
        unordered_map<string, int> &dist, 
        vector<string> &v, 
        vector<vector<string>> &ans, 
        unordered_map<string, vector<string>> &adj
    ){
        v.push_back(beginWord);
        if (dist[beginWord] == 0){
            ans.push_back(v);
            v.pop_back();
            return;
        }
        for (auto nextWord: adj[beginWord])
            dfs(nextWord, dist, v, ans, adj);
        v.pop_back();
    }
};


/*
ostream &operator<<(ostream &os, vector<int> &v){
        cout <<"[";
        for (auto s:v) cout << s << ",";
        cout << "]"<<endl;
        return os;
    }
class Solution {
public:
    bool isAdjacent(const string &s1, const string &s2){
        int cnt_diff = 0;
        const int size = s1.size();
        for (int i = 0; i < size; i++){
            cnt_diff += s1[i] != s2[i];
        }
        return cnt_diff == 1;
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        const int len = beginWord.length();
        const int size = wordList.size();
        int end_word_idx = -1;
        for (int i = 0; i < size; i++){
            if (wordList[i] == endWord){
                end_word_idx = i;
                break;
            }
        }
        if (end_word_idx == -1) return vector<vector<string>>();
        // 防止反复查询
        // vector<vector<int>> isAdj(size+1, vector<int>(size+1, 0));
        vector<vector<int>> isAdj(size, vector<int>(size, 0));
        for (int i = 0; i < size-1; i++){
            for (int j = i+1; j < size; j++){
                isAdj[i][j] = isAdjacent(wordList[i], wordList[j]);
                isAdj[j][i] = isAdj[i][j];
            }
        }
        
        queue<int> q;
        vector<int> vis(size, 0);
        for (int i = 0; i < size; i++){
            if (isAdjacent(beginWord, wordList[i])){
                q.push(i);
                vis[i] = 1;
            }
        }
        while(!q.empty() && vis[end_word_idx] == 0){
            int si = q.front();
            q.pop();
            for (int i = 0; i < size; i++){
                if (isAdj[si][i] && vis[i] == 0){
                    vis[i] = vis[si] + 1;
                    q.push(i);
                }
            }
        }
        if (vis[end_word_idx] == 0) return vector<vector<string>>(); // no path
        int path_len = vis[end_word_idx];
        if (path_len == 1){
            string path[] = {beginWord, endWord};
            return vector<vector<string>>(1, vector<string>(path, path+2));
        }
        // cout << path_len << endl;
        deque<vector<int>> ansq;
        vector<int> ansqv;
        for (int i = 0; i < size; i++){
            if (isAdjacent(beginWord, wordList[i])){
                ansq.push_back(vector<int>(1, i));
            }
        }
        // ansq.push(ansqv);
        while(ansq.front().size() < path_len){
            //cout << "vecs are:" << endl;
            //for (auto v:ansq) cout << "\t" << v << endl;
            ansqv = ansq.front();
            ansq.pop_front();
            if (ansqv.size() == path_len-1){
                if (isAdj[*ansqv.rbegin()][end_word_idx]){
                    //cout << "111pushing in " << end_word_idx << endl;
                    ansqv.push_back(end_word_idx);
                    ansq.push_back(ansqv);
                }
                continue;
            }
            for (int i = 0; i < size; i++){
                if ((isAdj[*ansqv.rbegin()][i]==1) && (find(ansqv.begin(), ansqv.end(), i) == ansqv.end())){
                    //cout << "adding " << i << " into ansqv" << ansqv<< endl;
                    auto ansqv_(ansqv);
                    ansqv_.push_back(i);
                    ansq.push_back(ansqv_);
                }
                else{
                    //cout << "i=" << i << ", *ansqv.rbegin()==" << *ansqv.rbegin()<< ", end_word_idx=="<<end_word_idx<< ", isAdj[*ansqv.rbegin()][end_word_idx]==" << (isAdj[*ansqv.rbegin()][end_word_idx]) << ", find(ansqv.begin(), ansqv.end(), i) == ansqv.end()==" << (find(ansqv.begin(), ansqv.end(), i) == ansqv.end())<< endl;
                }
            }
        }
        //cout << "there are " << ansq.size() << " diff sols" << endl;
        vector<vector<string>> ansv;
        while(!ansq.empty()){
            auto vi = ansq.front();
            ansq.pop_front();
            vector<string> vs(1, beginWord);
            for (int i = 0; i < vi.size(); i++){
                vs.push_back(wordList[vi[i]]);
            }
            ansv.push_back(vs);
        }
        return ansv;
    }
};

*/

int main(){
    Solution s;
    string wl[] = {"kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim"};
    vector<string> v(wl, wl+497);
    //string wl[] = {"hot","dot","dog","lot","log","cog"};
    //vector<string> v(wl, wl+6);
    //string wl[] = {"a", "b", "c"};
    //vector<string> v(wl, wl+3);
    s.findLadders("cet", "ism", v);
    // s.findLadders("hit", "cog", v); // hit hot lot log cog | hit hot dot dog cog 0 1 2 5
    //s.findLadders("a", "c", v);
    return 0;
}