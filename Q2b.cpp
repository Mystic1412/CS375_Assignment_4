#include <chrono>
#include "Graph.h"
#include <fstream>
using namespace std;
using namespace chrono;


int main(int argc, char* argv[]){
    if(argc<2){
        cerr<<"Usage: "<<argv[0] <<" <inputfile>\n";
        return 1;
    }

    ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        cerr<<"Error: Cannot open file\n";
        return 1;
    }

    string a, b;
    vector<pair<int,int>> edges;
    unordered_map<string,int> map;
    int idx = 0;

    while(inputFile>>a>>b){

        if(!map.count(a)) map[a] = idx++;
        if(!map.count(b)) map[b] = idx++;
        edges.push_back({map[a],map[b]});

    }
    
    Graph G1;
    G1.directed = false;
    G1.n = idx;
    G1.adj.assign(G1.n,{});
    for(auto &e: edges){
        G1.addEdge(e.first,e.second);
    }
    inputFile.close();

    ofstream outfile("Q2_output.txt");
    if(!outfile.is_open()){
        cerr<<"Error: Could not open output file.\n";
        return 1;
    }

    outfile<<"Graph 1\nAdjacency list:\n";
    G1.printGraph(outfile);
    auto startG1 = high_resolution_clock::now();
    bool hasCycleG1 = G1.hasCycleUndirected(outfile);
    auto endG1 = high_resolution_clock::now();

    if(hasCycleG1){
        outfile<<"\nGraph is cyclic\n";

    }else{
        outfile<<"\nGraph is acyclic\n";
    }

    outfile<<"Run time: "<<duration_cast<nanoseconds>(endG1-startG1).count()<<"ns\n";
   
    return 0;
}