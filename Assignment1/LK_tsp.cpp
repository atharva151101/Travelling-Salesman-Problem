#include"LK_tsp.h"

double LK_TSP::calculate_distance(vector<int> tour)
{
    double distance =0;
    for(int i=0;i<n;i++)
    {
        distance+=edges[tour[i]][tour[(i+1)%n]];
    }

    return distance;
}

void LK_TSP::print_tour(vector<int> tour)
{
    for(int i=0;i<n;i++)
    {
        cout<<tour[i]<<" ";
    }
    cout<<endl;
    
    cout<<tour_distance<<endl;
}

bool comp2(pair<pair<int,double>,double> a, pair<pair<int,double>,double> b)
{
    return a.second<b.second;        
}


bool comp(pair<int,double> a, pair<int,double> b)
{
    return a.second<b.second;        
}

pair<bool,pair<vector<int>,map<int,unordered_set<int>>>> LK_TSP::is_new_tour_valid(map<int,unordered_set<int>>& joined, map<int,unordered_set<int>> &broken)
{
    map<int,unordered_set<int>> new_tour_edges=tour_edges;
    vector<int> new_tour;
    for(int i=0;i<n;i++)
    {
        for(unordered_set<int>::iterator it=broken[i].begin();it!=broken[i].end();it++)
        {
            new_tour_edges[i].erase(*it);
        }
    }

    for(int i=0;i<n;i++)
    {
        for(unordered_set<int>::iterator it=joined[i].begin();it!=joined[i].end();it++)
        {
            new_tour_edges[i].insert(*it);
        }
    }

    for(int i=0;i<n;i++)
    {
        if(new_tour_edges[i].size()!=2)
             return make_pair(false,make_pair(new_tour,new_tour_edges));
        for(unordered_set<int>::iterator it=new_tour_edges[i].begin();it!=new_tour_edges[i].end();it++)
        {
            if(new_tour_edges[*it].find(i)==new_tour_edges[*it].end())
                return make_pair(false,make_pair(new_tour,new_tour_edges));
        }
    }

    new_tour.push_back(0);
    unordered_set<int> dup;dup.insert(0);
    int sec=*new_tour_edges[0].begin();
    new_tour.push_back(sec);
    if(dup.find(sec)!=dup.end())
        return make_pair(false,make_pair(new_tour,new_tour_edges));
    dup.insert(sec);    
    for(int i=2;i<n;i++)
    {
        for(unordered_set<int>::iterator it=new_tour_edges[new_tour[i-1]].begin();it!=new_tour_edges[new_tour[i-1]].end();it++)
        {
            if((*it)!=new_tour[i-2])
            {
                if(dup.find(*it)!=dup.end())
                    return make_pair(false,make_pair(new_tour,new_tour_edges));
                dup.insert((*it));    
                new_tour.push_back((*it));
                
                break;
            }
        }
    }

    return make_pair(true,make_pair(new_tour,new_tour_edges));

}

pair<bool,double> LK_TSP::nextXavailable(int start, int last,map<int,unordered_set<int>> joined, map<int,unordered_set<int>>broken)
{
    vector<int> options;
    options.push_back(get_prev_node(last));
    options.push_back(get_next_node(last));
    bool ans=false;
    double maxX = max(edges[last][options[0]],edges[last][options[1]]);
    for(int i=0;i<options.size();i++)
    {
        int next=options[i];
        if(joined[last].find(next)==joined[last].end() && broken[last].find(next)==broken[last].end())
        {
            map<int,unordered_set<int>> joined_new=joined;
            map<int,unordered_set<int>> broken_new=broken;
            broken_new[last].insert(next);
            broken_new[next].insert(last);

            joined_new[next].insert(start);
            joined_new[start].insert(next);
            
            pair<bool,pair<vector<int>,map<int,unordered_set<int>>>> new_tour=is_new_tour_valid(joined_new,broken_new);
            
            ans=ans | new_tour.first;

            //if(new_tour.first)cout<<"avalX "<<last<<" "<<next<<endl;
        }
   }
   return make_pair(ans,maxX);         
}
vector<pair<pair<int,double>,double>> LK_TSP::possibleYchoices(int start, int last,double gain, map<int,unordered_set<int>> joined, map<int,unordered_set<int>> broken)
{
    vector<pair<pair<int,double>,double>> choices;
    
    vector<pair<int,double>> Yorder;
    for(int i=0;i<n;i++)
    {
    	Yorder.push_back(make_pair(i,edges[last][i]));
    }
    sort(Yorder.begin(),Yorder.end(),comp);
    int cnt=0;
    for(int i=0;i<n && cnt<5;i++)
    {
        if(Yorder[i].first!=last && joined[last].find(Yorder[i].first)==joined[last].end() && broken[last].find(Yorder[i].first)==broken[last].end() && 
           tour_edges[last].find(Yorder[i].first)==tour_edges[last].end() )
        {
            
            if(gain>=edges[last][Yorder[i].first]){
             map<int,unordered_set<int>> joined_new=joined;
            map<int,unordered_set<int>> broken_new=broken;
            joined_new[last].insert(Yorder[i].first);
            joined_new[Yorder[i].first].insert(last);
            pair<bool,double> nextX = nextXavailable(start,Yorder[i].first,joined_new,broken_new);
            if(nextX.first){
            	choices.push_back(make_pair(Yorder[i],edges[last][i]-nextX.second));
            	cnt++;
            	}
            }
        }
    }
    sort(choices.begin(),choices.end(),comp2);
    //cout<<"zzzz "<<choices.size()<<endl;
    return choices;
}

