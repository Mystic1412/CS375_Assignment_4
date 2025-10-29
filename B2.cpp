#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
using namespace chrono;


struct Point{double x, y;};

bool cases(double x,double y){
    if(x<0||y<0) return 0;
    if(x + y < 5) return false; //calories
    if(2*x+y<6) return false; //vitamin A
    if(x+3*y<9) return false; //vitamin C
    return true;
}

double cost(double x, double y){
    return 0.12*x+0.15*y;
}


int main(){
    ofstream out("B2_output.txt");
    if(!out.is_open()){
        cerr<<"Error: Could not open output file.\n";
        return 1;
    }

    auto start = high_resolution_clock::now();
    vector<Point> options;
    
    //x + y = 5 and 2x + y = 6
    options.push_back({1.0,4.0});

    //x + y = 5 and x + 3y = 9
    options.push_back({3.0,2.0});

    //2x + y = 6 and x + 3y = 9
    options.push_back({1.8,2.4});

    //Axis intercepts 
    options.push_back({0.0,6.0});
    options.push_back({9.0,0.0});

    double bestCost =1e99;
    Point best = {-1,-1};

    for(auto p:options){
        if(cases(p.x,p.y)){
            double c = cost(p.x,p.y);
            if(c<bestCost){
                bestCost =c;
                best =p;
            }
        }
    }

    auto end = high_resolution_clock::now();

    out.setf(ios::fixed);
    out.precision(2);

    if(best.x<0){
        out<<"No feasible soultion found\n";
    }else{
        out<<"Optimal soultion:\nCups of Drink X: "<<best.x<<"\nCups of Drink Y: "<<best.y<<"\nMinimum cost: $"<<bestCost<<"\n";
    }

    out<<"Runtime: "<<duration_cast<nanoseconds>(end-start).count();
    out.close();
    return 0;
}