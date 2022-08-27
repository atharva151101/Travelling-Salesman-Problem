#include<tsp.h>
#include<LK_tsp.h>
#include<cstdlib>

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
        float x, y;
        cin>>x>>y;
        T.cities.push_back(make_pair(x,y));
    }

    for(int i=0;i<T.n;i++)
    {
        vector<float> row;
        for(int j=0;j<T.n;j++)
        {
            float distance; cin>>distance;
            row.push_back(distance);
        }
        T.graph.push_back(row);
    }
}
 
void TspSolver::solve_tsp(){
    LK_TSP LK_runner(graph);
    LK_runner.run_lin_kerninghan();
    bestTour=make_pair(LK_runner.tour,calculate_distance(LK_runner.tour));

    print_tour();
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

float TspSolver::calculate_distance(vector<int> tour)
{
    float distance =0;
    for(int i=0;i<=n;i++)
    {
        distance+=graph[tour[i]][tour[(i+1)%n]];
    }

    return distance;
}