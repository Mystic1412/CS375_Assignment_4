#include <chrono>
#include "Graph.h"
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
    unordered_map<string,int> map;
    vector<pair<int,int>> edges;
    int idx = 0;


    while(inputFile>>a>>b){
        if(!map.count(a)) map[a] = idx++;
        if(!map.count(b)) map[b] = idx++;
        edges.push_back({map[a], map[b]});
    }

    Graph G;
    G.directed = false;
    G.n = idx;
    G.adj.assign(G.n,{});
    for(auto &e: edges){
        G.addEdge(e.first, e.second);
    }

    ofstream outfile("Q6_output.txt");
    if(!outfile.is_open()){
        cerr<<"Error: Could not open output file.\n";
        return 1;
    }

    outfile<<"Adjacency List:\n";
    G.printGraph(outfile);
    outfile<<"\n";

    
    auto start = high_resolution_clock::now();
    G.isBipartite(outfile);
    auto end = high_resolution_clock::now();

    outfile<<"\nRuntime: "<<duration_cast<nanoseconds>(end-start).count()<<" ns\n";

    outfile.close();
    return 0;

}