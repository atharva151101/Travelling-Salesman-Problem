#include<iostream>
#include<utility>
#include<vector>
using namespace std;

#ifndef TSP_SOLVER
#define TSP_SOLVER

enum graphType {
    Eucledian,
    NonEucledian,
};

class TspSolver{
    private :
        int n;
        vector<pair<float,float>> cities ;
        vector<vector<float>> graph;
        graphType type;
        pair<vector<int>,float> bestTour;


    public :
        void solve_tsp();
        friend istream &operator>>(istream &, TspSolver &);
        void print_tour();
        float calculate_distance(vector<int>);

    
};


#endif