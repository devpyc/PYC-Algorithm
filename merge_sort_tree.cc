#include <bits/stdc++.h>
using namespace std;

class MergeSortTree {
private:
   int n;
   vector<vector<int>> tree;
   
   void build(int node, int start, int end, const vector<int>& arr) {
       if(start == end) {
           tree[node] = {arr[start]};
           return;
       }
       
       int mid = (start + end) >> 1;
       build(node*2, start, mid, arr);
       build(node*2+1, mid+1, end, arr);
       
       vector<int>& left = tree[node*2];
       vector<int>& right = tree[node*2+1];
       tree[node].resize(left.size() + right.size());
       
       merge(left.begin(), left.end(), 
             right.begin(), right.end(), 
             tree[node].begin());
   }
   
   int query(int node, int start, int end, int left, int right, int k) {
       if(right < start || end < left) return 0;
       if(left <= start && end <= right) {
           return tree[node].end() - 
                  upper_bound(tree[node].begin(), tree[node].end(), k);
       }
       
       int mid = (start + end) >> 1;
       return query(node*2, start, mid, left, right, k) + 
              query(node*2+1, mid+1, end, left, right, k);
   }
   
public:
   MergeSortTree(const vector<int>& arr) {
       n = arr.size();
       tree.resize(4*n);
       build(1, 0, n-1, arr);
   }
   
   int query(int left, int right, int k) {
       return query(1, 0, n-1, left, right, k);
   }
};

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   
   int n;
   cin >> n;
   
   vector<int> arr(n);
   for(int i = 0; i < n; i++) {
       cin >> arr[i];
   }
   
   MergeSortTree mst(arr);
   
   int q;
   cin >> q;
   while(q--) {
       int l, r, k;
       cin >> l >> r >> k;
       l--; r--;
       cout << mst.query(l, r, k) << '\n';
   }
   
   return 0;
}