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
        vector<pair<double,double>> cities ;
        vector<vector<double>> graph;
        graphType type;
        pair<vector<int>,double> bestTour;


    public :
        void solve_tsp();
        void solve_tsp_sa();
        friend istream &operator>>(istream &, TspSolver &);
        void print_best_tour();
        double calculate_distance(vector<int>);

    
};


#endif
