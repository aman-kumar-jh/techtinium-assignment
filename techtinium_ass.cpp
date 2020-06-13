#include<stdio.h>
#include <iostream>

#include "techtinium.h"

using namespace std;

typedef long long ll;

void input()
{
    
    /*
        @param1: name of machine
        @param2: capcity of the machine
        
    */
    register_machine("Large",10);
    register_machine("XLarge",20);
    register_machine("2XLarge",40);
    register_machine("4XLarge",80);
    register_machine("8XLarge",160);
    register_machine("10XLarge",320);

    /*
        @param1: Name of region
        @parma2: array of pair of machine name and its cost in respective region

    */
    register_cost_for_city("New York",
                            {{"Large",120},{"XLarge",230},{"2XLarge",450},{"4XLarge",774},{"8XLarge",1400},{"10XLarge",2820}});
    register_cost_for_city("India",
                            {{"Large",140},{"XLarge",inf},{"2XLarge",413},{"4XLarge",890},{"8XLarge",1300},{"10XLarge",2970}});
    register_cost_for_city("China",
                            {{"Large",110},{"XLarge",200},{"2XLarge",inf},{"4XLarge",670},{"8XLarge",1180},{"10XLarge",inf}});
}

void calculate(ll capacity,ll hours)
{
    /*
        @parm1: hours
        @parm2: capacity

        @return: details of machine required and cost for each region

    */
    find_optimally_allocate_resources(hours,capacity);
}

void test_cases(){

    cout<<"Test Case: 1"<<endl;
    calculate(1150,1);
    
    cout<<"Test Case: 2"<<endl;
    calculate(230,5);

    cout<<"Test Case: 3"<<endl;
    calculate(100,24);

    cout<<"Test Case: 4"<<endl;
    calculate(1100,12);

}

int main()
{
    input();

    test_cases();
    
    return 0;
}