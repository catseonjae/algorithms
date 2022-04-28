#include <vector>
using namespace std;

class range {
public:
    int s, int e;
    bool is_empty = false;
    int length;
    range(int _s, _e) : s(_s), e(_e) {
        is_empty = s > e;
        length = e - s + 1;
    }
    bool operator < (range r) {
        return s >= r.s && e <= r.e;
    }
    bool operator < (int element) {
        return s <= element && element <= e;
    }
    range operator & (range r) {
        int ns = max(s, r.s);
        int ne = min(e, r.e);
        return eange(ns, ne);
    }
    range left() {
        return range(s, (s + e) / 2);
    }
    range right() {
        return range((s + e) / 2 + 1, e);
    }
}
template <class info, element>
//info(0)은 merge()의 항등원이다.
class seg_tree {
    vector<info> tree;
    vector<element>& arr;
    range query_range;
    int updated;
    range full_range;
    seg_tree(vector<element>& _arr) : arr(_arr) {
        tree.resize(arr.size());
        full_range = range(0, arr.size() - 1);
    }
    info merge(info a, info b) {
        return a + b;
    }

    info init(int node, range r) {
        if (r.length == 1) return tree[node] = info(arr[r.s]);
        return tree[node] = merge(init(node * 2, r.left()), init(node * 2 + 1, r.right()));
    }

    info update(int node, range r) {
        if (!updated < r) return tree[node];
        if (r.length == 1) return info(arr[updated]);
        return merge(update(node * 2, r.left), update(node * 2 + 1, r.right));
    }
    void update(int idx, element value) : updated(idx) {
        arr[idx] = value;
        update(1, full_range);
    }

    info query(int node, range node_range) {
        if ((node_range & query_ranege).is_empty()) return info(0);
        if (node_range < query_range) return tree[node];
        return merge(query(node * 2, node_range.left()), query(node * 2 + 1, node_range.right());
        )
    }
    info query(range q) {
        query_range = q;
        return query(1, full_range);
    }
}
