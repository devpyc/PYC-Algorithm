#include <bits/stdc++.h>
using namespace std;

// 연속된 부분합이 S가 되는 경우의 수 구하기
int twoPointer1(vector<int>& arr, long long S) {
   int n = arr.size();
   int start = 0, end = 0;
   long long sum = 0;
   int cnt = 0;
   
   while(start < n) {
       while(end < n && sum < S) {
           sum += arr[end++];
       }
       if(sum == S) cnt++;
       sum -= arr[start++];
   }
   return cnt;
}

// 두 수의 합이 X인 쌍의 개수 구하기 (정렬된 배열)
int twoPointer2(vector<int>& arr, int X) {
   int n = arr.size();
   int left = 0, right = n-1;
   int cnt = 0;
   
   while(left < right) {
       int sum = arr[left] + arr[right];
       if(sum == X) {
           cnt++;
           left++;
           right--;
       }
       else if(sum < X) {
           left++;
       }
       else {
           right--;
       }
   }
   return cnt;
}

// 길이가 M인 최소합 구간 찾기
int twoPointer3(vector<int>& arr, int M) {
   int n = arr.size();
   int sum = 0;
   int minSum;
   
   for(int i = 0; i < M; i++)
       sum += arr[i];
   minSum = sum;
   
   for(int i = M; i < n; i++) {
       sum += arr[i] - arr[i-M];
       minSum = min(minSum, sum);
   }
   return minSum;
}

// 크기가 N인 배열에서 서로 다른 값이 K개 이하인 가장 긴 연속 부분 수열의 길이
int twoPointer4(vector<int>& arr, int K) {
   int n = arr.size();
   int start = 0, end = 0;
   map<int, int> cnt;
   int maxLen = 0;
   
   while(end < n) {
       cnt[arr[end]]++;
       while(cnt.size() > K) {
           if(--cnt[arr[start]] == 0)
               cnt.erase(arr[start]);
           start++;
       }
       maxLen = max(maxLen, end - start + 1);
       end++;
   }
   return maxLen;
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   
   int n, target;
   cin >> n >> target;
   
   vector<int> arr(n);
   for(int i = 0; i < n; i++) {
       cin >> arr[i];
   }
   
   cout << "연속된 부분합이 " << target << "인 경우의 수: ";
   cout << twoPointer1(arr, target) << '\n';
   
   sort(arr.begin(), arr.end());
   cout << "두 수의 합이 " << target << "인 쌍의 개수: ";
   cout << twoPointer2(arr, target) << '\n';
   
   cout << "길이가 3인 최소합 구간: ";
   cout << twoPointer3(arr, 3) << '\n';
   
   cout << "서로 다른 값이 2개 이하인 가장 긴 연속 부분 수열의 길이: ";
   cout << twoPointer4(arr, 2) << '\n';
   
   return 0;
}