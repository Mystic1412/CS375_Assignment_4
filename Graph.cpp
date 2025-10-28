#include "Graph.h"

Graph::Graph(int nodes, bool dir) : n(nodes), directed(dir){
    adj.resize(nodes);
}

void Graph::addEdge(int u, int v){
    adj[u].push_back(v);
    if(!directed){
        adj[v].push_back(u);
    }
}

void Graph::printGraph() const{
    for(int i=0; i<n; ++i){
        cout<<i<<": ";
        for(int v: adj[i]){
            cout<<v<<" ";
        }
        cout<<endl;
    }
}

bool dfsUndirected(int u, int parent, vector<bool>& visited, vector<int>& parentList, const vector<vector<int>>& adj, vector<int>& cycle){
    visited[u] = true;
    for(int v: adj[u]){
        if(!visited[v]){
            parentList[v] = u;
            if(dfsUndirected(v,u,visited,parentList, adj,cycle)) return true;
        }else if(v != parent){
            cycle.clear();
            int x=u;
            cycle.push_back(v);
            while(x != v && x != -1){
                cycle.push_back(x);
                x=parentList[x];
            }
            cycle.push_back(v);
            return true;
        }
    }
    return false;
}

bool Graph::hasCycleUndirected(){
    vector<bool> visited(n, false);
    vector<int> parentList(n, -1);
    vector<int> cycle;

    for(int i =0; i<n; ++i){
        if(!visited[i]){
            if(dfsUndirected(i,-1, visited, parentList, adj, cycle)){
                cout<<"\nCycle found: ";
                for(int j =0; j<(int)cycle.size();++j){
                    cout<<cycle[j];
                    if(j+1<(int)cycle.size()){
                        cout<<" -> ";
                    }
                }
                cout<<endl;
                return true;
            }
        }
    }
    return false;
}