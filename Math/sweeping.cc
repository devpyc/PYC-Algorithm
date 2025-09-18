// Sweeping

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

vector<pii> points;
int n;

int lineSweeping() {
   vector<pii> events;
   for(auto [x, y] : points) {
       events.push_back({x, 1});    
       events.push_back({y, -1});   
   }
   sort(events.begin(), events.end());
   
   int ret = 0, cnt = 0;
   for(auto [x, type] : events) {
       cnt += type;
       ret = max(ret, cnt);
   }
   return ret;
}