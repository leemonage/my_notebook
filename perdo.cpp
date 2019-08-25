struct node {
    int l, r, sum;
    node* ls;
    node* rs;
    node() = default;
    node(int l, int r) : l(l), r(r), sum(0), ls(nullptr), rs(nullptr) { }
    node(int l, int r, int x) : l(l), r(r), sum(x), ls(nullptr), rs(nullptr) { }
};

struct segtree {
    int n;
    vector<node*> T;

    node* build(int l, int r) {
        if (l == r) return new node(l, r);
        auto m = (l + r) / 2;
        auto res = new node(l, r);
        res->ls = build(l, m);
        res->rs = build(m + 1, r);
        return res;
    }

    segtree() = default;
    segtree(int n) : n(n) { T.emplace_back(build(0, n - 1)); }

    int get(node* t, int lq, int rq) {
        if (t->r < lq || t->r < lq) return 0;
        if (lq <= t->l && t->r <= rq) return t->sum;
        auto m = (t->l + t->r) / 2;
        return get(t->ls, lq, rq) + get(t->rs, lq, rq);
    }

    node* upd(node* t, int i, int x) {
        if (t->l == t->r) return new node(i, i, t->sum + x);
        auto m = (t->l + t->r) / 2;
        auto res = new node(t->l, t->r);
        res->ls = (i <= m ? upd(t->ls, i, x) : t->ls);
        res->rs = (i > m ? upd(t->rs, i, x) : t->rs);
        res->sum = res->ls->sum + res->rs->sum;
        return res;
    }

    int get(int ver, int lq, int rq) { return get(T[ver + 1], lq, rq); }
    void upd(int i, int x) { T.emplace_back(upd(T.back(), i, x)); }
};
