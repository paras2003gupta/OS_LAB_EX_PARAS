#include<bits/stdc++.h>

using namespace std;

class DisjointSet {
public:
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int uRoot = find(u);
        int vRoot = find(v);

        if (uRoot == vRoot) return;

        if (rank[uRoot] > rank[vRoot]) {
            parent[vRoot] = uRoot;
        } else if (rank[uRoot] < rank[vRoot]) {
            parent[uRoot] = vRoot;
        } else {
            parent[vRoot] = uRoot;
            rank[uRoot]++;
        }
    }
};

vector<pair<int, int>> prim(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<pair<int, int>> mst;
    vector<bool> visited(n, false);
    DisjointSet ds(n);

    visited[0] = true;

    while (mst.size() < n - 1) {
        int minWeight = INT_MAX;
        pair<int, int> minEdge;

        for (int u = 0; u < n; ++u) {
            if (visited[u]) {
                for (int v = 0; v < n; ++v) {
                    if (!visited[v] && graph[u][v] < minWeight) {
                        minWeight = graph[u][v];
                        minEdge = {u, v};
                    }
                }
            }
        }

        int u = minEdge.first;
        int v = minEdge.second;
        mst.push_back(minEdge);
        visited[v] = true;
        ds.unionSets(u, v);
    }

    return mst;
}

int main() {
    vector<vector<int>> graph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    vector<pair<int, int>> mst = prim(graph);

    int totalWeight = 0;
    cout << "Minimum Spanning Tree Edges:" << endl;
    for (const auto& edge : mst) {
        totalWeight += graph[edge.first][edge.second];
        cout << edge.first << " - " << edge.second << " : " << graph[edge.first][edge.second] << endl;
    }

    cout << "Total weight of MST: " << totalWeight << endl;

    return 0;
}
