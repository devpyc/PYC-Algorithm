#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

struct Node {
   int start, end, slink;
   map<char, int> next;
   
   Node(int start = -1, int end = -1) 
       : start(start), end(end), slink(-1) {}
   
   int length() { return end - start + 1; }
};

class SuffixTree {
private:
   string s;
   vector<Node> tree;
   int remaining, activeNode, activeEdge, activeLength;
   int pos;
   
   int newNode(int start, int end = -1) {
       tree.emplace_back(start, end);
       return tree.size() - 1;
   }
   
   char activeEdgeChar() {
       return s[activeEdge];
   }
   
   bool walkDown(int node) {
       if (activeLength >= tree[node].length()) {
           activeEdge += tree[node].length();
           activeLength -= tree[node].length();
           activeNode = node;
           return true;
       }
       return false;
   }
   
   void addSuffixLink(int node) {
       if (pos > 0) tree[pos].slink = node;
       pos = node;
   }
   
   void extend(int i) {
       tree[0].end = i;
       remaining++;
       pos = 0;
       
       while (remaining > 0) {
           if (activeLength == 0) activeEdge = i;
           
           if (tree[activeNode].next.find(activeEdgeChar()) == tree[activeNode].next.end()) {
               int leaf = newNode(i);
               tree[activeNode].next[activeEdgeChar()] = leaf;
               addSuffixLink(activeNode);
           } else {
               int nxt = tree[activeNode].next[activeEdgeChar()];
               if (walkDown(nxt)) continue;
               
               if (s[tree[nxt].start + activeLength] == s[i]) {
                   activeLength++;
                   addSuffixLink(activeNode);
                   break;
               }
               
               int split = newNode(tree[nxt].start, tree[nxt].start + activeLength - 1);
               tree[activeNode].next[activeEdgeChar()] = split;
               
               int leaf = newNode(i);
               tree[split].next[s[i]] = leaf;
               tree[nxt].start += activeLength;
               tree[split].next[s[tree[nxt].start]] = nxt;
               addSuffixLink(split);
           }
           
           remaining--;
           
           if (activeNode == 0 && activeLength > 0) {
               activeLength--;
               activeEdge = i - remaining + 1;
           } else {
               activeNode = tree[activeNode].slink > 0 ? tree[activeNode].slink : 0;
           }
       }
   }
   
public:
   SuffixTree(string str) : s(str + "$") {
       tree.reserve(2 * s.length());
       remaining = activeNode = activeEdge = activeLength = pos = 0;
       tree.emplace_back(-1, -1);
       
       for (int i = 0; i < s.length(); i++) {
           extend(i);
       }
   }
   
   void print(int node = 0, int depth = 0) {
       for (auto [ch, next] : tree[node].next) {
           for (int i = 0; i < depth; i++) cout << "  ";
           for (int i = tree[next].start; i <= tree[next].end; i++) {
               cout << s[i];
           }
           cout << '\n';
           print(next, depth + 1);
       }
   }
   
   bool find(string& pattern) {
       int node = 0, pos = 0;
       
       while (pos < pattern.length()) {
           if (tree[node].next.find(pattern[pos]) == tree[node].next.end()) {
               return false;
           }
           
           node = tree[node].next[pattern[pos]];
           int len = tree[node].length();
           
           for (int i = tree[node].start; i <= tree[node].end && pos < pattern.length(); i++, pos++) {
               if (s[i] != pattern[pos]) return false;
           }
       }
       return true;
   }
};

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   
   string s;
   cin >> s;
   
   SuffixTree st(s);
   
   cout << "Suffix Tree Structure:\n";
   st.print();
   
   int q;
   cin >> q;
   while (q--) {
       string pattern;
       cin >> pattern;
       if (st.find(pattern)) {
           cout << "Found\n";
       } else {
           cout << "Not Found\n";
       }
   }
   
   return 0;
}