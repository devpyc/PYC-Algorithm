#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct Point {
   ll x, y;
   Point() {}
   Point(ll x, ll y) : x(x), y(y) {}
   
   bool operator<(const Point& p) const {
       if(x != p.x) return x < p.x;
       return y < p.y;
   }
   
   bool operator==(const Point& p) const {
       return x == p.x && y == p.y;
   }
};

struct Line {
   Point p1, p2;
   Line() {}
   Line(Point p1, Point p2) : p1(p1), p2(p2) {}
};

ll ccw(const Point& p1, const Point& p2, const Point& p3) {
   ll ret = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
   if(ret > 0) return 1;
   if(ret < 0) return -1;
   return 0;
}

bool isIntersect(const Line& l1, const Line& l2) {
   Point p1 = l1.p1, p2 = l1.p2, p3 = l2.p1, p4 = l2.p2;
   
   ll ccw1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
   ll ccw2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
   
   if(ccw1 == 0 && ccw2 == 0) {
       if(p1 > p2) swap(p1, p2);
       if(p3 > p4) swap(p3, p4);
       return !(p2 < p3 || p4 < p1);
   }
   
   return ccw1 <= 0 && ccw2 <= 0;
}

pair<double,double> intersection(const Line& l1, const Line& l2) {
   double x1 = l1.p1.x, y1 = l1.p1.y;
   double x2 = l1.p2.x, y2 = l1.p2.y;
   double x3 = l2.p1.x, y3 = l2.p1.y;
   double x4 = l2.p2.x, y4 = l2.p2.y;
   
   double px = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) /
               ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
   double py = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) /
               ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
               
   return {px, py};
}

bool isPointOnSegment(const Point& p, const Line& l) {
   if(ccw(l.p1, l.p2, p) != 0) return false;
   
   if(l.p1 > l.p2) return !(p > l.p1 || p < l.p2);
   return !(p < l.p1 || p > l.p2);
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   
   int t;
   cin >> t;
   
   while(t--) {
       ll x1, y1, x2, y2, x3, y3, x4, y4;
       cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
       
       Line l1(Point(x1, y1), Point(x2, y2));
       Line l2(Point(x3, y3), Point(x4, y4));
       
       if(isIntersect(l1, l2)) {
           cout << "YES\n";
           
           if(ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2) != 0 ||
              ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2) != 0) {
               auto [x, y] = intersection(l1, l2);
               cout << fixed << setprecision(10) << x << " " << y << "\n";
           }
       } else {
           cout << "NO\n";
       }
   }
   
   return 0;
}