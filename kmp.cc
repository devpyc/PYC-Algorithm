// KMP (Knuth-Morris-Pratt)
#include <bits/stdc++.h>
using namespace std;

vector<int> getFailure(string pattern) {
   int m = pattern.length();
   vector<int> fail(m, 0);
   
   int j = 0;
   for(int i = 1; i < m; i++) {
       while(j > 0 && pattern[i] != pattern[j]) {
           j = fail[j-1];
       }
       if(pattern[i] == pattern[j]) {
           fail[i] = ++j;
       }
   }
   return fail;
}

vector<int> kmp(string text, string pattern) {
   vector<int> ans;
   vector<int> fail = getFailure(pattern);
   
   int n = text.length();
   int m = pattern.length();
   
   int j = 0;
   for(int i = 0; i < n; i++) {
       while(j > 0 && text[i] != pattern[j]) {
           j = fail[j-1];
       }
       if(text[i] == pattern[j]) {
           if(j == m-1) {
               ans.push_back(i-m+1);
               j = fail[j];
           }
           else {
               j++;
           }
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
   
   vector<int> result = kmp(text, pattern);
   
   cout << result.size() << '\n';
   for(int pos : result) {
       cout << pos + 1 << ' ';
   }
   
   return 0;
}