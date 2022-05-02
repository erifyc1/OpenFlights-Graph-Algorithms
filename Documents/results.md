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
  - Actual time complexity: O(V^2 * log V + E log E) The runtimes have been multiplied by logV and logE because we are using an map with and underlying AVL-like structure to manage marking edges as discovery and cross as well as accessing what edges come out of which nodes.
- Example run description: On a full scale run, BFS will first initialize maps that keep track of which vertices have been visited (0 meaning no visited and 1 meaning visited) and which edges are discovery or cross edges (0 non-existent edge, 1 discovery edge, and 2 cross edge). Then for each node in alphabetical order if a node is labeled as unvisited, it will start a BFS from that node. This brings us to the second function in BFS. The starting node will be pushed to a queue. Then until the queue is empty, front node will be removed and all adjacent unvisited Nodes will be pushed to the end of the queue will the edge is marked 1 for discovery. All edges leading to visited nodes will be marked 2 for cross edge. Lets note that the order in which edges are visited is completely dependent on the order they are inputted in the original data set, Thus the same data in a different order will result in a different BFS spanning tree. The final output of the BFS is a map containing all the edges. Also note that it is possible for multiple edges to exist between 2 airports due to different airlines but the algorithm considers them all to be one edge for the sake of simplicity in the future edges for different airlines could also be implemented.
- Tests implemented: ***********

## Dijkstra’s algorithm 
- Description: Performs a search, but using a priority queue instead of a regular queue for BFS. Provides a route to maximize "ease" of travel.
  - Inputs: start, destination
  - Output: DijkstraResult struct -> path: vector of nodes in path, pathLength: weighted length of path
  - Target time complexity: O(V^2)
  - Actual time complexity: O(V<sup>2</sup>)
- Example run description: 
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
