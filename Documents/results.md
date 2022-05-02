# Our Leading Questions & Results
- Q: How should security funding should be distributed to different airports?
- A: We created a PageRank algorithm which can determine which airports are the most central and therefore, should have the most security funding allocated. 
  - Upon running the test we determined ATL / Atlanta Airport is the highest ranked airport in PageRank. Therefore, the most security should be allocated here. 
  - On the other hand, we identified BSS / Balsas Airport (in Balsas, Brazil) to be the lowest ranked airport in PageRank. This airport is the least imporant for the whole airport network.
- Q: Can we create methods to find the shortest path between airports?
- A: We create BFS and Dijkstra's algorithms which can give us the shortest path by number of flights needed and by "ease" of travel respectively.
  - BFS finds the shortest number of flights needed to get from A to B
  - Dijkstra's algorithm takes into account that it is "easier" to travel on a route where there are more flights offered. So, the path may be more flights, but booking / coordinating these flights would theoretically be easier.

# Graph Algorithms
## BFS 
- Description: Performs a Breadth-first search of the flight routes.
  - Inputs: startNode, endNode
  - Output: vector of nodes in path (empty if path does not exist)
  - Target time complexity: O(V^2 + E)
  - Actual time complexity: ***********
- Example run description: ***********
- Tests implemented: ***********

## Dijkstra’s algorithm 
- Description: Performs a search, but using a priority queue instead of a regular queue for BFS. Provides a route to maximize "ease" of travel.
  - Inputs: start, destination
  - Output: DijkstraResult struct -> path: vector of nodes in path, pathLength: weighted length of path
  - Target time complexity: O(|V|^2)
  - Actual time complexity: ***********
- Example run description: ***********
- Tests implemented: ************

## PageRank
- Description: Determines the most and least central airports (ranked in a vector), or the probability of ending up at a given airport by taking random flights. Uses the convergence of the probabilities of a Markov matrix. 
  - Inputs: none
  - Output: getCenter() -> most central airport code, getLeastCenter() -> least central airport code
  - Target time complexity is O(K\*N), K = number of iterations, N = space requirement, so (K\*airlines*airports^2). 
  - Target space complexity: O(airlines*airports^2)
  - Actual time complexity: ***********
- Example run description: ***********
- Tests implemented: ************
