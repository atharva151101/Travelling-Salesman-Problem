#include"tsp.h"
#include<vector>
#include<unordered_set>
#include<utility>
#include<map>
#include<string>
#include<algorithm>

#ifndef LK
#define LK

class LK_TSP{

    private:
        int n;
        double tour_distance;
        double best_printed_tour;
        vector<vector<double>> edges;
        vector<int> inverse_tour;
        map<int,unordered_set<int>> tour_edges;
        double best_improvement;
        vector<int> best_tour;
        map<int,unordered_set<int>> best_tour_edges;
        unordered_set<string> already_seen;
        unordered_set<string> current_seen;

        
        void calculate_inverse_tour();
        void print_tour(vector<int>);
        pair<bool,double> nextXavailable(int,int,map<int,unordered_set<int>>,map<int,unordered_set<int>>);
        double calculate_distance(vector<int>);
        bool improve_tour(int);
        bool improve_tour(int, int);
        bool improve_tour(int,int,int);
        bool remove_next_edge(int,int,double, map<int,unordered_set<int>>, map<int,unordered_set<int>>,int, int,bool);
        bool add_next_edge(int,int,double,map<int,unordered_set<int>>, map<int,unordered_set<int>>,int,int,bool);
        vector<pair<pair<int,double>,double>> possibleYchoices(int,int ,double ,map<int,unordered_set<int>>, map<int,unordered_set<int>>);
        int get_prev_node(int);
        int get_next_node(int);
        pair<bool,pair<vector<int>,map<int,unordered_set<int>>>> is_new_tour_valid(map<int,unordered_set<int>> &, map<int,unordered_set<int>> &);
        void add_already_seen_tour();
        pair<string,string> tour_to_string(vector<int> &);
    public :
        vector<int> tour;
        vector<int> create_random_tour();    
        LK_TSP(vector<vector<double>>);
        void run_lin_kerninghan();
        

};

#endif
