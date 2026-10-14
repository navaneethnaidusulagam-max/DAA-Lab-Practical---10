#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int src, dest, weight;
};

struct DisjointSets {
    vector<int> parent, rank;

    DisjointSets(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]); 
        return parent[u];
    }

    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else {
            parent[v] = u;
            rank[u]++;
        }
    }
};

void KruskalMST(vector<Edge>& edges, int V) {
    vector<Edge> result; 

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    DisjointSets ds(V);

    for (auto& edge : edges) {
        int u = ds.find(edge.src);
        int v = ds.find(edge.dest);

        if (u != v) {
            result.push_back(edge);
            ds.unite(u, v);
        }
    }

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (auto& e : result) {
        cout << e.src << " - " << e.dest << " : " << e.weight << endl;
    }
}

int main() {
    int V = 4; 
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    KruskalMST(edges, V);

    return 0;
}
