#include "../include/tsp_solver.h"

#include <iostream>
#include <cmath>


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
