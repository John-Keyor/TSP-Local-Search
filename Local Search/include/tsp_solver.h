#pragma once

#include <vector>

struct Cell {
	int x;
	int y;
	double reward;
};

class TSPSolver {
	public:
		TSPSolver();
	private:
		// Input: search_cells - set of cells to be searched
		// Output: total_reward - reward acquired from searched_cells
		double get_total_reward(std::vector<Cell> search_cells);
		// Input: cell1, cell2 - cells
		// Output: distance - euclidean distance between cells
		double get_dist(Cell cell1, Cell cell2);
		// Input: ordered_search_cells - set of cells to be searched in order
		// Output: total_distance - distance traversed to visit all cells
		double get_total_dist(std::vector<Cell> ordered_search_cells);
		// Input: ordered_search_cells - set of cells to be searched in order
		// Output: time - time expended to visit all cells
		double get_total_time(std::vector<Cell> ordered_search_cells);
	public:

	private:
		// time (in seconds) to search a cell
		const double CELL_SEARCH_TIME = 6;
		// time (in seconds) to travel 1 unit
		const double TRAVEL_SPEED = 0.5;


};
