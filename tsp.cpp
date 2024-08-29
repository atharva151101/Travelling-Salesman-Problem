#include"tsp.h"
#include"LK_tsp.h"
#include"TSP_SA.h"
#include<cstdlib>
#include<cmath>

using namespace std;

istream &operator>>(istream & in, TspSolver & T)
{
    string s;
    getline(in,s);

    if(s.substr(0,9)=="euclidean") {
        T.type=Eucledian;
    } else {
        T.type=NonEucledian;
    }

    in>>T.n;

    for(int i=0;i<T.n;i++) {
        //double a ; cin>>a;
        double x, y;
        cin>>x>>y;
        T.cities.push_back(make_pair(x,y));
    }

    for(int i=0;i<T.n;i++)
    {
        vector<double> row;
        for(int j=0;j<T.n;j++)
        {
            double distance;
         //   distance=sqrt(pow(T.cities[i].first-T.cities[j].first,2)+ pow(T.cities[i].second-T.cities[j].second,2)); 
            //cout<<distance<<" ";
            cin>>distance;
            row.push_back(distance);
        }
        T.graph.push_back(row);
        //cout<<endl;
    }
    
    //vector<int> opt(T.n);
    //for(int i=0;i<T.n;i++){cin>>opt[i];opt[i]--;}
    //cout<<T.calculate_distance(opt)<<endl;
    
    vector<int> random_tour;
    for(int i=0;i<T.n;i++) {
        random_tour.push_back(i);
    }

    for(int i=T.n-1;i>=0;i--) {
        int j=rand()%(i+1);
        int temp=random_tour[i];
        random_tour[i]=random_tour[j];
        random_tour[j]=temp;
    }
    T.bestTour=make_pair(random_tour,T.calculate_distance(random_tour));

    return in;
}
 
void TspSolver::solve_tsp(){

    
    LK_TSP LK_runner(graph);
    int num=20;  
    for(int i=0;i<20;i++)
    {    
        LK_runner.run_lin_kerninghan();
        if(calculate_distance(LK_runner.tour)<bestTour.second)
        {
            bestTour=make_pair(LK_runner.tour,calculate_distance(LK_runner.tour));
            //print_best_tour();        
        }
    }    

}

void TspSolver::solve_tsp_sa(){

        
        TSP_SA TSP_runner(graph);
        TSP_runner.runner();
        
}


void TspSolver::print_best_tour()
{
cout<<"outside "; 
    for(int i=0;i<n;i++)
    {
        cout<<bestTour.first[i]<<" ";
    }
    cout<<endl;

    cout<<bestTour.second<<endl;
}


double TspSolver::calculate_distance(vector<int> tour)
{
    double distance =0;
    for(int i=0;i<n;i++)
    {
        distance+=graph[tour[i]][tour[(i+1)%n]];
    }

    return distance;
}