bool LK_TSP::add_next_edge(int start,int last,double gain,map<int,unordered_set<int>> joined, map<int,unordered_set<int>> broken,int num_joined,int num_broken,bool already_found)
{
    //if(num_broken>2 || num_joined>2)cout<<"hurrayyy  "<<num_broken<<" "<<num_joined<<endl;
    vector<pair<pair<int,double>,double>> choices = possibleYchoices(start,last,gain,joined,broken);

    if(choices.size()==0) {return false | already_found;}

    if(num_broken==2)
    {
        for(int i=0;i<choices.size() && i<5;i++)
        {
             map<int,unordered_set<int>> joined_new=joined;
             map<int,unordered_set<int>> broken_new=broken;
             joined_new[last].insert(choices[i].first.first);
             joined_new[choices[i].first.first].insert(last);
             
             double Gi=gain-edges[last][choices[i].first.first];
             if(Gi<=best_improvement)
              	continue; 
             bool canChooseX=remove_next_edge(start,choices[i].first.first,Gi,joined_new,broken,num_joined+1,num_broken,already_found);
             if(canChooseX)
                return true;
             if(already_found)
             	return true;
                
        }
        return false | already_found;
    }
    else
    {
        map<int,unordered_set<int>> joined_new=joined;
        map<int,unordered_set<int>> broken_new=broken;
        joined_new[last].insert(choices[0].first.first);
        joined_new[choices[0].first.first].insert(last);
        double Gi=gain-edges[last][choices[0].first.first];
        if(Gi<=best_improvement)
              return false | already_found;
        return remove_next_edge(start,choices[0].first.first,Gi,joined_new,broken,num_joined+1,num_broken,already_found);
        
    }


}

bool LK_TSP::remove_next_edge(int start,int last,double gain,map<int,unordered_set<int>> joined, map<int,unordered_set<int>> broken,int num_joined,int num_broken,bool already_found)
{
    //if(num_broken>2 || num_joined>1)cout<<"hurrayyy  "<<num_broken<<" "<<num_joined<<endl;
    vector<int> options;
    if(edges[last][get_prev_node(last)]>get_next_node(last))
    {	
    	options.push_back(get_prev_node(last));
    	options.push_back(get_next_node(last));
    }
    else
    {
    	options.push_back(get_next_node(last));
    	options.push_back(get_prev_node(last));
    }
    
    for(int i=0;i<options.size();i++)
    {
        int next=options[i];
        double Gi=gain+edges[last][next];
	//if(new_tour.first)cout<<"remX "<<last<<" "<<next<<endl;
        if(joined[last].find(next)==joined[last].end() && broken[last].find(next)==broken[last].end())
        {
            map<int,unordered_set<int>> joined_new=joined;
            map<int,unordered_set<int>> broken_new=broken;
            broken_new[last].insert(next);
            broken_new[next].insert(last);

            joined_new[next].insert(start);
            joined_new[start].insert(next);
            

            double GStar = Gi - edges[next][start];
            pair<bool,pair<vector<int>,map<int,unordered_set<int>>>> new_tour=is_new_tour_valid(joined_new,broken_new);
            if(new_tour.first && GStar>best_improvement)
            {
                best_improvement=GStar;
                best_tour=new_tour.second.first;
                best_tour_edges=new_tour.second.second;
               // if(num_broken>1)cout<<"sfdasf "<<best_improvement<<"  "<<num_broken+1<<endl<<"llll ";
                //print_tour(best_tour);
                already_found= already_found | true;
            }
		
            if(! new_tour.first && num_broken>1)
                continue;
            else if(! new_tour.first && num_broken==1)
            {
                bool canChooseY = add_next_edge(start,next,Gi,joined,broken_new,num_joined,num_broken+1,already_found);
                if(!canChooseY) continue;
                else return true;
            }
            else if (new_tour.first) {
            	//if(num_broken>2 || num_joined>1)cout<<"hurrayyy  "<<num_broken<<" "<<num_joined<<endl;

                bool canChooseY = add_next_edge(start,next,Gi,joined,broken_new,num_joined,num_broken+1,already_found);
                if(!canChooseY && num_broken==1)
                    continue;
                else return canChooseY | already_found;
            }
        }
    }     
    return false | already_found;                   
}

LK_TSP::LK_TSP(vector<vector<double>> edges)
{
    this->edges=edges;
    this->n=edges[0].size();
    
    
}


