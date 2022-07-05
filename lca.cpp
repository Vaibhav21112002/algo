class LCA {
    int n;
    vector<int> h, p;
    vector<vector<int>> adj, pr;
    vector<int> in, out;
    int timer;
    void dfs(int u, int v, vector<vector<int>>& adj, int ht = 0) {
        h[u] = ht;
        in[u] = ++timer;
        for (auto i : adj[u]) {
            if (i != v) {
                p[i] = u;
                dfs(i, u, adj, ht + 1);
            }
        }
        out[u] = ++timer;
    }
public:

    LCA(int _n, vector<vector<int>>&v): n(_n), adj(v) {
        timer = 0;
        h.assign(n + 1, 0);
        p.assign(n + 1, -1);
        in.assign(n + 1, 0);
        out.assign(n + 1, 0);
        dfs(1, -1, adj);
        int mx = INT_MIN;
        for (auto i : h)
            mx = max(mx, i);
        int mxN = 32 - __builtin_clz(mx);
        pr.resize(mxN, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            pr[0][i] = p[i];
        }
        for (int i = 1; i < mxN; i++) {
            for (int j = 1; j <= n; j++) {
                if (h[j] - (1 << i) < 0) {
                    pr[i][j] = -1;
                } else {
                    pr[i][j] = pr[i - 1][pr[i - 1][j]];
                }
            }
        }
    }

    int get(int x, int k) {
        if (k > h[x]) {
            return -1;
        }
        int ans = x;
        while (k) {
            int up = 32 - __builtin_clz(k) - 1;
            ans = pr[up][ans];
            k -= (1 << up);
        }
        return ans;
    }

    bool isAncestor(int a, int b) {
        return (in[a] < in[b] and out[b] < out[a]);
    }

    int lca(int a, int b) {
        if (a == b) {
            return a;
        }

        if (h[a] > h[b]) {
            swap(a, b);
        }

        b = get(b, h[b] - h[a]);
        if (a == b) {
            return a;
        }
        int l = 0, r = h[a];
        int ans;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (isAncestor(get(b, h[b] - mid), b) && isAncestor(get(b, h[b] - mid), a)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }

        }
        return get(b, h[b] - ans);
    }
};