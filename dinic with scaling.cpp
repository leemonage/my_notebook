/**
  * maxflow O(V E logC)
  */

struct flow_network {
    struct edge {
        int u, v;
        ll cap, flow;

        edge() { }
        edge(int u, int v, ll c, ll f = 0) : u(u), v(v), cap(c), flow(f) { }
    };

    int n, s, t;
    vector<edge> E;
    vector< vector<int> > g;
    vector<int> Q, D, ptr;

    flow_network() { }

    flow_network(int n, int s, int t) : n(n), s(s), t(t) {
        Q.resize(n);
        D.resize(n, INF);
        g.resize(n);
    }

    void add_edge(int u, int v, ll cap) {
        edge e = edge(u, v, cap);
        g[u].push_back(sz(E));
        E.push_back(e);
        e = edge(v, u, 0);
        g[v].push_back(sz(E));
        E.push_back(e);
    }

    bool bfs(ll T) {
        int qh = 0, qt = 0;
        Q[qt++] = s;
        D.assign(n, INF);
        D[s] = 0;

        while (qh < qt && D[t] == INF) {
            int v = Q[qh++];

            for (auto to : g[v])
                if (D[E[to].v] == INF && E[to].cap - E[to].flow >= T) {
                    D[E[to].v] = D[v] + 1;
                    Q[qt++] = E[to].v;
                }
        }

        return D[t] != INF;
    }

    ll dfs(int v, ll T) {
        if (v == t)
            return T;

        for (; ptr[v] < sz(g[v]); ++ptr[v]) {
            int id = g[v][ptr[v]];

            if (D[E[id].v] == D[v] + 1 && E[id].cap - E[id].flow >= T) {
                ll cur = dfs(E[id].v, T);
                E[id].flow += cur;
                E[id ^ 1].flow -= cur;
                
                if (cur)
                    return cur;
            }
        }

        return 0;
    }

    ll dinic() {
        ll flow = 0;

        for (ll T = (1ll << 31); T > 0; T >>= 1)
            for (; bfs(T); ) {
                ptr.assign(n, 0);

                while (ll cur = dfs(s, T))
                    flow += T;
            }

        return flow;
    }
};
