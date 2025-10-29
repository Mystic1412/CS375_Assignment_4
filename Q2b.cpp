#include <chrono>
#include "Graph.h"
#include <fstream>
using namespace std;
using namespace chrono;


int main(){
    ofstream outfile("Q2_output.txt");
    if(!outfile.is_open()){
        cerr<<"Error: Could not open output file.\n";
        return 1;
    }

    Graph G1(6, false);
    G1.addEdge(0,1); //X1 to Y1
    G1.addEdge(0,3); //X1 to Y2
    G1.addEdge(1,2); //Y1 to X3
    G1.addEdge(1,4); //Y1 to X2
    G1.addEdge(2,5); //X3 to Y3
    G1.addEdge(5,4); //Y3 to X2
    G1.addEdge(4,3); //X2 to Y2


    outfile<<"Graph 1\nAdjacency list:\n";
    for(int i=0; i<G1.n; i++){
        outfile << i<< ": ";
        for(int j=0; j<(int)G1.adj[i].size(); j++){
            outfile<<G1.adj[i][j]<<" ";
        }
        outfile<<"\n";
    }

    auto startG1 = high_resolution_clock::now();
    bool hasCycleG1 = G1.hasCycleUndirected(outfile);
    auto endG1 = high_resolution_clock::now();

    if(hasCycleG1){
        outfile<<"\nGraph is cyclic\n";

    }else{
        outfile<<"\nGraph is acyclic\n";
    }

    outfile<<"Run time: "<<duration_cast<nanoseconds>(endG1-startG1).count()<<"ns\n";



    Graph G2(4,false);
    G2.addEdge(0,1); //a to b
    G2.addEdge(0,2); //a to c
    G2.addEdge(0,3); //a to d
    G2.addEdge(1,3); //b to d
    G2.addEdge(2,3); //c to d
    G2.addEdge(1,2); //b to c

    outfile<<"\nGraph 2\nAdjacency list:"<<endl;
    for(int i=0; i<G2.n; i++){
        outfile << i<< ": ";
        for(int j=0; j<(int)G2.adj[i].size(); j++){
            outfile<<G1.adj[i][j]<<" ";
        }
        outfile<<"\n";
    }

    auto startG2 = high_resolution_clock::now();
    bool hasCycleG2 = G2.hasCycleUndirected(outfile);
    auto endG2 = high_resolution_clock::now();

    if(hasCycleG2){
       outfile<<"\nGraph is cyclic\n";
    }else{
        outfile<<"\nGraph is acyclic\n";
    }
    outfile<<"Run time: "<<duration_cast<nanoseconds>(endG2-startG2).count()<<"ns\n";

   
    return 0;
}