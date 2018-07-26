#include "include/tsp_solver.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <array>
#include <stdlib.h>     /* srand, rand */


int main() {

    TSPSolver tsp;
    std::vector<Cell> cells_with_uniform_rewards = tsp.create_uniform_reward_cells (5, 6);
    std::vector<Cell> cells_with_random_rewards = tsp.create_randomized_reward_cells (5, 6);

    int max_permutations = 1000;
    int time_limit = 200;
   
    std::cout << "\n________________________________________________\n" << std::endl;
    std::cout << "Using cells with uniform reward." << std::endl;
    
    tsp.modified_brute_force(cells_with_uniform_rewards, max_permutations, time_limit);  
    tsp.nearest_neighbour(cells_with_uniform_rewards, time_limit);

    std::cout << "\n________________________________________________\n" << std::endl;
    std::cout << "Using cells with randomized reward between 0 and 30." << std::endl; 

    tsp.modified_brute_force(cells_with_random_rewards, max_permutations, time_limit); 
    tsp.nearest_neighbour(cells_with_random_rewards, time_limit);

    std::cout << "\n" << std::endl;

    return 0;
}
