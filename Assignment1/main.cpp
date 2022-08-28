#include<iostream>
#include"tsp.h"
#include<cstdlib>
#include<ctime>

using namespace std;

int main()
{
    srand(time(NULL));

    TspSolver Tsp;
    cin>>Tsp;

    Tsp.solve_tsp();

    return 0;
}
