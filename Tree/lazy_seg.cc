// Segment Tree with Lazy Propagation

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX = 100001;
ll tree[MAX * 4], lazy[MAX * 4];
int arr[MAX];
int n;

void propagate(int node, int start, int end) {
   if (lazy[node] != 0) {
       tree[node] += (end - start + 1) * lazy[node];
       if (start != end) {
           lazy[node * 2] += lazy[node];
           lazy[node * 2 + 1] += lazy[node];
       }
       lazy[node] = 0;
   }
}

ll init(int node, int start, int end) {
   if (start == end)
       return tree[node] = arr[start];
       
   int mid = (start + end) / 2;
   return tree[node] = init(node * 2, start, mid) + init(node * 2 + 1, mid + 1, end);
}

void update_range(int node, int start, int end, int left, int right, ll diff) {
   propagate(node, start, end);
   
   if (left > end || right < start)
       return;
       
   if (left <= start && end <= right) {
       tree[node] += (end - start + 1) * diff;
       if (start != end) {
           lazy[node * 2] += diff;
           lazy[node * 2 + 1] += diff;
       }
       return;
   }
   
   int mid = (start + end) / 2;
   update_range(node * 2, start, mid, left, right, diff);
   update_range(node * 2 + 1, mid + 1, end, left, right, diff);
   tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int start, int end, int left, int right) {
   propagate(node, start, end);
   
   if (left > end || right < start)
       return 0;
       
   if (left <= start && end <= right)
       return tree[node];
       
   int mid = (start + end) / 2;
   return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   
   cin >> n;
   for (int i = 0; i < n; i++)
       cin >> arr[i];
       
   init(1, 0, n - 1);
   
   int m;
   cin >> m;
   
   while (m--) {
       int op;
       cin >> op;
       
       if (op == 1) {
           int left, right;
           ll diff;
           cin >> left >> right >> diff;
           update_range(1, 0, n - 1, left - 1, right - 1, diff);
       } else {
           int left, right;
           cin >> left >> right;
           cout << query(1, 0, n - 1, left - 1, right - 1) << '\n';
       }
   }
   return 0;
}