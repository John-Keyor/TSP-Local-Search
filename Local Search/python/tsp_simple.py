import matplotlib.pyplot as plt, numpy as np, doctest, copy, random
from itertools import permutations, islice

random.seed(996)
def total_reward(points):
    return sum(point[2] for point in set(points))


def distance(point1, point2):
    '''
    Calculate the Euclidean distance between 2 cells
    '''
    return ((point1[0] - point2[0])**2 + (point1[1] - point2[1])**2) ** 0.5


def total_distance(points):
    '''
    Calculate the total distance of a path
    '''
    return sum([distance(point, points[index + 1]) for index, point in enumerate(points[:-1])])

def total_time(points):
    '''
    It takes 6 seconds to search a cell. It takes 0.5 seconds to travel 1 unit of distance.
    '''

    # use len(set(points)) instead of len(points) so that the we don't search one cell more than once

    return (6*len(set(points))) + (0.5*total_distance(points))


def travelling_salesman(points, max_perm, time_period, start=None):
    if start is None:
        start = points[0]
  
    possible_paths = []

    # The islice(..) is to have a max number of permutations that we iterate through (e.g. We only look at 1000 permutations of the 30 cells)
    for perm in islice(permutations(points), max_perm):
        if perm[0] == start:
            # Before we add this path to the list of possible paths, we first need to check if it can be traversed under the required time
            # Because the rewards across the cells are randomized, the path we choose is Start Point (0, 0) + Cells in descending order of 
            # reward for n cells (e.g. the 5 cells with the most reward) + End Point (0, 0)

            constructed_path = copy.copy([perm[0]]+sorted(perm[1:], key=lambda x:x[2], reverse=True)+[perm[0]])
            slice_counter = 1
            while (total_time(constructed_path) > time_period): 
                constructed_path = copy.copy([perm[0]]+sorted(perm[1:], key=lambda x:x[2], reverse=True)[:-slice_counter]+[perm[0]])
                #print("Total time for this path is ", total_time(constructed_path))
                #print(constructed_path)
                slice_counter += 1
            possible_paths.append(copy.copy(constructed_path))
            
    print(len(possible_paths))
    return min(possible_paths, key=total_distance)


def optimized_travelling_salesman(points, time_period, start=None):
    
    '''
    Tries to maximize the reward by going to as many cells as possible. Doesn't try to go to the cells with the most rewards first to save time.
    '''

    cells = copy.copy(points)
    
    if start is None:
        start = points[0]
    must_visit = copy.copy(points)
    path = [start]
    must_visit.remove(start)
    while (must_visit and total_time(path) < time_period):
        nearest = min(must_visit, key=lambda x: distance(path[-1], x))
        if (total_time(path + [nearest]) > time_period):
            break
        path.append(nearest)
        must_visit.remove(nearest)
    path.append(start)
    start = None

    return path 


def plot(path, x, y, subplot, title, distance, time, reward, cells):
    #Takes path and plots it 
    
    plt.subplot(subplot)
    plt.title(title)
    plt.xlabel("Total distance travelled: " + str(distance) + "\nTotal time: " + str(time) + " seconds\nTotal reward: " + str(reward))
    plt.scatter(x, y, s = 20, c = 'b')
    for i, txt in enumerate(zip(*cells)[2]):
        plt.annotate(str(txt), cells[i][:2], tuple(0.05+cells[i][j] for j in range(2)))
    plt.plot(zip(*path)[0], zip(*path)[1], '-')
    plt.grid()
    plt.suptitle('TSP Simple Definition, Uniform Reward, Time limit: 200s', fontsize=16)
    #plt.show()

if __name__ == "__main__":
    
    x = [j for j in range(5) for i in range(6)]
    y = [j for i in range(5) for j in range(6)]
    reward_matrix = [[1] for i in range(30)] #30x1 matrix where 30 = number of cells, 1 = number of time periods 

    #30 tuples
    cells = zip(x, y)

    #plt.subplots(1, 2, sharey=True)
    
    max_permutations = 1000

    time_period = 60 #seconds. Searching a cell takes 12 seconds. 
    

    cells_with_random_rewards = zip(x, y, random.sample(range(40), 30)) 
    cells_with_uniform_rewards = zip(x, y, [1 for i in range(30)] )

    '''
    >>> sorted(cells_with_uniform_rewards, key=lambda x:x[2], reverse=True) == cells_with_uniform_rewards
    True
    '''

    final_local_plan = travelling_salesman(cells_with_uniform_rewards, max_permutations, 200)
    final_local_intelligent_plan = optimized_travelling_salesman(cells_with_uniform_rewards, 200)

    print("Total distance travelled for uniform brute force route ", total_distance(final_local_plan), " Total time ", total_time(final_local_plan))
    print("Total distance travelled for uniform optimized route ", total_distance(final_local_intelligent_plan), " Total time ", total_time(final_local_intelligent_plan) )

    #print(final_local_intelligent_plan)
    plt.figure(1)
    plot(final_local_plan, x, y, 121, "Brute force", total_distance(final_local_plan), total_time(final_local_plan), total_reward(final_local_plan), cells_with_uniform_rewards)
    plot(final_local_intelligent_plan, x, y, 122, "Nearest Neighbour", total_distance(final_local_intelligent_plan),total_time(final_local_intelligent_plan), total_reward(final_local_intelligent_plan), cells_with_uniform_rewards)
    
    plt.figure(2)
    final_local_plan = travelling_salesman(cells_with_random_rewards, max_permutations, 200)
    final_local_intelligent_plan = optimized_travelling_salesman(cells_with_random_rewards, 200)

    print("Total distance travelled for random brute force route ", total_distance(final_local_plan), " Total time ", total_time(final_local_plan))
    print("Total distance travelled for random optimized route ", total_distance(final_local_intelligent_plan), " Total time ", total_time(final_local_intelligent_plan) )
    plot(final_local_plan, x, y, 121, "Brute force", total_distance(final_local_plan), total_time(final_local_plan), total_reward(final_local_plan), cells_with_random_rewards)
    plot(final_local_intelligent_plan, x, y, 122, "Nearest Neighbour", total_distance(final_local_intelligent_plan),total_time(final_local_intelligent_plan), total_reward(final_local_intelligent_plan), cells_with_random_rewards)
    plt.suptitle('TSP Simple Definition, Random Reward, Time limit: 200s', fontsize=16) 

    plt.show()
