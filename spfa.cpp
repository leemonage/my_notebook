/* using ll = long long; */

struct edge {
    int v, u;
    ll w;
    edge(int v, int u, ll w) : v(v), u(u), w(w) { }
};

vector<ll> spfa(int s) {
    vector<ll> D(n, +INF);
    vector<char> inQ(n, false);
    D[s] = 0;
    std::queue<int> Q;
    Q.push(s);
    inQ[s] = true;
    
    while (!Q.empty()) {
        auto v = Q.front();
        inQ[v] = false;
        Q.pop();
        
        for (auto e : g[v])
            if (D[e.v] + e.w < D[e.u]) {
                D[e.u] = D[e.v] + e.w;
                if (!inQ[e.u]) Q.push(e.u), inQ[e.u] = true;
            }
    }
    
    return D;
}

