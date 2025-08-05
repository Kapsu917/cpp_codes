#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>
#include <tuple>

using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

struct SegTree {
    int n_elem;
    vector<long long> tree;
    vector<bool> lazy;
    const vector<int>& p;

    SegTree(const vector<int>& points) : p(points) {
        n_elem = p.size() > 1 ? p.size() - 1 : 0;
        if (n_elem <= 0) return;
        tree.resize(4 * n_elem, 0);
        lazy.resize(4 * n_elem, false);
    }

    void push(int node, int start, int end) {
        if (lazy[node]) {
            tree[node] = p[end + 1] - p[start];
            if (start != end) {
                lazy[2 * node] = true;
                lazy[2 * node + 1] = true;
            }
            lazy[node] = false;
        }
    }

    void update(int l, int r, int node, int start, int end) {
        if (n_elem <= 0) return;
        push(node, start, end);
        if (start > end || start > r || end < l) {
            return;
        }
        if (l <= start && end <= r) {
            lazy[node] = true;
            push(node, start, end);
            return;
        }
        int mid = start + (end - start) / 2;
        update(l, r, 2 * node, start, mid);
        update(l, r, 2 * node + 1, mid + 1, end);
        push(2 * node, start, mid);
        push(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    long long query(int l, int r, int node, int start, int end) {
        if (n_elem <= 0) return 0;
        if (start > end || start > r || end < l) {
            return 0;
        }
        push(node, start, end);
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        long long p1 = query(l, r, 2 * node, start, mid);
        long long p2 = query(l, r, 2 * node + 1, mid + 1, end);
        return p1 + p2;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<tuple<int, int, int>> pairs(n);
    set<int> points_set;
    for (int i = 0; i < n; ++i) {
        cin >> get<0>(pairs[i]) >> get<1>(pairs[i]);
        get<2>(pairs[i]) = i + 1;
        points_set.insert(get<0>(pairs[i]));
        points_set.insert(get<1>(pairs[i]));
    }

    vector<int> points(points_set.begin(), points_set.end());
    auto get_idx = [&](int val) {
        return lower_bound(points.begin(), points.end(), val) - points.begin();
    };

    DSU dsu(points.size());
    SegTree st(points);

    vector<bool> used(n, false);
    vector<int> result_indices;

    for (int k = 0; k < n; ++k) {
        long long max_gain = 0;
        int best_edge_idx = -1;

        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;

            int u, v, original_idx;
            tie(u, v, original_idx) = pairs[i];

            int u_idx = get_idx(u);
            int v_idx = get_idx(v);

            if (dsu.find(u_idx) == dsu.find(v_idx)) {
                continue;
            }

            long long covered_len = st.query(u_idx, v_idx - 1, 1, 0, st.n_elem - 1);
            long long current_gain = (long long)v - u - covered_len;

            if (current_gain > max_gain) {
                max_gain = current_gain;
                best_edge_idx = i;
            }
        }

        if (best_edge_idx == -1) {
            break;
        }

        used[best_edge_idx] = true;
        int u, v, original_idx;
        tie(u, v, original_idx) = pairs[best_edge_idx];
        result_indices.push_back(original_idx);

        int u_idx = get_idx(u);
        int v_idx = get_idx(v);

        dsu.unite(u_idx, v_idx);
        st.update(u_idx, v_idx - 1, 1, 0, st.n_elem - 1);
    }

    cout << result_indices.size() << "\n";
    for (int i = 0; i < result_indices.size(); ++i) {
        cout << result_indices[i] << (i == result_indices.size() - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

