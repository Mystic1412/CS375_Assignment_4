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

bool Graph::hasCycleUndirected(ostream& out){
    vector<bool> visited(n, false);
    vector<int> parentList(n, -1);
    vector<int> cycle;

    for(int i =0; i<n; ++i){
        if(!visited[i]){
            if(dfsUndirected(i,-1, visited, parentList, adj, cycle)){
                out<<"\nCycle found: ";
                for(int j =0; j<(int)cycle.size();++j){
                    out<<cycle[j];
                    if(j+1<(int)cycle.size()){
                        out<<" -> ";
                    }
                }
                out<<"\n";
                return true;
            }
        }
    }
    return false;
}


void dfsVisitTopo(int u, const Graph& G, vector<int>& color, vector<int>& disc, vector<int>& finish, int& time, vector<int>& topo, ofstream& out, vector<vector<char>>& edgeType){
    color[u] = 1;
    time++;
    disc[u] = time;

    for(int i=0; i<(int)G.adj[u].size(); i++){
        int v=G.adj[u][i];
        if(color[v] ==0){
            out<<"Edge "<<u+1<<" -> "<<v+1<<" : T (Tree)\n";
            edgeType[u][v] ='T';
            dfsVisitTopo(v,G,color,disc,finish,time,topo,out,edgeType);
        }else if(color[v] == 1){
            out<<"Edge "<<u+1<<" -> "<<v+1<<" : B (back)\n";
            edgeType[u][v] ='B';
        }else if(disc[u]<disc[v]){
            out<<"Edge "<<u+1<<" -> "<<v+1<<" : F (Forward)\n";
            edgeType[u][v] ='F';
        }else{
            out<<"Edge "<<u+1<<" -> "<<v+1<<" : C (Cross)\n";
            edgeType[u][v] ='C';
        }
    }
    color[u]=2;
    time++;
    finish[u] = time;
    topo.push_back(u);
}

void Graph::dfsTopologicalSort(ofstream& out){
    vector<int> color(n,0);
    vector<int> disc(n,0);
    vector<int> finish(n,0);
    vector<int> topo;
    vector<vector<char>> edgeType(n,vector<char>(n,'-'));
    int time =0;

    vector<int> order = {0,6,1,3,4,5,2,7};

    for(int i=0; i<(int)order.size(); i++){
        int u=order[i];
        if(color[u] == 0){
            dfsVisitTopo(u, *this, color, disc, finish, time, topo, out, edgeType);
        }

        out<<"\nDiscovery / Finishing TImes:\n";
        for(int i=0; i<n; i++){
            out<<"Node "<<i+1<<": "<<disc[i]<<"/"<<finish[i]<<"\n";
        }

        out<<"\nTopological Order: ";
        for(int i=topo.size()-1; i>=0; i--){
            out<<topo[i]+1;
            if(i>0)out<< " -> ";
        }
        out<<"\n";
    }
}


bool Graph::isBipartite(ofstream& out){
    vector<int> color(n,-1);
    bool isBipartite = true;
    vector<int> setV1, setV2;

    for(int i=0; i<n; ++i){
        if(color[i] ==-1) {
            queue<int> q;
            q.push(i);
            color[i]=0;
            setV1.push_back(i);

            while(!q.empty()){
                int u = q.front();
                q.pop();

                for(int j=0; j<(int)adj[u].size(); j++){
                    int v = adj[u][j];
                    if(color[v] == -1){
                        color[v] =1 -color[u];
                        q.push(v);
                        if(color[v] ==0){
                            setV1.push_back(v);
                        }else{
                            setV2.push_back(v);
                        }
                    }else if(color[v] ==color[u]){
                        isBipartite = false;
                    }
                }
            }
        }
    }

    if(isBipartite){
        out<<"Graph is bipartite\nSet V1:";
        for(int i=0; i<(int)setV1.size(); i++){
            out<<setV1[i]+1 <<" ";
        }
        out<<"\nSet V2:";
        for(int i=0; i<(int)setV2.size(); i++){
            out<<setV2[i]+1 <<" ";
        }
        out<<"\n";
    }else{
        out<<"Graph is NOT bipartite\n";
    }

    out<<"Time Complexity: O(V+E)\n";
    return isBipartite;
}