#include <chrono>
#include "Graph.h"
using namespace std;
using namespace chrono;

int main(){
    ofstream outfile("Q6_output.txt");
    if(!outfile.is_open()){
        cerr<<"Error: Could not open output file.\n";
        return 1;
    }
    Graph G(11, false);
    G.addEdge(0,1);
    G.addEdge(0,2);
    G.addEdge(1,3);
    G.addEdge(1,4);
    G.addEdge(2,5);
    G.addEdge(2,6);
    G.addEdge(3,7);
    G.addEdge(4,7);
    G.addEdge(5,7);
    G.addEdge(6,7);
    G.addEdge(6,8);
    G.addEdge(6,9);
    G.addEdge(7,10);
    G.addEdge(8,10);

    outfile<<"Adjacency LIst:\n";
    for(int i=0; i<G.n; i++){
        outfile<<i+1<<": ";
        for(int j=0; j<(int)G.adj[i].size(); j++){
            outfile<<G.adj[i][j] +1<<" ";
        }
        outfile<<"\n";
    }
    outfile<<"\n";
    auto start = high_resolution_clock::now();
    G.isBipartite(outfile);
    auto end = high_resolution_clock::now();
    outfile<<"\nRuntime: "<<duration_cast<nanoseconds>(end-start).count()<<" ns\n";

    outfile.close();
    return 0;

}