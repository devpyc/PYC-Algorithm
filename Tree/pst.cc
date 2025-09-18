// Persistent Segment Tree

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
   ll sum;
   Node *left, *right;
   Node(ll val = 0) : sum(val), left(nullptr), right(nullptr) {}
};

const int MAX = 100001;
vector<Node*> roots;
int arr[MAX];
int n;

Node* build(int start, int end) {
   Node* node = new Node();
   
   if (start == end) {
       node->sum = arr[start];
       return node;
   }
   
   int mid = (start + end) / 2;
   node->left = build(start, mid);
   node->right = build(mid + 1, end);
   node->sum = node->left->sum + node->right->sum;
   return node;
}

Node* update(Node* prev, int start, int end, int idx, int val) {
   Node* node = new Node();
   
   if (start == end) {
       node->sum = val;
       return node;
   }
   
   int mid = (start + end) / 2;
   if (idx <= mid) {
       node->right = prev->right;
       node->left = update(prev->left, start, mid, idx, val);
   } else {
       node->left = prev->left;
       node->right = update(prev->right, mid + 1, end, idx, val);
   }
   node->sum = node->left->sum + node->right->sum;
   return node;
}

ll query(Node* node, int start, int end, int left, int right) {
   if (right < start || end < left) return 0;
   if (left <= start && end <= right) return node->sum;
   
   int mid = (start + end) / 2;
   return query(node->left, start, mid, left, right) + 
          query(node->right, mid + 1, end, left, right);
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   
   cin >> n;
   for(int i = 0; i < n; i++) 
       cin >> arr[i];
   
   roots.push_back(build(0, n-1));
   
   int m;
   cin >> m;
   
   int version = 0;
   while(m--) {
       int op;
       cin >> op;
       
       if(op == 1) {
           int idx, val;
           cin >> idx >> val;
           idx--;
           roots.push_back(update(roots[version], 0, n-1, idx, val));
           version++;
       } else if(op == 2) {
           int ver, left, right;
           cin >> ver >> left >> right;
           ver--; left--; right--;
           cout << query(roots[ver], 0, n-1, left, right) << '\n';
       }
   }
   return 0;
}