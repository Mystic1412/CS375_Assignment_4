#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Graph{
public:
    int n;
    vector<vector<int>> adj;
    bool directed;

    Graph(): n(0), directed(false){}
    void addEdge(int u, int v);
    void printGraph(ostream& out) const;
    bool hasCycleUndirected(ostream& out);

    void dfsTopologicalSort(ofstream& out);

    bool isBipartite(ofstream& out);
    void loadFile(const string& filename, bool hasLabels);
};


#endif