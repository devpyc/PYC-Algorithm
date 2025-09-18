#include <bits/stdc++.h>
#define ll long long
#define Point pair<ll, ll>
using namespace std;

ll cross(const Point& p1, const Point& p2) {
   return p1.first * p2.second - p1.second * p2.first;
}

ll cross(const Point& p1, const Point& p2, const Point& p3) {
   return cross({p2.first - p1.first, p2.second - p1.second},
               {p3.first - p1.first, p3.second - p1.second});
}

vector<Point> getConvexHull(vector<Point>& points) {
   sort(points.begin(), points.end());
   vector<Point> hull;
   for(const auto& p : points) {
       while(hull.size() >= 2 && cross(hull[hull.size()-2], hull.back(), p) <= 0)
           hull.pop_back();
       hull.push_back(p);
   }
   int s = hull.size();
   for(int i = points.size()-2; i >= 0; i--) {
       while(hull.size() >= s+1 && cross(hull[hull.size()-2], hull.back(), points[i]) <= 0)
           hull.pop_back();
       hull.push_back(points[i]);
   }
   hull.pop_back();
   return hull;
}

ll getDist(const Point& p1, const Point& p2) {
   ll dx = p1.first - p2.first;
   ll dy = p1.second - p2.second;
   return dx*dx + dy*dy;
}

pair<int, int> rotatingCalipers(const vector<Point>& hull) {
   int n = hull.size();
   if(n <= 1) return {0, 0};
   if(n == 2) return {0, 1};
   
   int j = 1;
   ll maxDist = 0;
   pair<int, int> ret = {0, 0};
   
   for(int i = 0; i < n; i++) {
       int ni = (i+1)%n;
       Point vi = {hull[ni].first - hull[i].first, hull[ni].second - hull[i].second};
       
       while(true) {
           int nj = (j+1)%n;
           Point vj = {hull[nj].first - hull[j].first, hull[nj].second - hull[j].second};
           if(cross(vi, vj) <= 0) break;
           j = nj;
       }
       
       ll dist = getDist(hull[i], hull[j]);
       if(dist > maxDist) {
           maxDist = dist;
           ret = {i, j};
       }
   }
   
   return ret;
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   
   int n;
   cin >> n;
   
   vector<Point> points(n);
   for(int i = 0; i < n; i++)
       cin >> points[i].first >> points[i].second;
   
   vector<Point> hull = getConvexHull(points);
   auto [i, j] = rotatingCalipers(hull);
   
   cout << fixed << setprecision(6);
   cout << sqrt(getDist(hull[i], hull[j])) << '\n';
   
   return 0;
}