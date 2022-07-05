class DSU {
public:
    vector<int> parent, sz;
    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);

    }

    int find_set(int a) {
        if (a == parent[a]) {
            return a;
        }

        return parent[a] = find_set(parent[a]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
        }
    }
};