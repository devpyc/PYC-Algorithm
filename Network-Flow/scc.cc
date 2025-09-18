#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> discovered, sccId;
vector<bool> finished;
stack<int> st;
int vertexCounter, sccCounter;

int scc(int here) {
    int ret = discovered[here] = vertexCounter++;
    st.push(here);

    for(int there : adj[here]) {
        if(discovered[there] == -1)
            ret = min(ret, scc(there));
        else if(!finished[there])
            ret = min(ret, discovered[there]);
    }

    if(ret == discovered[here]) {
        while(true) {
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            finished[t] = true;
            if(t == here) break;
        }
        sccCounter++;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int v, e;
    cin >> v >> e;
    
    adj.resize(v);
    discovered.assign(v, -1);
    finished.assign(v, false);
    sccId.resize(v);
    vertexCounter = sccCounter = 0;

    while(e--) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    for(int i = 0; i < v; i++)
        if(discovered[i] == -1)
            scc(i);

    return 0;
}