//
//  main.cpp
//  CS-776_Assignment_2
//
//  Created by Scott S Forer on 9/15/16.
//  Copyright © 2016 Scott S Forer. All rights reserved.
//

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#define bit_length 150

using namespace std;


class individual
{
public:
    int combo[bit_length];
    double fitness;
};

int pop_size = 10;
vector<individual> agent;
double eval(int *pj);
//int bit_length = 150;
int target[bit_length];

int to_kill = pop_size/2;
int kill;
int gen_max = 360;


//-----------------------------------------------------------
//builds two solutions
void build_pop()
{
    agent.resize(pop_size);
    for (int pop=0; pop<pop_size; pop++)
    {
        individual A;
        agent.at(pop) = A;
        for (int num=0; num<bit_length; num++)
        {
            agent.at(pop).combo[num] = rand() % 2;
        }
    }
}


//-----------------------------------------------------------
//builds target
void create_target()
{
    for (int num=0; num<bit_length; num++)
    {
        target[num] = rand() % 2;
    }
    //cout << "target" << endl;
    //for (int num=0; num<bit_length; num++)
    //{
    //cout << target[num] << "\t";
    //}
    //cout << endl;
    //cout << endl;
}


//-----------------------------------------------------------
//compares the individuals bit by bit to the target
void easy_eval()
{
    for(int pop=0; pop<pop_size; pop++)
    {
        agent.at(pop).fitness = 0;
        int fit = 0;
        for (int num=0; num<bit_length; num++)
        {
            if(agent.at(pop).combo[num] == target[num])
            {
                fit ++;
            }
            else
            {
                continue;
            }
        }
        agent.at(pop).fitness = fit;
    }
}

//-----------------------------------------------------------
//evaluates the fitness for
int hard_eval(int *pj)
{
    int sum=0;
    for(int i=0; i<25; i++)
    {
        if(pj[i]==0)
        {
            sum = sum + 1;
        }
    }
    for(int i=25; i<50; i++)
    {
        if(pj[i]==1)
        {
            sum = sum + 1;
        }
    }
    for(int i=50; i<75; i++)
    {
        if(pj[i]==0)
        {
            sum = sum + 1;
        }
    }
    for(int i=75; i<100; i++)
    {
        if(pj[i]==1)
        {
            sum = sum +1;
        }
    }
    
    if(sum<100)
    {
        if(sum<=75)
        {
            if(sum<50)
            {
                if(sum<=25)
                {
                    return sum;
                }
                else
                {
                    return 25;
                }
            }
            else
            {
                return sum;
            }
            return sum;
        }
        else
        {
            return 75;
        }
    }
    else
    {
        return 100;
    }
}

//-----------------------------------------------------------
//evaluates the fitness for each individual
void evaluate(individual& A, individual& B)
{
    //easy_eval(A, B);
    //hard_eval(A);
    //hard_eval(B);
}


//-----------------------------------------------------------
//gets the fitness for each individual
void get_fitness()
{
    //evaluate(A, B);
    //A.fitness = 0;
    //A.fitness = eval(A.combo);
    //B.fitness = 0;
    //B.fitness = eval(B.combo);
    
    //A.fitness = hard_eval(A.combo);
    //B.fitness = hard_eval(B.combo);
    
    //easy_eval();
    
    
    
    for(int i=0; i<agent.size(); i++)
    {
        agent.at(i).fitness = 0;
        agent.at(i).fitness = eval(agent.at(i).combo);
    }
}


//-----------------------------------------------------------
//randomly selects two individuals and decides which one will die based on their fitness
int binary_select()
{
    int loser;
    int index_1 = rand() % agent.size();
    int index_2 = rand() % agent.size();
    while (index_1 == index_2)
    {
        index_2 = rand() % agent.size();
    }
    if(agent.at(index_1).fitness > agent.at(index_2).fitness)
    {
        loser = index_2;
    }
    else
    {
        loser = index_1;
    }
    return loser;
}


//-----------------------------------------------------------
//mutates the copies of the winning individuals
void mutation(individual &M)
{
    int bits_to_flip = (int)rand() % 10;
    //int bits_to_flip = 2;
    for (int p=0; p<bits_to_flip; p++)
    {
        int bitdex = (int)rand() % bit_length;
        for (int i=0; i< bit_length; i++)
        {
            if (i == bitdex)
            {
                if (M.combo[i] == 0)
                {
                    M.combo[i] = 1;
                }
                else
                {
                    M.combo[i] = 0;
                }
            }
        }
    }
    //return M;
}


//-----------------------------------------------------------
//runs the natural selection process
void natural_selection()
{
    //cout << "in" << endl;
    //cout << agent.size() << endl;
    
    for(int k=0; k<to_kill; k++)
    {
        kill = binary_select();
        agent.erase(agent.begin() + kill);
        //cout << "k = " << k << endl;
    }
    
    //cout << "out1" << endl;
    //cout << agent.size() << endl;
    //cout << endl;
    
    
    int to_replicate = to_kill;
    for (int rRrR=0; rRrR<to_replicate; rRrR++)
    {
        //cout << "r = " << rRrR << endl;
        individual M;
        int spot = rand() % agent.size();
        M = agent.at(spot);
        mutation(M);
        agent.push_back(M);
        //cout << "rend = " << rRrR << endl;
    }
    //cout << "out2" << endl;
    //cout << agent.size() << endl;
    //cout << endl;
}


struct greater_than_fitness
{
    inline bool operator() (const individual& struct1, const individual& struct2)
    {
        return (struct1.fitness > struct2.fitness);
    }
};




//-----------------------------------------------------------
//runs program
void EA()
{
    build_pop();
    create_target();
    for (int gen=0; gen<gen_max; gen++)
    {
        cout << "generation" << "\t" << gen << endl;
        get_fitness();
        //sort(agent.begin(), agent.end(), fitness);
        //for (int p=0; p<pop_size; p++)
        //{
        //cout << agent.at(p).fitness << "\t";
        //}
        cout << endl;
        natural_selection();
        //cout << endl;
        if (gen == gen_max-1)
        {
            get_fitness();
            sort(agent.begin(), agent.end(), greater_than_fitness());
            for (int p=0; p<pop_size; p++)
            {
                cout << agent.at(p).fitness << "\t";
            }
            cout << endl;
            cout << endl;
            cout << "Best Individual" << endl;
            cout << agent.at(0).fitness << endl;
            cout << endl;
            for (int num=0; num<bit_length; num++)
            {
                cout << agent.at(0).combo[num] << "\t";
            }
            cout << endl;
            cout << endl;
            cout << "worst Individual" << endl;
            cout << agent.at(pop_size-1).fitness << endl;
            cout << endl;
            int sum = 0;
            for (int p=0; p<pop_size; p++)
            {
                sum = sum + agent.at(p).fitness;
            }
            double ave;
            ave = sum/pop_size;
            cout << "Average Fitness" << "\t" << ave << endl;
            //for (int num=0; num<bit_length; num++)
            //{
            //cout << A.combo[l] << "\t";
            //}
            cout << endl;
        }
    }
}



//-----------------------------------------------------------
//-----------------------------------------------------------
int main()
{
    srand(time(NULL));
    EA();
    
    return 0;
}
