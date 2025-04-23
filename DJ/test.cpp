#include <algorithm>
#include <any>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
using namespace std;


template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  // os << "[";
  for (size_t i = 0; i < v.size(); ++i) {
    os << v[i]; // Requires T to be print64_table (supports <<)
    os << " ";
  }
  os << "\n";
  return os;
}

template <typename T> ostream &operator<<(ostream &os, const set<T> &s) {
  // cout << size(s) << "\n";
  for (auto x : s) {
    os << x << ' '; // Requires T to be print64_table (supports <<)
  }
  os << "\n";
  return os;
}

struct GoRequest {
  int64_t from;
  int64_t to;
  int64_t final_dist;
};

class RequestComparator {
public:
  bool operator()(const GoRequest &r1, const GoRequest &r2) {
    return r1.final_dist > r2.final_dist;
  }
};

class Graph {
public:
  int64_t n;
  vector<vector<int64_t>> gotos;
  map<pair<int64_t, int64_t>, int64_t> length;
  Graph(int64_t size) {
    n = size;
    gotos = vector<vector<int64_t>>(n + 1);
  }
  void AddEdge(int64_t a, int64_t b, int64_t l) {
    gotos[a].push_back(b);
    gotos[b].push_back(a);
    length[pair(a, b)] = l;
    length[pair(b, a)] = l;
  }
  void AddOriented(int64_t a, int64_t b, int64_t l) {
    gotos[a].push_back(b);
    length[pair(a, b)] = l;
  }
};

class BFS : public Graph {
public:
  vector<int64_t> dist;
  vector<int64_t> parent;
  BFS(int64_t size) : Graph(size) {
    dist = vector<int64_t>(n + 1, -1);
    parent = vector<int64_t>(n + 1, -1);
  }

  void bfs(int64_t node) {
    priority_queue<GoRequest, vector<GoRequest>, RequestComparator> q;
    // first = vertex, second = dist
    dist[node] = 0; // this must be deleted if graph has node <-> node edge
    q.push({int64_t(0), node, int64_t(0)});
    while (size(q) > 0) {
      GoRequest p = q.top();
      q.pop();
      if (dist[p.to] > 0) {
        continue;
      }
      int64_t d = p.final_dist;
      dist[p.to] = d;
      parent[p.to] = p.from;
      for (int64_t x : gotos[p.to]) {
        if (dist[x] == -1) {
          q.push({p.to, x, d + length[pair(p.to, x)]});
        }
      }
    }
  }
};

int main() {
  int64_t n, m;
  cin >> n >> m;
  BFS g(n);

  for (int64_t i = 0; i < m; ++i) {
    int64_t a, b, l;
    cin >> a >> b >> l;
    if (a == b) {
      continue;
    }
    g.AddEdge(a, b, l);
  }
  int64_t s, f;
  cin >> s >> f;

  g.bfs(s);
  cout << g.dist[f] << "\n";
  if (g.dist[f] != -1) {
    vector<int> path;
    int x = f;
    while (x != 0) {
      path.push_back(x);
      x = g.parent[x];
    }
    cout << size(path) << "\n";
    for (int i = size(path) - 1; i >= 0; --i) {
      cout << path[i] << ' ';
    }
  }
}