vector<int> LK_TSP::create_random_tour(){
    vector<int> tour;
    for(int i=0;i<this->n;i++) {
        tour.push_back(i);
    }

    for(int i=this->n-1;i>=0;i--) {
        int j=rand()%(i+1);
        int temp=tour[i];
        tour[i]=tour[j];
        tour[j]=temp;
    }
    return tour;
}

void LK_TSP::run_lin_kerninghan()
{
    this->tour=create_random_tour();
    
    unordered_set<int> temp;
    for(int i=0;i<n;i++)
    {
        this->tour_edges[i]=temp;
    }
    for(int i=0;i<n;i++)
    {  
        this->tour_edges[tour[i]].insert(tour[(i+1)%n]);
        this->tour_edges[tour[(i+1)%n]].insert(tour[i]);
    }
    this->tour_distance=calculate_distance(tour);
    current_seen.clear();

    vector<int> perm = create_random_tour();
    bool improved = true;
    while(improved){
        improved=false;
        for(int i=0;i<this->n;i++)
        {
            calculate_inverse_tour();
            best_improvement=0;
            bool is_improved=improve_tour(perm[i]);
            
            if(!is_improved)
            {
                if(already_seen.find(tour_to_string(tour).first)!=already_seen.end())
                {
                    break;
                }
            }

            improved = improved | is_improved;
        }
    }
    pair<string,string> seen_tour=tour_to_string(tour);
    if(already_seen.find(seen_tour.first)==already_seen.end())
    {
        already_seen.insert(seen_tour.first);
        already_seen.insert(seen_tour.second);
    }
    //cout<<"size "<<already_seen.size()<<endl;
}


bool LK_TSP::improve_tour(int t1, int t2,int t3)
{
    map<int,unordered_set<int>> joined, broken;
    unordered_set<int> temp;
    for(int i=0;i<n;i++) {
        joined[i]=temp;
        broken[i]=temp;
    }
    
    joined[t2].insert(t3);
    joined[t3].insert(t2);
    
    broken[t1].insert(t2);
    broken[t2].insert(t1);
    
    if(remove_next_edge(t1,t3,edges[t1][t2]-edges[t2][t3],joined,broken,1,1,false))
    {	
        pair<string,string> current_tour=tour_to_string(best_tour);
        if(current_seen.find(current_tour.first)!=current_seen.end())
            return false;
                    
        current_seen.insert(current_tour.first);
        current_seen.insert(current_tour.second);
        
        //if(already_seen.find(current_tour.first)==already_seen.end())
    	//{
        //	already_seen.insert(current_tour.first);
        //	already_seen.insert(current_tour.second);
    	//}
    	//else return false;
    	//cout<<"ass "<<best_improvement<<endl;
    	if(tour_distance<=calculate_distance(best_tour)){return false;}
        tour=best_tour;
        tour_edges=best_tour_edges;
        tour_distance=calculate_distance(best_tour);
        cout<<"inside ";print_tour(tour);
        //cout<<"size "<<current_seen.size()<<endl;
        return true;
    }
    return false;
}

bool LK_TSP::improve_tour(int t1, int t2)
{
    vector<pair<int,double>> t3s;
    for(int i=0;i<n;i++)
    {
        if(tour_edges[t2].find(i)==tour_edges[t2].end() && tour_edges[t1].find(i)==tour_edges[t1].end() && edges[t1][t2]-edges[t2][i]>0)
        {
            t3s.push_back(make_pair(i,edges[t2][i]-max(edges[i][get_prev_node(i)],edges[i][get_next_node(i)])));
        }
    }
    
    sort(t3s.begin(),t3s.end(),comp);
    
    
    for(int i=0;i<t3s.size() && i<5 ;i++)
    {
        if(improve_tour(t1,t2,t3s[i].first))
            return true;
    }

    return false;

}

bool LK_TSP::improve_tour(int t1)
{
    if (!improve_tour(t1, get_prev_node(t1)))
        return improve_tour(t1, get_next_node(t1));

    return true;    
}

void LK_TSP::calculate_inverse_tour()
{
    vector<int> inverse_tour(n);
    for(int i=0;i<n;i++)
    {
        inverse_tour[this->tour[i]]=i;
    }
    this->inverse_tour=inverse_tour;
}

int LK_TSP::get_prev_node(int node)
{
    int idx=inverse_tour[node];
    return tour[(idx-1+n)%n];
}

int LK_TSP::get_next_node(int node)
{
    int idx=inverse_tour[node];
    return tour[(idx+1+n)%n];
}

pair<string,string> LK_TSP::tour_to_string(vector<int> & tour)
{
    int ind=0;
    while( ind<tour.size() && tour[ind]!=0 )ind++;

    string str1,str2;
    for(int i=0;i<tour.size();i++)
    {
        str1+=to_string(tour[(ind+i)%tour.size()]);
        str1+="-";
        str2+=to_string(tour[(ind+i)%tour.size()]);
        str2+="-";
    }

    return make_pair(str1,str2);
}
