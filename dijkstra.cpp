#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>

using namespace std;

const int INF = 0x7FFFFFFF;

class Edge {
 public:
  Edge() {}
  Edge(const string& source, const string& target, const int dist)
      : source_(source), target_(target), dist_(dist) {}
  string source() const { return source_; }
  string target() const { return target_; }
  int distance() const { return dist_; }

 private:
  const string source_;
  const string target_;
  int dist_;
};

class Graph {
 public:
  void AddEdge(const string& a, const string& b, int dist) {
    adj_[a].push_back(Edge(a, b, dist));
    adj_[b].push_back(Edge(b, a, dist));
    nodes_.insert(a);
    nodes_.insert(b);
  }

  const vector<Edge>& adjacents(const string& a) const {
    return adj_.find(a)->second;
  }

  const set<string>& nodes() const { return nodes_; }

  map<string, vector<Edge>> adj_;
  set<string> nodes_;
};

stack<string> dijkstra(const Graph& graph, const string& src,
                       const string& target) {
  set<string> unvisited;
  map<string, int> dist;
  map<string, string> route;
  for (const string& node : graph.nodes()) {
    if (node != src) {
      unvisited.insert(node);
      dist[node] = INF;
    }
  }
  dist[src] = 0;
  route[src] = src;
  string current_node = src;

  while (!unvisited.empty()) {
    for (const auto& edge : graph.adjacents(current_node)) {
      if (!unvisited.count(edge.target())) continue;
      int candidate_dist = dist[current_node] + edge.distance();
      if (candidate_dist < dist[edge.target()]) {
        dist[edge.target()] = candidate_dist;
        route[edge.target()] = current_node;
      }
    }
    unvisited.erase(current_node);
    if (current_node == target) break;

    int min_dist = INF;
    for (const auto& node : unvisited) {
      if (dist[node] < min_dist) {
        min_dist = dist[node];
        current_node = node;
      }
    }
    if (min_dist == INF) break;
  }

  stack<string> path;
  for (string node = target; node != src && node != ""; node = route[node]) {
    path.push(node);
  }
  path.push(src);

  return path;
}

int main() {
  Graph g;
  g.AddEdge("A", "B", 5);
  g.AddEdge("A", "C", 3);
  g.AddEdge("A", "D", 4);
  g.AddEdge("B", "D", 1);
  g.AddEdge("B", "F", 3);
  g.AddEdge("B", "G", 1);
  g.AddEdge("C", "D", 2);
  g.AddEdge("D", "E", 2);
  g.AddEdge("E", "F", 3);
  g.AddEdge("E", "G", 1);
  g.AddEdge("F", "G", 4);

  for (const auto& edge : g.adjacents("A")) {
    cout << edge.source() << " " << edge.target() << " " << edge.distance()
         << endl;
  }

  stack<string> path = dijkstra(g, "C", "G");
  while (!path.empty()) {
    cout << path.top() << " ";
    path.pop();
  }
  cout << endl;

  return 0;
}
