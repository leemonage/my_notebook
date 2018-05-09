struct dsu {
    int n;
    vector<int> p, w;

    dsu() { }

    dsu(int n) : n(n) {
        w.resize(n, 1);
        p.resize(n);

        forn (i, n)
            p[i] = i;
    }

    int getp(int v) { return v == p[v] ? v : p[v] = getp(p[v]); }

    bool join(int u, int v) {
        u = getp(u);
        v = getp(v);

        if (u == v)
            return false;

        if (w[u] < w[v])
            swap(u, v);

        p[v] = u;
        w[u] += (w[u] == w[v]);
        return true;
    }
};
