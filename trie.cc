#include <bits/stdc++.h>
using namespace std;

struct Trie {
    Trie* next[26];
    bool isEnd;
    
    Trie() {
        fill(next, next + 26, nullptr);
        isEnd = false;
    }
    
    ~Trie() {
        for(int i = 0; i < 26; i++)
            delete next[i];
    }
    
    void insert(string& str, int idx) {
        if(idx == str.length()) {
            isEnd = true;
            return;
        }
        
        int cur = str[idx] - 'a';
        if(next[cur] == nullptr)
            next[cur] = new Trie();
        next[cur]->insert(str, idx + 1);
    }
    
    bool find(string& str, int idx) {
        if(idx == str.length())
            return isEnd;
            
        int cur = str[idx] - 'a';
        if(next[cur] == nullptr)
            return false;
        return next[cur]->find(str, idx + 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n;
    
    Trie* root = new Trie();
    
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        root->insert(s, 0);
    }
    
    cin >> m;
    for(int i = 0; i < m; i++) {
        string s;
        cin >> s;
        cout << (root->find(s, 0) ? "1\n" : "0\n");
    }
    
    delete root;
    return 0;
}