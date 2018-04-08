struct _node {
    int key, val, res;
    ll pr;
    _node* left;
    _node* right;

    _node() : left(nullptr), right(nullptr) { pr = (rand() ^ (rand() << 16)); }
    _node(int k, int v)
        : key(k), val(v), res(v), left(nullptr), right(nullptr) { pr = (rand() ^ (rand() << 16)); }
};

using pnode = _node*;

class treap {
private:
    pnode root;

    int getres(pnode t) {
        if (t == nullptr)
            return 0;

        return t->res;
    }

    void upd(pnode& t) {
        if (t == nullptr)
            return ;

        t->res = max({getres(t->left), t->val, getres(t->right)});
    }

    void split(int k, pnode t, pnode& l, pnode& r) {
        if (t == nullptr) {
            l = r = nullptr;
            return ;
        }

        if (t->key <= k) {
            split(k, t->right, t->right, r);
            upd(l = t);
        } else {
            split(k, t->left, l, t->left);
            upd(r = t);
        }
    }

    pnode merge(pnode l, pnode r) {
        if (l == nullptr)
            return r;

        if (r == nullptr)
            return l;

        if (l->pr > r->pr) {
            l->right = merge(l->right, r);
            upd(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            upd(r);
            return r;
        }
    }

public:
    treap() { root = nullptr; }

    void insert(int k, int x) { /* */ }

    int get(int k) { /* */ }
};
