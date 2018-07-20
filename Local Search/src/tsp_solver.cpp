#include "../include/tsp_solver.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>    

// Member functions definitions including constructor
TSPSolver::TSPSolver(void) : CELL_SEARCH_TIME(6), TRAVEL_SPEED(0.5) {
    std::cout << "\nTSPSolver Object is being created\n" << std::endl;
}


// Input: search_cells - set of cells to be searched
// Output: total_reward - reward acquired from searched_cells
double TSPSolver::get_total_reward(std::vector<Cell> search_cells) {
	double total_reward = 0;
	for(int i = 0; i < (int) search_cells.size(); i++) {
		total_reward += search_cells[i].reward;
	}
	return total_reward;
}


// Input: cell1, cell2 - cells
// Output: distance - euclidean distance between cells
double TSPSolver::get_dist(Cell cell1, Cell cell2) {
	int delta_x = cell1.x - cell2.x;
	int delta_y = cell1.y - cell2.y;
	double dist = sqrt(pow(delta_x,2) + pow(delta_y,2));
	return dist;
}

// Input: ordered_search_cells - set of cells to be searched in order
// Output: total_distance - distance traversed to visit all cells
double TSPSolver::get_total_dist(std::vector<Cell> ordered_search_cells) {
	double total_dist = 0;
	for(int i = 1; i < (int) ordered_search_cells.size(); i++) {
		Cell cell1 = ordered_search_cells[i-1];
		Cell cell2 = ordered_search_cells[i];
		total_dist += get_dist(cell1, cell2);
	}
	return total_dist;
}

// Input: ordered_search_cells - set of cells to be searched in order
// Output: time - time expended to visit all cells
double TSPSolver::get_total_time(std::vector<Cell> ordered_search_cells) {
	double search_time = CELL_SEARCH_TIME*ordered_search_cells.size();
	double travel_time = TRAVEL_SPEED*get_total_dist(ordered_search_cells);
	double total_time = search_time + travel_time;
	return total_time;
}

void TSPSolver::print_cell(Cell cell1) {
    std::cout << "(" << cell1.x << ", " << cell1.y << ", " << cell1.reward << ")" << std::endl;
}

void TSPSolver::print_all_cells (std::vector<Cell> cells) {
	std::cout << "[";
    for(int i = 0; i < (int) cells.size(); i++) {
        std::cout << "(" << cells[i].x << ", " << cells[i].y << ", " << cells[i].reward;
        if (i == cells.size()-1) {
            std::cout << ")";
        }
        else {
            std::cout << "), ";
        }
	}
    std::cout << "]" << std::endl;    
}


void TSPSolver::print_total_reward (std::vector<Cell> cells) {
    std::cout << "\nTotal reward of the cells is " << get_total_reward(cells) << std::endl;
}

void TSPSolver::print_total_dist (std::vector<Cell> cells) {
    std::cout << "\nTotal reward of the cells is " << get_total_dist(cells) << std::endl;
}

void TSPSolver::print_total_time (std::vector<Cell> cells) {
    std::cout << "\nTotal reward of the cells is " << get_total_time(cells) << std::endl;
}

void TSPSolver::print_all_stats (std::vector<Cell> cells) {

    std::set<Cell> unique_cells(cells.begin(), cells.end());

    std::cout << "Total reward: " << get_total_reward(cells) << " | Total distance: " << get_total_dist(cells) 
    << " | Total time: " << get_total_time(cells) << " | Total unique cells visited: " << unique_cells.size() << std::endl;

}

double TSPSolver::totalTimeGetter(std::vector<Cell> cells) {
    return get_total_time(cells);
}

double TSPSolver::totalDistanceGetter(std::vector<Cell> cells) {
    return get_total_dist(cells);
}

double TSPSolver::totalRewardGetter(std::vector<Cell> cells) {
    return get_total_reward(cells);
}

