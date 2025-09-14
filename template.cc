#pragma GCC optimize("O3,unroll-loops,inline,fast-math,no-stack-protector")
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <bitset>
#include <iterator>
#include <tuple>
#include <climits>
#include <cassert>
#include <numeric> 
#include <random>
#include <iomanip>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define ld long double
using namespace std;
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define S second
#define F first
#define all(x) x.begin(),x.end()
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Line
{
    ll slope,intercept;
    Line(ll slope , ll intercept) : slope(slope),intercept(intercept){};
    ll value(ll x)
    {
        return x*slope+intercept;
    }
    ll intersection(Line y)
    {
        return ((y.intercept - intercept + slope - y.slope - 1ll) / (slope-y.slope));
    }
    void print()
    {
    	cout<<slope<<" "<<intercept<<" ";
    }
};
struct Point
{
	ll x,y;
	Point(ll nx,ll ny)
	{
		x = nx;
		y = ny;
	}
	Point operator + (Point p2)
	{
		return Point(x+p2.x,y+p2.y);
	}
	Point operator - (Point p2)
	{
		return Point(x-p2.x,y-p2.y);
	}
	ll operator * (Point p2)
	{
		return x*p2.y-y*p2.x;
	}
};
bool comp(Point a,Point b)
{
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}
vector<Point> ch(vector<Point> & pts)
{
	vector<Point> answer;
	answer.push_back(pts[0]);
	ll l = 0;
	for (ll e = 1;e<pts.size();e++)
	{
		while (answer.size() > 1 && (pts[e]-answer[l-1])*(answer[l]-answer[l-1])>0)
		{
			answer.erase(--answer.end());
			l--;
		}
		answer.push_back(pts[e]);
		l++;
	}
	answer.erase(--answer.end());
	return answer;
}
vector<Point> CH(vector<Point> & pts)
{
	sort(pts.begin(),pts.end(),comp);
	vector<Point> answer = ch(pts);
	reverse(pts.begin(),pts.end());
	vector<Point> h = ch(pts);
	for (Point i : h) answer.push_back(i);
	return answer;
}
ll A(vector<Point> & pts)
{
	ll answer = 0;
	ll n = pts.size();
	for (ll i = 0;i<n;i++)
	{
		answer += pts[i]*pts[(i+1)%n];
	}
	return answer;
}
struct CHT
{
    deque<pair<Line,ll>> lines;
    void insert(ll m,ll c)
    {
        Line line(m,c);
        while (lines.size() > 1 && lines.back().second >= lines.back().first.intersection(line))
        {
            lines.pop_back();
        }
        if (lines.empty())
        {
            lines.emplace_back(line,0);
            return;
        }
        lines.emplace_back(line,lines.back().first.intersection(line));
        // for (auto i : lines)
        // {
        	// i.first.print();
        	// cout<<i.second<<"\n";
        // }
    }
    ll query(ll x)
    {
        while (lines.size() > 1)
        {
            if (lines[1].first.value(x) > lines[0].first.value(x)) lines.pop_front();
            else break;
        }
        // lines.front().first.print();
        return lines.front().first.value(x);
    }
    ll query2(ll x)
    {
        auto qry = *lower_bound(lines.rbegin(), lines.rend(),
                                make_pair(Line(0, 0), x),
                                [&](const pair<Line, int> &a, const pair<Line, int> &b) {
                                    return a.second > b.second;
                                });
        return qry.first.value(x);
    }
};
const int ALPHABET_SIZE = 26;
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};
class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (current->children[index] == NULL) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }
    
    void deleteWord(const string& word) {
        deleteWordRecursive(root, word, 0);
    }
    
    bool deleteWordRecursive(TrieNode* node, const string& word, int depth) {
        if (node == nullptr) {
            return false;
        }

        if (depth == word.length()) {
            if (!node->isEndOfWord) {
                return false; // Word not present in the trie
            }

            node->isEndOfWord = false;

            // If the node has no children, it can be safely removed
            return nodeHasNoChildren(node);
        }

        int index = word[depth] - 'a';
        if (deleteWordRecursive(node->children[index], word, depth + 1)) {
            // Delete the child node if it can be deleted
            delete node->children[index];
            node->children[index] = nullptr;

            // Check if the current node has no children and is not an end-of-word node
            return nodeHasNoChildren(node);
        }

        return false;
    }

    bool nodeHasNoChildren(TrieNode* node) {
        for (TrieNode* child : node->children) {
            if (child != nullptr) {
                return false;
            }
        }
        return !node->isEndOfWord;
    }
    
    bool search(const string& word) {
        TrieNode* node = searchNode(word);
        return (node != NULL && node->isEndOfWord);
    }
    
    TrieNode* searchNode(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (current->children[index] == NULL) {
                return NULL; // Character not found in the trie
            }
            current = current->children[index];
        }
        return current;
    }
    
    void printAllWords() {
        string currentWord;
        printWordsRecursive(root, currentWord);
    }
    
    void printWordsRecursive(TrieNode* node, string& currentWord) {
        if (node == NULL) {
            return;
        }

        if (node->isEndOfWord) {
            cout << currentWord << endl;
        }

        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->children[i] != NULL) {
                currentWord.push_back('a' + i);
                printWordsRecursive(node->children[i], currentWord);
                currentWord.pop_back();
            }
        }
    }
};

