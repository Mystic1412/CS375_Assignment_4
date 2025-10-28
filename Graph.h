#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Graph{
public:
    int n;
    vector<vector<int>> adj;
    bool directed;

    Graph(int node, bool dir = false);
    void addEdge(int u, int v);
    void printGraph() const;
    bool hasCycleUndirected();
};


#endif