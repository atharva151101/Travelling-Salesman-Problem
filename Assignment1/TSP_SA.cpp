#include"TSP_SA.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#define Temperature_update_factor 0.999
#define Initial_Temperature 999999999999999
using namespace	std;

TSP_SA::TSP_SA(vector<vector<double>> edge)
		{
			srand((unsigned int) time(NULL));

			this->n = edge.size();
			this->edge = edge;
			T = Initial_Temperature;
			
			//Initialisations of path arrays
            for(int i=0;i<n;i++)
            {
             path_best.push_back(i);
             path_new.push_back(i);
             path_current.push_back(i);
            }
			
		}

double TSP_SA:: pathCost(vector<int> path)
		{
			double total = 0;
			for(int i = 0;i < n;i++)
			{
				total += edge[path[i]][path[(i+1)%n]];
			}
			return total;
		}

    
void TSP_SA::edgeExchange(int a, int b, vector<int>& path_new)
		{
			if(a > b)
			{
				edgeExchange(b,a,path_new);
			}
			//reverse the substring
			while(a<b)
				swap(path_new[a++],path_new[b--]);
		}

void TSP_SA::runner()
		{
			srand((unsigned int)time(NULL));
			int counter = 0;
			int k = 1;
			while(1)
			{
				int iterator=100;
				
				while(--iterator)
				{
					for(int i=1;i<n;i++)
						path_new[i]=path_current[i];
					int node1 = (rand()%(n-1))+1;
					int node2 = (rand()%(n-1))+1;
                    double random_prob = (double) (rand()/ (double) RAND_MAX);
					edgeExchange(node1, node2, path_new);
					double delta_cost_diff = pathCost(path_new) - pathCost(path_current);
					double prob = 1/(1+ pow(M_E, (delta_cost_diff/T)));
					if(prob > random_prob)
						{for(int i=1;i<n;i++)
							path_current[i]=path_new[i];
                        }
				    double cost_new=pathCost(path_new);
                    double cost_best=pathCost(path_best);
					
					if(cost_new >= cost_best)
					  counter++;
					else
					{
						//cout<<cost_best-cost_new<<endl;
                        counter = 0;
						for(int i=1;i<n;i++)
							path_best[i]=path_new[i];
						printBestPath();
					}
					
				}
				T *= Temperature_update_factor;
				if(counter > 1000000)
				{
					T = k*10*n;
					counter = 0 ;
					k =2*k;
					if(T>Initial_Temperature)
					{
						T = Initial_Temperature;
						k = 1;
					}
				}
			}
		}

void TSP_SA::printBestPath()
		{
			if(!validate_path(path_best))
			{
				cout<<"invlid path";
				exit(-1);
			}
			cout<<"Path: "<<pathCost(path_best)<<endl;
			for(int i=0;i<n;i++)
				cout<<path_best[i]+1<<" ";
			cout<<endl;
		}

bool TSP_SA::validate_path(vector<int> path)
{
	vector<bool> found(n,false);
	for(int i=0;i<n;i++)
		if(found[path[i]]) return false;
		else found[path[i]]=true;
	return true;
}