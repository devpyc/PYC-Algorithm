#include <bits/stdc++.h>
using namespace std;

// O(n log n) LIS
vector<int> lis(vector<int>& arr) {
   int n = arr.size();
   vector<int> dp;
   vector<int> idx(n);
   
   for(int i = 0; i < n; i++) {
       auto it = lower_bound(dp.begin(), dp.end(), arr[i]);
       if(it == dp.end()) {
           idx[i] = dp.size();
           dp.push_back(arr[i]);
       } else {
           idx[i] = it - dp.begin();
           *it = arr[i];
       }
   }
   
   int len = dp.size();
   vector<int> result;
   for(int i = n-1, j = len-1; i >= 0; i--) {
       if(idx[i] == j) {
           result.push_back(arr[i]);
           j--;
       }
   }
   reverse(result.begin(), result.end());
   return result;
}

// dp O(n²) LIS
vector<int> lis_dp(vector<int>& arr) {
   int n = arr.size();
   vector<int> dp(n, 1);
   vector<int> prev(n, -1);
   
   int maxLen = 1, endIdx = 0;
   
   for(int i = 0; i < n; i++) {
       for(int j = 0; j < i; j++) {
           if(arr[j] < arr[i] && dp[i] < dp[j] + 1) {
               dp[i] = dp[j] + 1;
               prev[i] = j;
               if(dp[i] > maxLen) {
                   maxLen = dp[i];
                   endIdx = i;
               }
           }
       }
   }
   
   vector<int> result;
   for(int i = endIdx; i != -1; i = prev[i]) {
       result.push_back(arr[i]);
   }
   reverse(result.begin(), result.end());
   return result;
}

//세그먼트 트리를 이용한 LIS
class SegmentTree {
private:
   vector<int> tree;
   int size;
   
   void update(int node, int start, int end, int index, int value) {
       if(index < start || end < index) return;
       
       if(start == end) {
           tree[node] = max(tree[node], value);
           return;
       }
       
       int mid = (start + end) / 2;
       update(node*2, start, mid, index, value);
       update(node*2+1, mid+1, end, index, value);
       tree[node] = max(tree[node*2], tree[node*2+1]);
   }
   
   int query(int node, int start, int end, int left, int right) {
       if(right < start || end < left) return 0;
       if(left <= start && end <= right) return tree[node];
       
       int mid = (start + end) / 2;
       return max(query(node*2, start, mid, left, right),
                 query(node*2+1, mid+1, end, left, right));
   }

public:
   SegmentTree(int n) : size(n) {
       tree.resize(4*n);
   }
   
   void update(int index, int value) {
       update(1, 0, size-1, index, value);
   }
   
   int query(int left, int right) {
       return query(1, 0, size-1, left, right);
   }
};

vector<int> lis_segtree(vector<int>& arr) {
   int n = arr.size();
   vector<pair<int,int>> pairs(n);
   for(int i = 0; i < n; i++) {
       pairs[i] = {arr[i], i};
   }
   sort(pairs.begin(), pairs.end());
   
   vector<int> compressed(n);
   for(int i = 0; i < n; i++) {
       compressed[pairs[i].second] = i;
   }
   
   SegmentTree seg(n);
   vector<int> dp(n), prev(n, -1);
   int maxLen = 0, endIdx = 0;
   
   for(int i = 0; i < n; i++) {
       int val = seg.query(0, compressed[i]) + 1;
       dp[i] = val;
       seg.update(compressed[i], val);
       
       if(val > maxLen) {
           maxLen = val;
           endIdx = i;
       }
   }
   
   vector<int> result;
   int curLen = maxLen;
   int curNum = arr[endIdx];
   for(int i = endIdx; i >= 0; i--) {
       if(dp[i] == curLen && arr[i] <= curNum) {
           result.push_back(arr[i]);
           curLen--;
           curNum = arr[i];
       }
   }
   reverse(result.begin(), result.end());
   return result;
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   
   int n;
   cin >> n;
   vector<int> arr(n);
   for(int i = 0; i < n; i++) {
       cin >> arr[i];
   }
   
   vector<int> result1 = lis(arr);
   vector<int> result2 = lis_dp(arr);
   vector<int> result3 = lis_segtree(arr);
   
   cout << result1.size() << '\n';
   for(int x : result1) cout << x << ' ';
   cout << '\n';
   
   cout << result2.size() << '\n';
   for(int x : result2) cout << x << ' ';
   cout << '\n';
   
   cout << result3.size() << '\n';
   for(int x : result3) cout << x << ' ';
   cout << '\n';
   
   return 0;
}