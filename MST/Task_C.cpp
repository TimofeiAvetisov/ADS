struct Edge {
    int from, to, weight;
};

vector<Edge> edges;

sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
    return a.weight < b.weight;
});

for (auto [a, b, w] : edges) {
    if (p(a) != p(b)) {
        unite(a, b);
    }
}

int p[maxn], s[maxn];

int leader(int v) {
    return (p[v] == v) ? v : p[v] = leader(p[v]);
}

void unite(int a, int b) {
    a = leader(a), b = leader(b);
    if (s[a] > s[b])
        swap(a, b);
    s[b] += s[a];
    p[a] = b;
}

void init(n) {
    for (int i = 0; i < n; i++)
        p[i] = i, s[i] = 1;
}