void TSPSolver::modified_brute_force (std::vector<Cell> cells, int max_perm, int time_period) {
   
    std::cout << "Running modified brute force for TSP Simple Definition..." << std::endl;
    std::cout << "Method will look at " << max_perm << " permutations. Time period is constrained to " << time_period << "." << std::endl;
   
    std::cout << "\nThe following is the input to the method. Shown below are the cells in default order." << std::endl;
    print_all_stats(cells);
    print_all_cells(cells);

    std::vector<Cell> input_cells(cells);
    std::vector<Cell> round_trip;
    std::set<std::vector<Cell>> possible_paths;

    int cells_skipped = 0;
    int iterations = 0;

    // Get "max_perm" number of permutations that meet the time_period constraint
    while (possible_paths.size() < max_perm) {
        round_trip = cells;
        round_trip.push_back(cells[0]);
        while (get_total_time(round_trip) > time_period) {
            std::sort(cells.begin(), cells.end());
            cells.pop_back();
            cells_skipped++;
            round_trip = cells;
            round_trip.push_back(cells[0]);
        }
        possible_paths.insert(round_trip);

        //This need to be thoroughly tested further
        std::next_permutation(cells.begin(), cells.end());
        
        //Exit condition in case the max number of permutations is greater than the number of all possible permutations
        iterations++;
        if (iterations >= max_perm*2) {
            break;
        }
    }
  
    // Declare and initialize the optimal path
    std::vector<Cell> optimal_path;
    optimal_path = cells;
    optimal_path.push_back(cells[0]);

    // The optimal path is the one permutation that both meets the time constraint and maximizes the reward 
    for (std::set<std::vector<Cell>>::iterator it = possible_paths.begin(); it != possible_paths.end(); it++) {
        if (get_total_reward((*it)) >= get_total_reward(optimal_path)) {
            optimal_path = (*it);
        } 
    }

    std::set<Cell> unique_cells(optimal_path.begin(), optimal_path.end()); 

    std::cout << "\nThe following is the output of the method. Shown below is the approximation of optimal path that is constrained to a time limit of " <<
    time_period << ". Cells skipped: " << (input_cells.size() - unique_cells.size()) << std::endl;
    print_all_stats(optimal_path);
    print_all_cells(optimal_path);
}

void TSPSolver::nearest_neighbour (std::vector<Cell> cells, int time_period) {

    std::cout << "\n\nRunning nearest neighbour for TSP Simple Definition..." << std::endl;
    std::cout << "Time period is constrained to " << time_period << "." << std::endl;
   
    std::cout << "\nThe following is the input to the method. Shown below are the cells in default order." << std::endl;
    print_all_stats(cells);
    print_all_cells(cells);

    std::vector<Cell> must_visit(cells); 
    std::vector<Cell> round_trip;
    Cell start(cells[0]);

    round_trip.push_back(start); 


    // Remove "start" from must_visit vector
    auto it = std::find(must_visit.begin(), must_visit.end(), start);
    if(it != must_visit.end()) { //it != .end() means the element was not found
        must_visit.erase(it);
    }

    while ((must_visit.size() > 0) &&  (get_total_time(round_trip) < time_period)){
        Cell nearest(must_visit[must_visit.size()-1]);

        // Find the nearest neighbour of the current cell
        for(int i = 0; i < (int) must_visit.size(); i++) {
            if (get_dist(round_trip.back(), must_visit[i]) < get_dist(round_trip.back(), nearest)) {
                nearest = must_visit[i]; 
            }
	    }

        // If adding the nearest cell and the origin causes the path to go over the time limit, don't add it 
        std::vector<Cell> possible_path(round_trip);
        possible_path.push_back(nearest);
        possible_path.push_back(start);
        if (get_total_time(possible_path) > time_period) {
            break;
        }
       
        //Add the nearest neighbour
        round_trip.push_back(nearest);
        
        // Remove "nearest" from must_visit vector
        auto it = std::find(must_visit.begin(), must_visit.end(), nearest);
        if(it != must_visit.end()) { //it != .end() means the element was not found
            must_visit.erase(it);
        }
    
    }

    //Add the origin
    round_trip.push_back(start);

    std::cout << "\nThe following is the output of the method. Shown below is the approximation of optimal path that is constrained to a time limit of " <<
    time_period << ". Cells skipped: " << must_visit.size() << std::endl;
    print_all_stats(round_trip);
    print_all_cells(round_trip);

}

std::vector<Cell> TSPSolver::create_uniform_reward_cells (int x_dimension, int y_dimension) {
    std::vector<Cell> cells_with_uniform_rewards;
    for(int i = 0; i < x_dimension; i++) { // 30 cells: i < 5
	    for(int j = 0; j < y_dimension; j++) { // 30 cells: j < 6
            cells_with_uniform_rewards.push_back(Cell());
            cells_with_uniform_rewards.back().x = i;
            cells_with_uniform_rewards.back().y = j;
            cells_with_uniform_rewards.back().reward = 1.0;
        }
	}
    return cells_with_uniform_rewards;
}

std::vector<Cell> TSPSolver::create_randomized_reward_cells (int x_dimension, int y_dimension) {
    std::vector<Cell> cells_with_random_rewards;
    for(int i = 0; i < x_dimension; i++) { // 30 cells: i < 5
	    for(int j = 0; j < y_dimension; j++) { // 30 cells: j < 6
            cells_with_random_rewards.push_back(Cell());
            cells_with_random_rewards.back().x = i;
            cells_with_random_rewards.back().y = j;
            cells_with_random_rewards.back().reward = rand() % static_cast<int>(31);
            //output = min + (rand() % static_cast<int>(max - min + 1))
        }
	}
    return cells_with_random_rewards;
}