vector<vector<ll>> ST(vector<ll> & a)
{
    ll n = a.size();
    vector<vector<ll>> st(n,vector<ll>(21));
    for (ll e = 0;e<n;e++)
    {
        st[e][0] = a[e];
    }
    for (ll k = 1;k<=20;k++)
    {
        for (ll e = 0;e<n-(1<<k)+1;e++)
        {
        	st[e][k] = min(st[e][k-1],st[e+(1<<(k-1))][k-1]);
        }
    }
    return st;
}
vector<ll> twopows;
ll FINDST(vector<vector<ll>> & st,ll l,ll r)
{
    if (twopows.empty())
    {
        twopows = vector<ll>(1000001);
        for (ll e = 1,d = 0;e<=1000000;e++)
        {
            if ((1 << (d+1)) == e) d++;
            twopows[e] = d;
        }
    }
    ll k = twopows[r-l+1];
    return min(st[l][k],st[r-(1 << k)+1][k]);
}
struct LCT // queries are sorted in increasing order
{
	ll n;
	vector<Line> tree;
	vector<ll> Q;
	LCT(vector<ll> q)
	{
		Q = q;
		n = q.size()-1;
		tree.assign(4*n+4,Line(0,(ll)-1e18));
	}
	void add(Line curr,ll v = 1,ll l = 1,ll r = -1)
	{
		if (r == -1) r = n;
		if (l == r)
		{
			if (curr.value(Q[l]) > tree[v].value(Q[l])) swap(curr,tree[v]);
			return;
		}
		ll mid = (l+r)/2;
		if (curr.value(Q[mid]) > tree[v].value(Q[mid]))
		{
			swap(curr,tree[v]);
		}
		if (curr.slope > tree[v].slope) add(curr,v*2+1,mid+1,r);
		else add(curr,v*2,l,mid);
	}
	ll find(ll ind,ll v = 1,ll l = 1,ll r = -1)
	{
		// cout<<tree[v].slope<<" "<<tree[v].intercept<<"\n";
		if (r == -1) r = n;
		if (l == r) return tree[v].value(Q[ind]);
		ll mid = (l+r)/2;
		if (ind <= mid) return max(tree[v].value(Q[ind]),find(ind,v*2,l,mid));
		else return max(tree[v].value(Q[ind]),find(ind,v*2+1,mid+1,r));
	}
};
ll get(ll a,vector<ll> & pr)
{
	return pr[a] = (pr[a] == a ? a : get(pr[a],pr));
}
bool merge(ll a,ll b,vector<ll> & pr,vector<ll> & siz)
{
	 a = get(a,pr),b = get(b,pr);
	 if (a == b) return 0;
	 if (siz[a] > siz[b])
	 {
	 	pr[b] = a;
	 	siz[a] += siz[b];
	 }
	 else
	 {
	 	pr[a] = b;
	 	siz[b] += siz[a];
	 }
	 return 1;
}
mt19937_64 mt(time(0));
ld rnd()
{
	ld ANS = mt();
	ANS /= mt.max();
	return ANS;
}
void read(vector<ll> & a)
{
	for (ll & i : a) cin>>i;
}
void read(vector<vector<ll>> & a)
{
	for (vector<ll> & i : a)
	{
		for (ll & j : i) cin>>j;
	}
}
void print(vector<ll> & a)
{
	for (ll & i : a) cout<<i<<" ";
	cout<<"\n";
}
void print(vector<vector<ll>> & a)
{
	for (vector<ll> & i : a)
	{
		for (ll & j : i) cout<<j<<" ";
		cout<<"\n";
	}
}
struct BIGINT
{
	vector<ll> a;
	ll len;
	BIGINT(ll n)
	{
		len = n;
		a.assign(n,0ll);
	}
	void add(BIGINT b)
	{
		for (ll e = len-1;e>0;e--)
		{
			a[e] += b.a[e];
			if (a[e] >= 10)
			{
				a[e-1] += 1;
				a[e] -= 10;
			}
		}
	}
	void print()
	{
		bool f = 0;
		for (ll e = 0;e<len;e++)
		{
			if (a[e] > 0) f = 1;
			if (f) cout<<a[e];
		}
		if (!f) cout<<0;
		cout<<"\n";
	}
};
ll mod = 1e9+7;
ll mult(vector<ll> a)
{
	ll answer = 1;
	for (ll i : a)
	{
		answer *= i;
		answer %= mod;
	}
	return answer;
}
ll binpow(ll n,ll k = mod-2,ll M = mod)
{
	bitset<31> o(k);
	ll curr = 1;
	for (ll e = 30;e>-1;e--)
	{
		curr *= curr;
		curr %= M;
		if (o[e])
		{
			curr *= n;
			curr %= M;
		}
	}
	return curr;
}
vector<ll> fact,invfact;
inline ll bincoef(ll n,ll k)
{
	if (n < k || k < 0) return 0;
	if (fact.empty())
	{
		fact = invfact = vector<ll>(3000001,1);
		for (ll e = 1;e<=3000000;e++)
		{
			fact[e] = (fact[e-1]*e)%mod;
		}
		invfact[3000000] = binpow(fact[3000000]);
		for (ll e = 2999999;e>=0;e--)
		{
			invfact[e] = (invfact[e+1]*(e+1))%mod;
		}
	}
	return ((fact[n]*invfact[n-k])%mod*invfact[k])%mod;;
}
vector<vector<ll>> G(ll n,ll m = -1)
{
	if (m == -1) m = n-1;
	vector<vector<ll>> ed(n);
	for (ll i = 0;i<m;i++)
	{
		ll u,v;cin>>u>>v;
		u--;v--;
		ed[u].push_back(v);
		ed[v].push_back(u);
	}
	return ed;
}
vector<ll> bfs(vector<ll> v,vector<vector<ll>> & ed)
{
	vector<ll> dist(ed.size(),-1);
	queue<ll> Q;
	for (ll i : v)
	{
		dist[i] = 0;
		Q.push(i);
	}
	while (!Q.empty())
	{
		ll v = Q.front();
		Q.pop();
		for (ll u : ed[v])
		{
			if (dist[u] == -1)
			{
				dist[u] = dist[v]+1;
				Q.push(u);
			}
		}
	}
	return dist;
}
vector<ll> dij(ll v,vector<vector<pair<ll,ll>>> & ed)
{
	set<pair<ll,ll>> vert;
	vector<ll> dist(ed.size(),1e18);
	dist[v] = 0;
	vert.insert({0,v});
	while (!vert.empty())
	{
		ll v = (*vert.begin()).second;
		vert.erase(vert.begin());
		for (pair<ll,ll> u : ed[v])
		{
			if (dist[u.first] > dist[v]+u.second)
			{
				vert.erase({dist[u.first],u.first});
				dist[u.first] = dist[v]+u.second;
				vert.insert({dist[u.first],u.first});
			}
		}
	}
	return dist;
}
ll x = 99901;
vector<ll> PX,INVX;
vector<ll> HASH(string & s)
{
	ll n = s.size();
	if (PX.empty())
	{
		PX.assign(1000001,1);INVX.assign(1000001,1);
		for (ll i = 1;i<=1000000;i++)
		{
			PX[i] = (PX[i-1]*x)%mod;
		}
		INVX[1000000] = binpow(PX[1000000]);
		for (ll i = 999999;i>=0;i--)
		{
			INVX[i] = (INVX[i+1]*x)%mod;
		}
	}
	vector<ll> hash(n);
	for (ll i = 0;i<n;i++)
	{
		hash[i] = ((i > 0 ? hash[i-1] : 0ll)+s[i]*PX[i])%mod;
	}
	return hash;
}
ll FH(vector<ll> & hash,ll l,ll r)
{
	return ((hash[r]-(l > 0 ? hash[l-1] : 0ll)+mod)*INVX[l])%mod;
}
vector<ll> Mob(ll n)
{
	vector<ll> mob(n+1,1),p(n+1,1);
	for (ll i = 2;i<=n;i++)
	{
		if (!p[i])
		{
			continue;
		}
		for (ll j = i;j<=n;j+=i)
		{
			p[j] = 0;
			if (j%(i*i) == 0) mob[j] = 0;
			mob[j] = -mob[j];
		}
	}
	return mob;
}
vector<ll> ModSqrt(ll c,ll p)
{
	if (c == 0) return {0};
	if (p == 2)
	{
		return {1};
	}
	if (binpow(c,(p-1)/2,p) != 1) return {};
	ll l = 0,q = p-1;
	while (q%2 == 0)
	{
		q /= 2;
		l++;
	}
	ll n = 1;
	while (binpow(n,(p-1)/2,p) == 1)
	{
		n = rand()%p;
	}
	ll e = 0;
	ll inv = binpow(n,p-2,p);
	for (ll i = 2;i<=l;i++)
	{
		ll x = (binpow(inv,e,p)*c)%p;
		if (binpow(x,(p-1)/(1ll << i),p) != 1) e += (1ll << (i-1));
	}
	ll a = (binpow(inv,e/2,p)*binpow(c,(q+1)/2,p))%p;
	ll b = (binpow(n,e/2,p)*a)%p;
	return {b,p-b};
}
pair<ll,ll> bez(ll a,ll b)
{
	if (a == 0) return {0,1};
	if (b == 0) return {1,0};
	pair<ll,ll> tmp;
	if (a > b)
	{
		tmp = bez(a%b,b);
		tmp.second -= a/b*tmp.first;
	}
	else
	{
		tmp = bez(a,b%a);
		tmp.first -= b/a*tmp.second;
	}
	return tmp;
}
struct JiDriverSegmentTree {
    static const int T = (1 << 21);
    static const long long INF = 1e15 + 7;
 
