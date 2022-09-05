#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include<utility>
#include<vector>
#define Initial_Temperature 999999999999999
#define Temperature_update_factor 0.999

using namespace std;

class TSP_SA 
{
	private:
		int n;
		vector<vector<double>> edge;
		vector<int> path_current,path_new,path_best;
		double T;

	public:
		TSP_SA(vector<vector<double>> edge);
		void edgeExchange(int a, int b, vector<int>& path_new);
		void runner();
		void printBestPath();
		double pathCost(vector<int> path);
		bool validate_path(vector<int> path);
};