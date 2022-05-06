# Video Presentation
https://drive.google.com/file/d/12sbATG_VpfpU_FLi245id5Cjbs4Ck70g/view?usp=sharing

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
  - Target time complexity: O(V<sup>2</sup> + E)
  - Actual time complexity: O(V<sup>2</sup> * log(V) + E * log(E)) The runtimes have been multiplied by logV and logE because we are using an map with and underlying AVL-like structure to manage marking edges as discovery and cross as well as accessing what edges come out of which nodes.
- Example run description: On a full scale run, BFS will first initialize maps that keep track of which vertices have been visited (0 meaning no visited and 1 meaning visited) and which edges are discovery or cross edges (0 non-existent edge, 1 discovery edge, and 2 cross edge). Then for each node in alphabetical order if a node is labeled as unvisited, it will start a BFS from that node. This brings us to the second function in BFS. The starting node will be pushed to a queue. Then until the queue is empty, front node will be removed and all adjacent unvisited Nodes will be pushed to the end of the queue will the edge is marked 1 for discovery. All edges leading to visited nodes will be marked 2 for cross edge. Lets note that the order in which edges are visited is completely dependent on the order they are inputted in the original data set, Thus the same data in a different order will result in a different BFS spanning tree. The final output of the BFS is a map containing all the edges. Also note that it is possible for multiple edges to exist between 2 airports due to different airlines but the algorithm considers them all to be one edge for the sake of simplicity in the future edges for different airlines could also be implemented.
- Tests implemented: ***********

## Dijkstra’s algorithm 
- Description: Performs a search, but using a priority queue instead of a regular queue for BFS. Provides a route to maximize "ease" of travel.
  - Inputs: start, destination
  - Output: DijkstraResult struct -> path: vector of nodes in path, pathLength: weighted length of path
  - Target time complexity: O(V<sup>2</sup>)
  - Actual time complexity: O(V<sup>2</sup>)
- Example run description: Start with a weighted, directed adjacency matrix, where each entry represents the reciprocal of the number of flights between the two places. Then, starting from the start airport, update all connected airports with the distance of the current airport plus the weight of the connection and add the id of the current airport as the previous airport. Add each connecting airport that has not been visited to a priority queue. Continue removing the first element of the priority queue and running the previous steps until the priority queue is empty. Then, starting at the destination airport, back trace through each airport, adding each to a vector. The reverse of this vector is the path.
- Tests implemented: 
  - path of airport to itself
  - impossible path
  - short path test (small data subset)
  - long path test (full dataset)

## Centrality Algorithm (PageRank)
- Description: Determines the most and least central airports (ranked in a schotastic vector), or the probability of ending up at a given airport by taking random flights. Uses the convergence of the probabilities of a Markov matrix. This would also be called the steady state vector, or the eigenvector of the transition matrix to the eigenvalue 1, because multiplying by the transition matrix doesn't change the output. One could normally compute it by finding the eigenvalues, but, given the size of our matrix, we decided to use power iteration, which consists of multiplying an initial vector by the transition matrix many times. We then determine the most and least central airports by finding the maximum and minimum values in the matrix.
  - Inputs: Adjacency matrix of airports
  - Output: getCenter() -> most central airport code, getLeastCenter() -> least central airport code
  - Target time complexity: O(airlines * airports<sup>2</sup>)
  - Actual time complexity: O(airports<sup>3</sup>)
- Example run description: Start with a weighted, directed adjacency matrix, where each entry represents the reciprocal of the number of flights between the two places. Then, normalize each column such that it sums to one, which represents the probability of moving from the airport represented by that column to the airport represented by the row number. Next, multiply a starting vector that has an equal chance of starting at any airport (1/n in each row) by the normalized adjacency matrix 100 times. Take the resulting vector and find the maximum and minimum values which represent the most and least central airports.
- Tests implemented: 
  - Steady state vector properties
  - Convergence of steady state vector
  - Most central airport
  - Least central airport

