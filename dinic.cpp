/**
  *  maxflow O(V^2 E)
  */

using ll = long long;

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

    bool bfs() {
        int qh = 0, qt = 0;
        Q[qt++] = s;
        D.assign(n, INF);
        D[s] = 0;

        while (qh < qt && D[t] == INF) {
            int v = Q[qh++];

            for (auto to : g[v])
                if (D[E[to].v] == INF && E[to].flow < E[to].cap) {
                    D[E[to].v] = D[v] + 1;
                    Q[qt++] = E[to].v;
                }
        }

        return D[t] != INF;
    }

    ll dfs(int v, ll R) {
        if (v == t)
            return R;

        if (R == 0)
            return 0;

        for (; ptr[v] < sz(g[v]); ++ptr[v]) {
            int id = g[v][ptr[v]];

            if (D[E[id].v] == D[v] + 1) {
                ll cur = dfs(E[id].v, min(R, E[id].cap - E[id].flow));
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

        for (; bfs(); ) {
            ll cur;
            ptr.assign(n, 0);

            while (cur = dfs(s, INF * INF))
                flow += cur;
        }

        return flow;
    }
};
