#include <chrono>
#include <fstream>
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

    vector<pair<string,string>> rawEdges;
    unordered_set<string> labels;
    string a, b;

    while(inputFile>>a>>b){
        rawEdges.push_back({a,b});
        labels.insert(a);
        labels.insert(b);
    }
    inputFile.close();

    vector<string> sorted(labels.begin(), labels.end());
    sort(sorted.begin(),sorted.end());

    unordered_map<string,int> map;
    for(int i=0; i<(int)sorted.size();i++){
        map[sorted[i]] =i;
    }

    vector<pair<int,int>> edges;
    for(auto &e:rawEdges){
        edges.push_back({map[e.first], map[e.second]});
    }

    Graph G;
    G.directed = true;
    G.n = sorted.size();
    G.adj.assign(G.n,{});
    for(auto &e: edges){
        G.addEdge(e.first, e.second);
    }

    ofstream outfile("Q5b_output.txt");
    if(!outfile.is_open()){
        cerr<<"Error: Could not open output file.\n";
        return 1;
    }

    outfile<<"Adjacency List:\n";
    G.printGraph(outfile);
    outfile<<"\n";
    
    auto start = high_resolution_clock::now();
    G.dfsTopologicalSort(outfile);
    auto end = high_resolution_clock::now();

    outfile<<"\nTime complexity: O(V+E)\nRuntime: "<<duration_cast<nanoseconds>(end-start).count()<<" ns\n";
    outfile.close();
    return 0;
}