    struct Node {
        long long min;
        int minCnt;
        long long secondMin;
 
        long long max;
        int maxCnt;
        long long secondMax;
 
        long long sum;
 
        long long pushSum;
        long long pushEq;
        // If we have pushEq, no other pushes should be made. They're all combined together in pushEq.
        // Otherwise we first apply pushSum and then min= and max= pushes (in any order btw).
    } tree[T];
 
    int n;
 
    void doPushEq(int v, int l, int r, long long val) {
        tree[v].min = tree[v].max = tree[v].pushEq = val;
        tree[v].minCnt = tree[v].maxCnt = r - l;
        tree[v].secondMax = -INF;
        tree[v].secondMin = INF;
 
        tree[v].sum = val * (r - l);
        tree[v].pushSum = 0;
    }
 
    void doPushMinEq(int v, int l, int r, long long val) {
        if (tree[v].min >= val) {
            doPushEq(v, l, r, val);
        } else if (tree[v].max > val) {
            if (tree[v].secondMin == tree[v].max) {
                tree[v].secondMin = val;
            }
            tree[v].sum -= (tree[v].max - val) * tree[v].maxCnt;
            tree[v].max = val;
        }
    }
 
    void doPushMaxEq(int v, int l, int r, long long val) {
        if (tree[v].max <= val) {
            doPushEq(v, l, r, val);
        } else if (tree[v].min < val) {
            if (tree[v].secondMax == tree[v].min) {
                tree[v].secondMax = val;
            }
            tree[v].sum += (val - tree[v].min) * tree[v].minCnt;
            tree[v].min = val;
        }
    }
 
