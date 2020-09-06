/* 
    Author: Yida Wang 
    Last Date Modified: April 16th, 2020 
    Description: 
    This program simulates the probability of the scores
    in the arcade game Skee Ball. 
*/ 
#include <iostream> 
#include <iomanip> 
#include <cmath> 
#include <random> 
#include <ctime> 
using namespace std; 
 
// define player and initilize 
typedef struct player 
{ 
    double score;     
    double count; 
} player; 

int struct_size = 13; 
player* player_ptr = new player[struct_size]; 

void initi_player() 
{ 
    for (int i = 0; i < struct_size; ++i) 
    { 
        player_ptr[i].score = 0;         
        player_ptr[i].count = 0; 
    } 
} 
// generate random score 
int rand_score() 
{ 
    double score = 0; 
    double rand_roll = ((double)rand() / (RAND_MAX));     
    if (rand_roll >= 0 && rand_roll <= 0.5) 
    { 
        score = 10; 
    } 
    else if (rand_roll > 0.5 && rand_roll <= 0.75) 
    { 
        score = 20; 
    } 
    else if (rand_roll > 0.75 && rand_roll <= 0.9) 
    {         
        score = 30;     
    } 
    else if (rand_roll > 0.9 && rand_roll <= 0.97) 
    {         
        score = 40;     
    } 
    else if (rand_roll > 0.97) 
    {         
        score = 50;     
    }     
    return score; 
} 
// calculate total score per roll 
int roll_ball(int num_roll) 
{ 
    double score_per_trial = 0;     
    for (int i = 0; i < num_roll; ++i) 
    { 
        score_per_trial += rand_score(); 
    } 
    return score_per_trial; 
} 
// put score into the struct 
void store_score(int trials) 
{ 
    int trial_score = 0;     
    for (int i = 0; i < trials; ++i) 
    { 
        trial_score = roll_ball(3); 
        for (int index = 0; index < struct_size; ++index) 
        { 
            if (player_ptr[index].score == trial_score) 
            { 
                player_ptr[index].count++;                 
                break;             
            } 
            else if (player_ptr[index].score == 0) 
            { 
                player_ptr[index].score = trial_score;                 
                player_ptr[index].count++;                 
                break;             
            }             
            else             
            {                
                continue; 
            } 
        } 
    } 
} 
// calculate probability 
double calculate_likelihood(int count, int trials) 
{     
    return ((double)count / (double)trials); 
} 
// sort the score 
void sort_score() 
{ 
    int temp_score = 0, temp_count = 0; 
    bool swapped;     
    do     
    { 
        swapped = false; 
        for (int i = 0; i < struct_size - 1; ++i) 
        { 
            if (player_ptr[i + 1].score < player_ptr[i].score) 
            { 
                temp_score = player_ptr[i].score;                 
                temp_count = player_ptr[i].count;                 
                player_ptr[i].score = player_ptr[i + 1].score;                 
                player_ptr[i].count = player_ptr[i + 1].count;                 
                player_ptr[i + 1].score = temp_score;                 
                player_ptr[i + 1].count = temp_count;                 
                swapped = true; 
            } 
        } 
    } while (swapped); 
} 
// print output 
void print_table(int trials) 
{ 
    cout << setw(10) << "Score" << setw(4) << "|" << setw(8) << "Count" << setw(4) << "|" << setw(14) << "Probability" << endl; 
    cout << "  -----------------------------------------" << endl;     
    for (int i = 0; i < struct_size; ++i) 
    { 
        if (player_ptr[i].score != 0) 
        { 
            cout << setprecision(0) << fixed; 
            cout << setw(8) << player_ptr[i].score << "     | ";             
            cout << setw(6) << player_ptr[i].count << "    | ";             
            cout << setw(10) << setprecision(4) << fixed << calculate_likelihood(player_ptr[i].count, trials) << endl; 
        } 
    } 
} 
int main() { 
    srand((unsigned)time(0));     
    initi_player();     
    int trials; 
    cout << "  Computational simulation of Skee Ball game" << endl;     
    cout << "  Enter number of trials: ";     
    cin >> trials;     
    store_score(trials);     
    sort_score();     
    print_table(trials); 
    delete[] player_ptr;    // free the ptr 
} 
