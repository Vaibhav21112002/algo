//<-------------------SEGMENT TREES-------------->
template <typename T>
class segment {
    int n;
    vector<T> artree, tree;
public:

    void buildTree(int node, int st, int end) {
        if (st == end) {
            tree[node] = artree[st];
            return ;
        }
 
        int mid = (st + end) / 2;
        buildTree(2 * node, st, mid);
        buildTree(2 * node + 1, mid + 1, end);
 
        tree[node] = (tree[2 * node] + tree[2 * node + 1]);
    }

    segment(){
        ;
    }

    segment(vector<T>& v) : n(v.size()), artree(v){
        tree.resize(4 * n + 4);
        buildTree(1,0,n-1);
    }
    
 
 
    T query(int node, int st, int end, int l, int r) {
        if (st > r || end < l) {
            return 0;
        }
 
        if (l <= st && end <= r) {
            return tree[node];
        }
 
        int mid = (st + end) / 2;
        T q1 = query(2 * node, st, mid, l, r);
        T q2 = query(2 * node + 1 , mid + 1, end, l, r);
 
        return (q1 + q2);
    }
 
    void update(int node, int st, int end , int idx, T val) {
        if (st == end) {
            artree[st] = val;
            tree[node] = val;
            return;
        }
 
        T mid = (st + end) / 2;
        if (idx <= mid) {
            update(2 * node, st, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
 
        tree[node] =(tree[2 * node] + tree[2 * node + 1]);
    }
};
 
//<----------------SEGMENT TREES ENDS--------->