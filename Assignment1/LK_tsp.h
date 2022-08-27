#include<tsp.h>
#include<vector>
#include<unordered_set>
#include<utility>
#include<map>
#include<algorithm>

#ifndef LK
#define LK

class LK_TSP{

    private:
        int n;
        vector<vector<float>> edges;
        vector<int> inverse_tour;
        map<int,unordered_set<int>> tour_edges;
        float best_improvement;
        vector<int> best_tour;
        map<int,unordered_set<int>> best_tour_edges;

        vector<int> create_random_tour();    
        void calculate_inverse_tour();
        bool improve_tour(int);
        bool improve_tour(int, int);
        bool improve_tour(int,int,int);
        bool remove_next_edge(int,int,float, map<int,unordered_set<int>>, map<int,unordered_set<int>>,int, int,bool);
        bool add_next_edge(int,int,float,map<int,unordered_set<int>>, map<int,unordered_set<int>>,int,int,bool);
        vector<pair<int,int>> possibleYchoices(int ,float ,map<int,unordered_set<int>>, map<int,unordered_set<int>>);
        int get_prev_node(int);
        int get_next_node(int);
        pair<bool,pair<vector<int>,map<int,unordered_set<int>>>> is_new_tour_valid(map<int,unordered_set<int>> &, map<int,unordered_set<int>> &);
    
    public :
        vector<int> tour;
        LK_TSP(vector<vector<float>>);
        void LK_TSP::run_lin_kerninghan();
        

};

#endif