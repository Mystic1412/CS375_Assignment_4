#include <chrono>
#include <fstream>
#include "Graph.h"
using namespace std;
using namespace chrono;

int main(){
    ofstream outfile("Q5b_output.txt");
    if(!outfile.is_open()){
        cerr<<"Error: Could not open output file.\n";
        return 1;
    }

    Graph G(8,true);
    G.addEdge(0, 1);
    G.addEdge(0, 3);
    G.addEdge(0, 6);
    G.addEdge(1, 2);
    G.addEdge(1, 3);
    G.addEdge(1, 6);
    G.addEdge(3, 7);
    G.addEdge(4, 1);
    G.addEdge(4, 2);
    G.addEdge(5, 1);
    G.addEdge(5, 3);
    G.addEdge(5, 4);
    G.addEdge(6, 2);

    outfile<<"Adjacency List:\n";
    for(int i=0; i<G.n;i++){
        outfile<<i+1<<": ";
        for(int j=0; j<(int)G.adj[i].size(); j++){
            outfile<<G.adj[i][j]+1<<" ";
        }
        outfile<<"\n";
    }
    outfile<<"\n";
    auto start = high_resolution_clock::now();
    G.dfsTopologicalSort(outfile);
    auto end = high_resolution_clock::now();

    outfile<<"\nTime complexity: O(V+E)\nRuntime: "<<duration_cast<nanoseconds>(end-start).count()<<" ns\n";
    outfile.close();
    return 0;
}