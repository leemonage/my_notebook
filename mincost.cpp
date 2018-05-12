/**
  *  expected flow with minimum cost O(VE + |flow| E logE)
  */

struct mincost {
    struct edge {
        int u, v;
        ll cap, flow, cost;

        edge() { }
        edge(int u, int v, ll c, ll cst) : u(u), v(v), cap(c), cost(cst), flow(0) { }
    };

    int n, s, t;
    vector<edge> E;
    vector< vector<int> > g;
    vector<char> used;

    mincost() { }

    mincost(int n, int s, int t) : n(n), s(s), t(t) {
        g.resize(n);
    }

    void add_edge(int u, int v, ll cap, ll cost) {
        edge e = edge(u, v, cap, cost);
        g[u].push_back(sz(E));
        E.push_back(e);
        e = edge(v, u, 0, -cost);
        g[v].push_back(sz(E));
        E.push_back(e);
    }

    bool dfs(int v) {
        used[v] = true;

        if (v == t)
            return true;

        for (auto to : g[v])
            if (E[to].flow < E[to].cap && !used[E[to].v]) {
                if (dfs(E[to].v))
                    return true;
            }

        return false;
    }

    ll work(int expected_flow) {
        bool run;
        vector<ll> D(n, INF * INF), phi;
        vector<int> pr(n);
        D[s] = 0;
        pr[s] = -1;

        do {
            run = false;

            for (int i = 0; i < sz(E); ++++i) {
                auto e = E[i];

                if (D[e.u] + e.cost < D[e.v]) {
                    D[e.v] = D[e.u] + e.cost;
                    pr[e.v] = i;
                    run = true;
                }
            }
        } while (run);

        phi = D;
        ll flow = 0, cost = 0;
        used.assign(n, false);

        for (; flow < expected_flow && dfs(s); ++flow) {
            vector<int> path;
            int v = t;

            for (; v != s; v = E[pr[v]].u) {
                ++E[pr[v]].flow;
                --E[pr[v] ^ 1].flow;
                cost += E[pr[v]].cost;
            }

            D.assign(n, INF * INF);
            set< pair<ll, int> > Q;
            Q.insert(make_pair(D[s] = 0, s));

            for (; !Q.empty(); ) {
                int v = Q.begin()->second;
                Q.erase(Q.begin());

                for (auto to : g[v]) {
                    auto e = E[to];

                    if (e.flow == e.cap)
                        continue;

                    if (D[v] + e.cost + phi[e.u] - phi[e.v] < D[e.v]) {
                        Q.erase(make_pair(D[e.v], e.v));
                        D[e.v] = D[v] + e.cost + phi[e.u] - phi[e.v];
                        pr[e.v] = to;
                        Q.insert(make_pair(D[e.v], e.v));
                    }
                }
            }

            for (int v = 0; v < n; ++v)
                phi[v] += D[v];

            used.assign(n, false);
        }

        if (flow != expected_flow)
            return -1;

        return cost;
    }
};
