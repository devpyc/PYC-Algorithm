// Segment Tree

// 1. 구간합
#include <bits/stdc++.h>
using namespace std;

const int MAX = 100001;
long long tree[MAX * 4];
long long arr[MAX];
int n;

void init(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    
    int mid = (start + end) / 2;
    init(node*2, start, mid);
    init(node*2+1, mid+1, end);
    tree[node] = tree[node*2] + tree[node*2+1];
}

long long query(int node, int start, int end, int left, int right) {
    if (left > end || right < start) 
        return 0;
    
    if (left <= start && end <= right) 
        return tree[node];
    
    int mid = (start + end) / 2;
    return query(node*2, start, mid, left, right) + 
           query(node*2+1, mid+1, end, left, right);
}

void update(int node, int start, int end, int index, long long val) {
    if (index < start || index > end) 
        return;
    
    if (start == end) {
        arr[index] = val;
        tree[node] = val;
        return;
    }
    
    int mid = (start + end) / 2;
    update(node*2, start, mid, index, val);
    update(node*2+1, mid+1, end, index, val);
    tree[node] = tree[node*2] + tree[node*2+1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    init(1, 0, n-1);
    
    int m;
    cin >> m;
    
    while(m--) {
        int op;
        cin >> op;
        
        if(op == 1) {
            int index;
            long long val;
            cin >> index >> val;
            update(1, 0, n-1, index-1, val);
        }
        else {
            int left, right;
            cin >> left >> right;
            cout << query(1, 0, n-1, left-1, right-1) << '\n';
        }
    }
    
    return 0;
}

// 2. 최대값

// #include <bits/stdc++.h>
// using namespace std;

// const int MAX = 100001;
// const int INF = 1e9;
// int max_tree[MAX * 4];
// int arr[MAX];
// int n;

// void init(int node, int start, int end) {
//     if (start == end) {
//         max_tree[node] = arr[start];
//         return;
//     }
    
//     int mid = (start + end) / 2;
//     init(node*2, start, mid);
//     init(node*2+1, mid+1, end);
//     max_tree[node] = max(max_tree[node*2], max_tree[node*2+1]);
// }

// int query(int node, int start, int end, int left, int right) {
//     if (left > end || right < start) 
//         return -INF;
    
//     if (left <= start && end <= right) 
//         return max_tree[node];
    
//     int mid = (start + end) / 2;
//     return max(query(node*2, start, mid, left, right),
//               query(node*2+1, mid+1, end, left, right));
// }

// void update(int node, int start, int end, int index, int val) {
//     if (index < start || index > end) 
//         return;
    
//     if (start == end) {
//         arr[index] = val;
//         max_tree[node] = val;
//         return;
//     }
    
//     int mid = (start + end) / 2;
//     update(node*2, start, mid, index, val);
//     update(node*2+1, mid+1, end, index, val);
//     max_tree[node] = max(max_tree[node*2], max_tree[node*2+1]);
// }

// int main() {
//     ios_base::sync_with_stdio(0);
//     cin.tie(0);
    
//     cin >> n;
//     for(int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }
    
//     init(1, 0, n-1);
    
//     int m;
//     cin >> m;
    
//     while(m--) {
//         int op;
//         cin >> op;
        
//         if(op == 1) {
//             int index, val;
//             cin >> index >> val;
//             update(1, 0, n-1, index-1, val);
//         }
//         else {
//             int left, right;
//             cin >> left >> right;
//             cout << query(1, 0, n-1, left-1, right-1) << '\n';
//         }
//     }
    
//     return 0;
// }

// 3. 최소값

// #include <bits/stdc++.h>
// using namespace std;

// const int MAX = 100001;
// const int INF = 1e9;
// int min_tree[MAX * 4];
// int arr[MAX];
// int n;

// void init(int node, int start, int end) {
//     if (start == end) {
//         min_tree[node] = arr[start];
//         return;
//     }
    
//     int mid = (start + end) / 2;
//     init(node*2, start, mid);
//     init(node*2+1, mid+1, end);
//     min_tree[node] = min(min_tree[node*2], min_tree[node*2+1]);
// }

// int query(int node, int start, int end, int left, int right) {
//     if (left > end || right < start) 
//         return INF;
    
//     if (left <= start && end <= right) 
//         return min_tree[node];
    
//     int mid = (start + end) / 2;
//     return min(query(node*2, start, mid, left, right),
//               query(node*2+1, mid+1, end, left, right));
// }

// void update(int node, int start, int end, int index, int val) {
//     if (index < start || index > end) 
//         return;
    
//     if (start == end) {
//         arr[index] = val;
//         min_tree[node] = val;
//         return;
//     }
    
//     int mid = (start + end) / 2;
//     update(node*2, start, mid, index, val);
//     update(node*2+1, mid+1, end, index, val);
//     min_tree[node] = min(min_tree[node*2], min_tree[node*2+1]);
// }

// int main() {
//     ios_base::sync_with_stdio(0);
//     cin.tie(0);
    
//     cin >> n;
//     for(int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }
    
//     init(1, 0, n-1);
    
//     int m;
//     cin >> m;
    
//     while(m--) {
//         int op;
//         cin >> op;
        
//         if(op == 1) {
//             int index, val;
//             cin >> index >> val;
//             update(1, 0, n-1, index-1, val);
//         }
//         else {
//             int left, right;
//             cin >> left >> right;
//             cout << query(1, 0, n-1, left-1, right-1) << '\n';
//         }
//     }
    
//     return 0;
// }