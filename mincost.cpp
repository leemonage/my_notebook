/**
  *  TODO: find mincost flow
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

    ll get() {
        //
    }
};
