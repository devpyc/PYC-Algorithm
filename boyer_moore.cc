// Boyer-Moore

#include <bits/stdc++.h>
using namespace std;

const int NO_OF_CHARS = 256;

void badCharHeuristic(string pattern, int badchar[NO_OF_CHARS]) {
    int m = pattern.length();
    
    for(int i = 0; i < NO_OF_CHARS; i++) {
        badchar[i] = -1;
    }
    
    for(int i = 0; i < m; i++) {
        badchar[(int)pattern[i]] = i;
    }
}

vector<int> boyerMoore(string text, string pattern) {
    vector<int> ans;
    int n = text.length();
    int m = pattern.length();
    
    int badchar[NO_OF_CHARS];
    badCharHeuristic(pattern, badchar);
    
    int s = 0;
    while(s <= (n - m)) {
        int j = m - 1;
        
        while(j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }
        
        if(j < 0) {
            ans.push_back(s);
            s += (s + m < n) ? m - badchar[text[s + m]] : 1;
        }
        else {
            s += max(1, j - badchar[text[s + j]]);
        }
    }
    return ans;
}

void computeGoodSuffix(string pattern, int goodSuffix[]) {
    int m = pattern.length();
    vector<int> suffix(m);
    
    suffix[m-1] = m;
    int g = m-1;
    int f = m-1;
    
    for(int i = m-2; i >= 0; i--) {
        if(i > g && suffix[i + m - 1 - f] < i - g) {
            suffix[i] = suffix[i + m - 1 - f];
        }
        else {
            if(i < g) g = i;
            f = i;
            while(g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
                g--;
            }
            suffix[i] = f - g;
        }
    }
    
    for(int i = 0; i < m; i++) {
        goodSuffix[i] = m;
    }
    
    for(int i = m-1; i >= 0; i--) {
        if(suffix[i] == i + 1) {
            for(int j = 0; j < m-1-i; j++) {
                if(goodSuffix[j] == m) {
                    goodSuffix[j] = m-1-i;
                }
            }
        }
    }
    
    for(int i = 0; i <= m-2; i++) {
        goodSuffix[m-1-suffix[i]] = m-1-i;
    }
}

vector<int> boyerMooreHorspool(string text, string pattern) {
    vector<int> ans;
    int n = text.length();
    int m = pattern.length();
    
    int badchar[NO_OF_CHARS];
    int goodSuffix[m];
    
    badCharHeuristic(pattern, badchar);
    computeGoodSuffix(pattern, goodSuffix);
    
    int s = 0;
    while(s <= n-m) {
        int j = m-1;
        
        while(j >= 0 && pattern[j] == text[s+j]) {
            j--;
        }
        
        if(j < 0) {
            ans.push_back(s);
            s += goodSuffix[0];
        }
        else {
            s += max(goodSuffix[j], j - badchar[text[s+j]]);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string text, pattern;
    getline(cin, text);
    getline(cin, pattern);
    
    vector<int> result1 = boyerMoore(text, pattern);
    cout << "Boyer-Moore: " << result1.size() << '\n';
    for(int pos : result1) {
        cout << pos + 1 << ' ';
    }
    cout << '\n';
    
    vector<int> result2 = boyerMooreHorspool(text, pattern);
    cout << "Boyer-Moore-Horspool: " << result2.size() << '\n';
    for(int pos : result2) {
        cout << pos + 1 << ' ';
    }
    
    return 0;
}