    void doPushSum(int v, int l, int r, long long val) {
        if (tree[v].min == tree[v].max) {
            doPushEq(v, l, r, tree[v].min + val);
        } else {
            tree[v].max += val;
            if (tree[v].secondMax != -INF) {
                tree[v].secondMax += val;
            }
 
            tree[v].min += val;
            if (tree[v].secondMin != INF) {
                tree[v].secondMin += val;
            }
 
            tree[v].sum += (r - l) * val;
            tree[v].pushSum += val;
        }
    }
 
    void pushToChildren(int v, int l, int r) {
        if (l + 1 == r) {
            return;
        }
        int mid = (r + l) / 2;
        if (tree[v].pushEq != -1) {
            doPushEq(2 * v, l, mid, tree[v].pushEq);
            doPushEq(2 * v + 1, mid, r, tree[v].pushEq);
            tree[v].pushEq = -1;
        } else {
            doPushSum(2 * v, l, mid, tree[v].pushSum);
            doPushSum(2 * v + 1, mid, r, tree[v].pushSum);
            tree[v].pushSum = 0;
 
            doPushMinEq(2 * v, l, mid, tree[v].max);
            doPushMinEq(2 * v + 1, mid, r, tree[v].max);
 
            doPushMaxEq(2 * v, l, mid, tree[v].min);
            doPushMaxEq(2 * v + 1, mid, r, tree[v].min);
        }
    }
 
