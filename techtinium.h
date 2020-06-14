#include<stdio.h>
#include <iostream>

#include<map>
#include<vector>
#include<string>


using namespace std;

typedef long long ll;
static const ll inf = 1e18;

struct resource
{
    string name;
    ll capacity,cost;
};

struct overall_cost
{
    string region;
    ll total_cost;
    map<string,int> machines;
    
};

map<string,ll> machine;

map<string,vector<pair<string,ll>>> resource_cost;

void print_output(const vector<overall_cost> &output)
{
    cout<<"{"<<endl;
    cout<<" \"Output\":["<<endl;
    
    for(overall_cost entry : output)
    {
        cout<<"  {"<<endl;
        cout<<"   \"region\":"<<entry.region<<","<<endl;

        if(entry.total_cost >= inf) cout<<"   \"total_cost\":"<<"Not possible"<<","<<endl;
        else cout<<"   \"total_cost\":"<<entry.total_cost<<","<<endl;
        
        cout<<"   \"machines\":["<<endl;
        for(auto iterator : entry.machines)
        {
            cout<<"    ("<<iterator.first<<", "<<iterator.second<<"),"<<endl;    
        }
        cout<<"   ]"<<endl;
        cout<<"  }"<<endl;
    }
    
    cout<<" ]"<<endl;
    cout<<"}"<<endl;
    cout<<endl;

}

vector<resource> clean_data(const vector<pair<string,ll>> &cost,ll hours)
{
    vector<resource> data;

    for(auto iterator : cost)
    {
        if(iterator.second == inf) continue;
        string name = iterator.first;
        data.push_back({name,machine[name],iterator.second*hours});
    }

    return data;
}

map<string,int> find_no_machines(const vector<vector<ll>> &cache_cost, const vector<resource> &data)
{
    int machine_no = cache_cost.size()-1;
    int current_capacity = cache_cost[0].size()-1;
    map<string,int> no_machines;
    while(machine_no > 0 && current_capacity > 0)
    {
        if(cache_cost[machine_no][current_capacity] == cache_cost[machine_no-1][current_capacity])
        {
            machine_no--;
        }else if(cache_cost[machine_no-1][current_capacity] == cache_cost[machine_no][current_capacity - data[machine_no-1].capacity] + data[machine_no-1].cost){
            machine_no--;
        }else{
            no_machines[data[machine_no-1].name]++;
            current_capacity-=data[machine_no-1].capacity;
        }
    }

    return no_machines;
}

overall_cost find_cost(const string &city,const vector<pair<string,ll>> &cost,ll hours,ll capacity)
{
    
    vector<resource> data = clean_data(cost,hours);
   
    ll no_of_machine = data.size();

    vector<vector<ll>> cache_cost(no_of_machine+1,vector<ll>(capacity+1,inf));

    for(ll index_on_machine=0;index_on_machine<=no_of_machine;index_on_machine++)
    {
        cache_cost[index_on_machine][0] = 0;
    }

    for(ll index_on_machine=1;index_on_machine<=no_of_machine;index_on_machine++)
    {
        for(ll on_capacity=1;on_capacity<=capacity;on_capacity++)
        {
            if(data[index_on_machine-1].capacity <= on_capacity)
            {
                ll current_cost = data[index_on_machine-1].cost;
                cache_cost[index_on_machine][on_capacity] = min(cache_cost[index_on_machine-1][on_capacity], current_cost + cache_cost[index_on_machine][on_capacity-data[index_on_machine-1].capacity]);
            }else
            {
                cache_cost[index_on_machine][on_capacity] = cache_cost[index_on_machine-1][on_capacity];
            }
            
        }
    }

    ll total_cost = cache_cost[no_of_machine][capacity];
    
    map<string,int> machine_required;

    if(total_cost >= inf) return {city,inf,machine_required};

    machine_required = find_no_machines(cache_cost,data); 

    return {city,total_cost,machine_required};
}

void find_optimally_allocate_resources(ll hours,ll capacity)
{
    
    vector<overall_cost> output;
    
    for(auto iterator : resource_cost)
    {
        output.push_back(find_cost(iterator.first,iterator.second,hours,capacity));
    }

    print_output(output);
}

void register_machine(string name,ll power)
{
    machine[name] = power;
}

void register_cost_for_city(const string city,const vector<pair<string,ll>> &cost)
{
    resource_cost[city] = cost;
}




