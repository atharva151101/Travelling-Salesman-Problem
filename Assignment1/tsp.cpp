#include"tsp.h"
#include"LK_tsp.h"
#include<cstdlib>
#include<cmath>

using namespace std;

istream &operator>>(istream & in, TspSolver & T)
{
    string s;
    cin>>s;

    if(s=="euclidean") {
        T.type=Eucledian;
    } else {
        T.type=NonEucledian;
    }

    in>>T.n;

    for(int i=0;i<T.n;i++) {
        double a;cin>>a;
        double x, y;
        cin>>x>>y;
        T.cities.push_back(make_pair(x,y));
    }

    for(int i=0;i<T.n;i++)
    {
        vector<double> row;
        for(int j=0;j<i;j++)
        {
        	row.push_back(T.graph[j][i]);
        }
        for(int j=i;j<T.n;j++)
        {
            double distance=sqrt(pow(T.cities[i].first-T.cities[j].first,2)+pow(T.cities[i].second-T.cities[j].second,2)); //cin>>distance;
            row.push_back(distance);cout<<distance<<" ";
        }
        T.graph.push_back(row);
        cout<<endl;
    }
    cout<<T.graph[53][3]<<endl;
    cout<<T.graph[3][53]<<endl;
        cout<<T.graph[24][38]<<endl;
        cout<<T.graph[38][24]<<endl;
        cout<<T.graph[53][54]<<endl;
        cout<<T.graph[54][53]<<endl;
        cout<<T.graph[3][38]<<endl;
        cout<<T.graph[38][3]<<endl;
    
    return in;
}
 
void TspSolver::solve_tsp(){
    LK_TSP LK_runner(graph);
    LK_runner.run_lin_kerninghan();
    bestTour=make_pair(LK_runner.tour,calculate_distance(LK_runner.tour));

    print_tour();
    
    vector<int> tour(n);
    for(int i=0;i<n;i++){cin>>tour[i];tour[i]--;}
    cout<<"optimal "<<calculate_distance(tour);
 
}

void TspSolver::print_tour()
{
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