    void updateFromChildren(int v) {
        tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
 
        tree[v].max = max(tree[2 * v].max, tree[2 * v + 1].max);
        tree[v].secondMax = max(tree[2 * v].secondMax, tree[2 * v + 1].secondMax);
        tree[v].maxCnt = 0;
        if (tree[2 * v].max == tree[v].max) {
            tree[v].maxCnt += tree[2 * v].maxCnt;
        } else {
            tree[v].secondMax = max(tree[v].secondMax, tree[2 * v].max);
        }
        if (tree[2 * v + 1].max == tree[v].max) {
            tree[v].maxCnt += tree[2 * v + 1].maxCnt;
        } else {
            tree[v].secondMax = max(tree[v].secondMax, tree[2 * v + 1].max);
        }
 
        tree[v].min = min(tree[2 * v].min, tree[2 * v + 1].min);
        tree[v].secondMin = min(tree[2 * v].secondMin, tree[2 * v + 1].secondMin);
        tree[v].minCnt = 0;
        if (tree[2 * v].min == tree[v].min) {
            tree[v].minCnt += tree[2 * v].minCnt;
        } else {
            tree[v].secondMin = min(tree[v].secondMin, tree[2 * v].min);
        }
        if (tree[2 * v + 1].min == tree[v].min) {
            tree[v].minCnt += tree[2 * v + 1].minCnt;
        } else {
            tree[v].secondMin = min(tree[v].secondMin, tree[2 * v + 1].min);
        }
    }
 
