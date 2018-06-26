struct suffarray {
    int n;
    vector<int> s, c, arr, pos, lcp;
    vector< pair< pair<int, int>, int> > p;
    vector< vector< pair< pair<int, int>, int> > > buckets;

    suffarray() { }

    suffarray(const string& str) {
        n = sz(str) + 1;
        s.resize(n);
        arr.resize(n);

        for (int i = 0; i < n - 1; ++i)
            s[i] = str[i] - 'a' + 1;

        s[n - 1] = 0;
        c.resize(2 * n);
        p.resize(2 * n);
        build_array();
        build_lcp();
    }

    void BOOM(int step) { // ahah
        if (step == 1)
            forn (i, n)
                swap(p[i].first.first, p[i].first.second);

        int N = 0;

        forn (i, n)
            N = max(N, p[i].first.first + 1);

        buckets.clear();
        buckets.resize(N);

        forn (i, n)
            buckets[p[i].first.first].emplace_back(p[i]);

        int k = 0;

        forn (i, N)
            for (auto j : buckets[i])
                p[k++] = j;

        if (step == 1)
            forn (i, n)
                swap(p[i].first.first, p[i].first.second);
    }

    void build_array() {
        for (int i = 0; i < n; ++i)
            c[i] = s[i];

        for (int h = 0, cnt = 0; cnt < n; ++h) {
            for (int i = 0; i < n; ++i)
                p[i] = make_pair(make_pair(c[i], c[i + (1 << h)]), i);

            BOOM(1);
            BOOM(2);
            cnt = 0;

            for (int i = 0; i < n; ++i) {
                c[p[i].second] = cnt;
                cnt += p[i].first != p[i + 1].first;
            }
        }

        for (int i = 0; i < n; ++i)
            arr[c[i]] = i;
    }

    void build_lcp() {
        pos.resize(n);
        lcp.resize(n);

        for (int i = 0; i < n; ++i)
            pos[arr[i]] = i;

        int k = 0;

        for (int i = 0; i < n; ++i) {
            k = max(0, k - 1);

            if (pos[i] == n - 1) {
                lcp[pos[i]] = -1;
            } else {
                int j = arr[pos[i] + 1];
                for (; max(i, j) + k < n && s[i + k] == s[j + k]; ++k);
                lcp[pos[i]] = k;
            }
        }
    }
};
