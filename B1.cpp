#include <chrono>
#include <vector>
#include "Graph.h"
#include <algorithm>
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
    vector<pair<string,string>> rawEdges;
    unordered_set<string> labels;
    while(inputFile>>a>>b){
        rawEdges.push_back({a,b});
        labels.insert(a);
        labels.insert(b);
    }
    inputFile.close();

    vector<string> sorted(labels.begin(), labels.end());
    sort(sorted.begin(),sorted.end(), [](const string&a, const string &b){
        auto numA = stoi(a.substr(2));
        auto numB = stoi(b.substr(2));
        return numA<numB;
    });

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


    ofstream outfile("B1_output.txt");
    if(!outfile.is_open()){
        cerr<<"Error: Could not open output file.\n";
        return 1;
    }


    outfile<<"DAG(prereq -> Course):\n";
    for(int i=0; i<G.n; ++i){
        outfile<<"cs"<<i+1<<": ";
        for(int v: G.adj[i]){
            outfile<<"cs"<<v+1<<" ";
        }
        outfile<<"\n";
    }

    outfile<<"\n";  
    auto start = high_resolution_clock::now();

    vector<int> indeg(G.n,0);
    for(int u = 0; u<G.n; u++){
        for(int v:G.adj[u]){
            indeg[v]++;
        }
    }

    vector<int> S;
    for(int i=0; i<G.n; i++){
        if(indeg[i] ==0){
            S.push_back(i);
        }
    }

    int semester =0, completed =0;

    while(!S.empty()){
        vector<int> Next;
        outfile << "Semester "<<(semester+1)<<": ";
        for(int i =0; i<(int)S.size();i++){
            outfile<<"cs"<<S[i]+1;
            if(i+1<(int)S.size()){
                outfile<<", ";
            }
        }
        outfile<<"\n";

        for(int u: S){
            completed++;
            for(int v:G.adj[u]){
                indeg[v]--;
                if(indeg[v]==0){
                    Next.push_back(v);
                }
            }
        }
        S = Next;
        semester++;
    }
    auto end = high_resolution_clock::now();
    if(completed < G.n){
        outfile<<"\nGraph contains a cycle -> invalid schedule";
    }else{
        outfile<<"\nMinimum number of semesters = "<<semester<<"\n";
    }

    outfile<<"Time complexity: O(V+E)\nRuntime: "<<duration_cast<nanoseconds>(end-start).count()<<" ns\n";
    outfile.close();

    return 0;
}