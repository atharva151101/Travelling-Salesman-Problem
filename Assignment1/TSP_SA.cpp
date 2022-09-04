#include"TSP_SA.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#define INITIAL_T 999999999999999
#define T_UPDATE_FACTOR 0.999
using namespace	std;

TSP_SA::TSP_SA(vector<vector<double>> edge)
		{
			srand((unsigned int) time(NULL));

			this->n = edge.size();
			this->edge = edge;
			T = INITIAL_T;
			
			//Initialisations of path arrays
            for(int i=0;i<n;i++)
            {
             path_best.push_back(i);
             path_new.push_back(i);
             path_current.push_back(i);
            }
			
		}

double TSP_SA:: getPathCost(vector<int> path)
		{
			double cost = 0;
			for(int i = 0;i < n;i++)
			{
				cost += edge[path[i]][path[(i+1)%n]];
			}
			return cost;
		}

    
void TSP_SA::twoEdgeExchange(int a, int b, vector<int>& path_new)
		{
			if(a > b)
			{
				twoEdgeExchange(b,a,path_new);
			}
			//reverse the substring
			while(a<b)
			{
				swap(path_new[a],path_new[b]);
				a++;
				b--;
			}
		}

void TSP_SA::begin()
		{
			srand((unsigned int)time(NULL));
			int counter = 0;
			int k = 1;
			while(1)
			{
				int iterator=100;
				
				while(--iterator)
				{
					int node1 = (rand()%(n-1))+1;
					int node2 = (rand()%(n-1))+1;
                    for(int i=1;i<n;i++)
						path_new[i]=path_current[i];
                    double r = (double) (rand()/ (double) RAND_MAX);
					twoEdgeExchange(node1, node2, path_new);
					double delta_E = getPathCost(path_new) - getPathCost(path_current);
					double p = 1/(1+ pow(M_E, (delta_E/T)));
					if(p > r)
						{for(int i=1;i<n;i++)
							path_current[i]=path_new[i];
                        }
				    double cost_new=getPathCost(path_new);
                    double cost_best=getPathCost(path_best);
					
					if(cost_new < cost_best)
					{
						//cout<<cost_best-cost_new<<endl;
                        counter = 0;
						for(int i=1;i<n;i++)
							path_best[i]=path_new[i];
						printBestPath();
						
					}
					else
						counter++;
					
				}
				//cout<<getPathCost(path_best)<<endl;
				T *= T_UPDATE_FACTOR;
				if(counter > 1000000)
				{
					T = k*10*n;
					k += k;
					if(T>INITIAL_T)
					{
						T = INITIAL_T;
						k = 1;
					}
					counter = 0 ;
					 //cout<<"\nchange T "<<T<<endl;
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
			cout<<"Path: "<<getPathCost(path_best)<<endl;
			for(int i=0;i<n;i++)
				cout<<path_best[i]+1<<" ";
			cout<<endl;
		}

bool TSP_SA::validate_path(vector<int> path)
{
	//if(path.size()!=n+1) return false;
	vector<bool> found(n,false);
	//if(path[0]!=path[n])return false;
	for(int i=0;i<n;i++)
		if(found[path[i]]) return false;
		else found[path[i]]=true;
	return true;
}