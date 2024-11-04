#include <bits/stdc++.h>
using namespace std;

// 기본적인 0-1 배낭문제
int knapsack01(vector<int>& weight, vector<int>& value, int maxWeight) {
   int n = weight.size();
   vector<int> dp(maxWeight + 1);
   
   for(int i = 0; i < n; i++)
       for(int w = maxWeight; w >= weight[i]; w--)
           dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
   
   return dp[maxWeight];
}

// 최대 K개 선택 가능한 배낭문제
int boundedKnapsack(vector<int>& weight, vector<int>& value, vector<int>& count, int maxWeight) {
   int n = weight.size();
   vector<int> dp(maxWeight + 1);
   
   for(int i = 0; i < n; i++)
       for(int k = 1; k <= count[i]; k++)
           for(int w = maxWeight; w >= weight[i]; w--)
               dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
   
   return dp[maxWeight];
}

// 무제한 선택 가능한 배낭문제 (완전 배낭)
int unboundedKnapsack(vector<int>& weight, vector<int>& value, int maxWeight) {
   int n = weight.size();
   vector<int> dp(maxWeight + 1);
   
   for(int w = 1; w <= maxWeight; w++)
       for(int i = 0; i < n; i++)
           if(weight[i] <= w)
               dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
   
   return dp[maxWeight];
}

// 경로 추적이 가능한 0-1 배낭문제
vector<int> knapsackWithPath(vector<int>& weight, vector<int>& value, int maxWeight) {
   int n = weight.size();
   vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1));
   
   for(int i = 1; i <= n; i++) {
       for(int w = 0; w <= maxWeight; w++) {
           if(weight[i-1] <= w)
               dp[i][w] = max(dp[i-1][w], dp[i-1][w - weight[i-1]] + value[i-1]);
           else
               dp[i][w] = dp[i-1][w];
       }
   }
   
   vector<int> selected;
   int w = maxWeight;
   for(int i = n; i > 0; i--) {
       if(dp[i][w] != dp[i-1][w]) {
           selected.push_back(i-1);
           w -= weight[i-1];
       }
   }
   
   return selected;
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   
   int n, maxWeight;
   cin >> n >> maxWeight;
   
   vector<int> weight(n), value(n), count(n);
   for(int i = 0; i < n; i++)
       cin >> weight[i] >> value[i] >> count[i];
       
   cout << "0-1 배낭문제: " << knapsack01(weight, value, maxWeight) << '\n';
   cout << "Bounded 배낭문제: " << boundedKnapsack(weight, value, count, maxWeight) << '\n';
   cout << "Unbounded 배낭문제: " << unboundedKnapsack(weight, value, maxWeight) << '\n';
   
   cout << "선택된 물건들: ";
   vector<int> selected = knapsackWithPath(weight, value, maxWeight);
   for(int idx : selected)
       cout << idx << ' ';
   cout << '\n';
   
   return 0;
}