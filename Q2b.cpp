#include <chrono>
#include "Graph.h"
using namespace std;
using namespace chrono;


int main(){
    Graph G1(6, false);
    G1.addEdge(0,1); //X1 to Y1
    G1.addEdge(0,3); //X1 to Y2
    G1.addEdge(1,2); //Y1 to X3
    G1.addEdge(1,4); //Y1 to X2
    G1.addEdge(2,5); //X3 to Y3
    G1.addEdge(5,4); //Y3 to X2
    G1.addEdge(4,3); //X2 to Y2


    cout<<"Graph 1\nAdjacency list:"<<endl;
    G1.printGraph();

    auto startG1 = high_resolution_clock::now();
    bool hasCycleG1 = G1.hasCycleUndirected();
    auto endG1 = high_resolution_clock::now();

    if(hasCycleG1){
        cout<<"\nGraph is cyclic"<<endl;

    }else{
        cout<<"\nGraph is acyclic"<<endl;
    }

    cout<<"Run time: "<<duration_cast<nanoseconds>(endG1-startG1).count()<<"ns"<<endl;



    Graph G2(4,false);
    G2.addEdge(0,1); //a to b
    G2.addEdge(0,2); //a to c
    G2.addEdge(0,3); //a to d
    G2.addEdge(1,3); //b to d
    G2.addEdge(2,3); //c to d
    G2.addEdge(1,2); //b to c

    cout<<"\nGraph 2\nAdjacency list:"<<endl;
    G2.printGraph();

    auto start = high_resolution_clock::now();
    bool hasCycleG2 = G2.hasCycleUndirected();
    auto end = high_resolution_clock::now();

    if(hasCycleG2){
        cout<<"\nGraph is cyclic"<<endl;
    }else{
        cout<<"\nGraph is acyclic"<<endl;
    }

    cout<<"Run time: "<<duration_cast<nanoseconds>(end-start).count()<<"ns"<<endl;

   
    return 0;
}