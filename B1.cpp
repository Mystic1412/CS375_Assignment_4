#include <chrono>
#include <vector>
#include "Graph.h"
using namespace std;
using namespace chrono;

int main(){
    ofstream outfile("B1_output.txt");
    if(!outfile.is_open()){
        cerr<<"Error: Could not open output file.\n";
        return 1;
    }
    Graph G(15, true);

    G.addEdge(1,3);
    G.addEdge(3,4);
    G.addEdge(0,5);
    G.addEdge(2,5);
    G.addEdge(3,6);
    G.addEdge(4,7);
    G.addEdge(5,7);
    G.addEdge(6,8);
    G.addEdge(8,9);
    G.addEdge(7,10);
    G.addEdge(2,11);
    G.addEdge(5,12);
    G.addEdge(3,13);
    G.addEdge(5,13);
    G.addEdge(13,14);

    outfile<<"DAG(prereq -> Course):\n";
    for(int i=0; i<G.n;i++){
        outfile<<"cs"<<i+1<<": ";
        for(int j=0; j<(int)G.adj[i].size(); j++){
            outfile<<"cs"<<G.adj[i][j]+1<<" ";
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