    void build(int v, int l, int r, const vector<ll>& inputArray) {
        tree[v].pushSum = 0;
        tree[v].pushEq = -1;
        if (l + 1 == r) {
            tree[v].max = inputArray[l];
            tree[v].secondMax = -INF;
            tree[v].maxCnt = 1;
 
            tree[v].min = inputArray[l];
            tree[v].secondMin = INF;
            tree[v].minCnt = 1;
 
            tree[v].sum = inputArray[l];
        } else {
            int mid = (r + l) / 2;
            build(2 * v, l, mid, inputArray);
            build(2 * v + 1, mid, r, inputArray);
            updateFromChildren(v);
        }
    }
 
    void build(const vector<ll>& inputArray) {
        n = inputArray.size();
        build(1, 0, n, inputArray);
    }
 
    void updateMinEq(int v, int l, int r, int ql, int qr, int val) {
        if (qr <= l || r <= ql || tree[v].max <= val) {
            return;
        }
        if (ql <= l && r <= qr && tree[v].secondMax < val) {
            doPushMinEq(v, l, r, val);
            return;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        updateMinEq(2 * v, l, mid, ql, qr, val);
        updateMinEq(2 * v + 1, mid, r, ql, qr, val);
        updateFromChildren(v);
    }
 
    void updateMinEq(int ql, int qr, int val) {
        updateMinEq(1, 0, n, ql, qr+1, val);
    }
 
    void updateMaxEq(int v, int l, int r, int ql, int qr, int val) {
        if (qr <= l || r <= ql || tree[v].min >= val) {
            return;
        }
        if (ql <= l && r <= qr && tree[v].secondMin > val) {
            doPushMaxEq(v, l, r, val);
            return;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        updateMaxEq(2 * v, l, mid, ql, qr, val);
        updateMaxEq(2 * v + 1, mid, r, ql, qr, val);
        updateFromChildren(v);
    }
 
    void updateMaxEq(int ql, int qr, int val) {
        updateMaxEq(1, 0, n, ql, qr+1, val);
    }
 
    void updateEq(int v, int l, int r, int ql, int qr, int val) {
        if (qr <= l || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            doPushEq(v, l, r, val);
            return;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        updateEq(2 * v, l, mid, ql, qr, val);
        updateEq(2 * v + 1, mid, r, ql, qr, val);
        updateFromChildren(v);
    }
 
    void updateEq(int ql, int qr, int val) {
        updateEq(1, 0, n, ql, qr+1, val);
    }
 
    void updatePlusEq(int v, int l, int r, int ql, int qr, int val) {
        if (qr <= l || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            doPushSum(v, l, r, val);
            return;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        updatePlusEq(2 * v, l, mid, ql, qr, val);
        updatePlusEq(2 * v + 1, mid, r, ql, qr, val);
        updateFromChildren(v);
    }
 
    void updatePlusEq(int ql, int qr, int val) {
        updatePlusEq(1, 0, n, ql, qr+1, val);
    }
 
    long long findSum(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return tree[v].sum;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        return findSum(2 * v, l, mid, ql, qr) + findSum(2 * v + 1, mid, r, ql, qr);
    }
 
    long long findSum(int ql, int qr) {
        return findSum(1, 0, n, ql, qr+1);
    }
 
    long long findMin(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return INF;
        }
        if (ql <= l && r <= qr) {
            return tree[v].min;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        return min(findMin(2 * v, l, mid, ql, qr), findMin(2 * v + 1, mid, r, ql, qr));
    }
 
    long long findMin(int ql, int qr) {
        return findMin(1, 0, n, ql, qr+1);
    }
 
    long long findMax(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return -INF;
        }
        if (ql <= l && r <= qr) {
            return tree[v].max;
        }
        pushToChildren(v, l, r);
        int mid = (r + l) / 2;
        return max(findMax(2 * v, l, mid, ql, qr), findMax(2 * v + 1, mid, r, ql, qr));
    }
 
    long long findMax(int ql, int qr) {
        return findMax(1, 0, n, ql, qr+1);
    }
};


const int sigma = 52;
struct Aho_Corasick
{
	bool marked;
	ll from;
	vector<Aho_Corasick*> D;
	bitset<sigma> under;
	Aho_Corasick* SuffLink;
	Aho_Corasick(ll x = -1,ll n = sigma)
	{
		marked = 0;
		under = 0;
		from = x;
		D = vector<Aho_Corasick*>(n,nullptr);
	}
	void insert(vector<ll> & s,ll p = 0)
	{
		if (p == s.size()) return;
		if (D[s[p]] == nullptr) D[s[p]] = new Aho_Corasick(s[p]);
		under[s[p]] = 1;
		D[s[p]]->insert(s,p+1);
	}
	void build()
	{
		queue<Aho_Corasick*> BFS;
		queue<Aho_Corasick*> PR;
		BFS.push(this);
		for (ll i = 0;i<D.size();i++)
		{
			if (D[i] == nullptr) D[i] = this;
		}
		while (!BFS.empty())
		{
			Aho_Corasick* v = BFS.front();
			BFS.pop();
			Aho_Corasick* pr = nullptr;
			if (!PR.empty())
			{
				pr = PR.front();
				PR.pop();
			}
			if (pr != nullptr && pr->from != -1)
			{
				v->SuffLink = pr->SuffLink->D[v->from];
			}
			else
			{
				v->SuffLink = this;
			}
			for (ll i = 0;i<D.size();i++)
			{
				if (v->under[i])
				{
					PR.push(v);
					BFS.push(v->D[i]);
				}
				else
				{
					v->D[i] = v->SuffLink->D[i];
				}
			}
		}
	}
	void mark()
	{
		if (marked) return;
		marked = 1;
		SuffLink->mark();
	}
};
ll disc_log(ll a,ll b,ll mod,ll len)
{
	if (b == 1) return len;
	ll H = sqrtl(mod)+1;
	ll c = binpow(a,H);
	vector<pair<ll,ll>> F,S;
	ll C = c;
	for (ll i = 1;i<=H;i++)
	{
		F.push_back({C,i});
		C = (C*c)%mod;
	}
	sort(all(F));
	ll B = 1;
	for (ll i = 0;i<=H;i++)
	{
		S.push_back({(b*B)%mod,i});
		B = (B*a)%mod;
	}
	sort(all(S));
	ll u = 0,v = 0;
	while (u < F.size() && v < S.size())
	{
		if (F[u].F == S[v].F)
		{
			ll x = (F[u].S*H-S[v].S)%len;
			return x;
		}
		if (F[u].F < S[v].F) u++;
		else v++;
	}
	return 1e18;
}
pair<vector<ll>,vector<ll>> sufarray(string s)
{
	s+='$';
	ll n = s.size();
	vector<ll> p(n),c(n);
	ll k = 0;
	{
		vector<pair<char,ll>> j;
		for (ll e = 0;e<n;e++)
		{
			j.push_back({s[e],e});
		}
		sort(j.begin(),j.end());
		for (ll e = 0;e<n;e++)
		{
			p[e] = j[e].second;
		}
		for (ll e = 1;e<n;e++)
		{
			c[p[e]] = c[p[e-1]]+1-(j[e].first==j[e-1].first);
		}
	}
	vector<pair<pair<ll,ll>,ll>> B(n);
	vector<pair<pair<ll,ll>,ll>> A(n);
	vector<ll> cnt(n);
	vector<ll> pos(n);
	while ((1 << k) < n)
	{ 
		for (ll e = 0;e<n;e++)
		{
			cnt[e] = 0;
			pos[e] = 0;
			p[e] = (p[e]-(1 << k)+n)%n;
			B[e] = {{c[p[e]],c[(p[e]+(1<<k))%n]},p[e]};
		}
		for (ll e = 0;e<n;e++)
		{
			cnt[c[p[e]]]++;
		}
		for (ll e = 1;e<n;e++)
		{
			pos[e] = pos[e-1]+cnt[e-1];
		}
		for (ll e = 0;e<n;e++)
		{
			A[pos[c[p[e]]]++] = B[e];
		}
		for (ll e = 0;e<n;e++)
		{
			p[e] = A[e].second;
		}
		c[p[0]] = 0;
		for (ll e = 1;e<n;e++)
		{
			c[p[e]] = c[p[e-1]]+1-(A[e].first == A[e-1].first);
		}
		k++;
	}
	vector<ll> lcp(n);
	k = 0;
	for (ll e = 0;e<n-1;e++)
	{
		ll pe = c[e];
		ll j = p[pe-1];
		while (s[e+k] == s[j+k]) k++;
		lcp[pe] = k;
		k = max(k-1,(ll)0);
	}
	p.erase(p.begin());
	lcp.erase(lcp.begin());
	return {p,lcp};
}
struct treap
{
	treap *l = nullptr,*r = nullptr;
	ll x,y,sz,sum;
	treap(ll nx,ll ny)
	{
		x = nx,y = ny,sz = 1,sum = nx;
	}
};
ll get(treap * t)
{
	return t == nullptr ? 0ll : t->sum;
}
ll cnt(treap * t)
{
	return t == nullptr ? 0ll : t->sz;
}
void update_cnt(treap * t)
{
	if (t == nullptr) return;
	t->sum = get(t->l)+get(t->r)+t->x;
	t->sz = cnt(t->l)+cnt(t->r)+1;
}
void split(treap *t,ll val,treap *&l, treap *&r)
{
	if (t == nullptr) l = r = nullptr;
	else if (t->x <= val)
	{
		split(t->r,val,t->r,r),l = t;
	}
	else
	{
		split(t->l,val,l,t->l),r = t;
	}
	update_cnt(t);
}
void merge(treap *& t,treap * l,treap * r)
{
	update_cnt(l);
	update_cnt(r);
	if (l == nullptr || r == nullptr) t = l != nullptr ? l : r;
	else if (l->y >= r->y)
	{
		merge(l->r,l->r,r),t = l;
	}
	else
	{
		merge(r->l,l,r->l),t = r;
	}
	update_cnt(t);
}
void insert(treap *& t,ll x,ll y = -1)
{
	if (y == -1) y = mt()%(ll)1e9;
	treap *R = nullptr;
	split(t,x,t,R);
	merge(t,t,new treap(x,y));
	merge(t,t,R);
}
void erase(treap *&t,ll x)
{
	treap *M,*R;
	split(t,x-1,t,M);
	treap *tmp;
	split(M,x,M,R);
	merge(t,t,M->l);
	merge(t,t,M->r);
	merge(t,t,R);
}
void print(treap * t)
{
	if (t == nullptr) return;
	cout<<"("<<t->x<<","<<t->sum<<","<<t->sz<<")"<<"{";
	print(t->l);
	print(t->r);
	cout<<"}";
}
const ll root = 3;
ll mod_pow(ll a, ll b, ll m = mod) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
void ntt(vector<ll> &a, bool invert) {
    ll n = a.size();
    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (ll len = 2; len <= n; len <<= 1) {
        ll wlen = mod_pow(root, (mod - 1) / len);
        if (invert) wlen = mod_pow(wlen, mod - 2); // inverse root
        for (ll i = 0; i < n; i += len) {
            ll w = 1;
            for (ll j = 0; j < len / 2; j++) {
                ll u = a[i + j];
                ll v = a[i + j + len / 2] * w % mod;
                a[i + j] = (u + v < mod) ? u + v : u + v - mod;
                a[i + j + len / 2] = (u - v >= 0) ? u - v : u - v + mod;
                w = w * wlen % mod;
            }
        }
    }
    if (invert) {
        ll n_inv = mod_pow(n, mod - 2);
        for (ll &x : a) x = x * n_inv % mod;
    }
}
vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
    vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n = 1;
    while (n < (ll)(a.size() + b.size())) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    for (ll i = 0; i < n; i++) fa[i] = fa[i] * fb[i] % mod;
    ntt(fa, true);
    return fa;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin>>t;
    
    while(t--){

    }
}