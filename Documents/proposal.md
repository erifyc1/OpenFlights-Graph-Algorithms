# Leading Question
- We seek to create a search tool that can give various routes between given airports. This would include the least number of stops as well as connecting using only a specific set of airlines. Time permitting, we also want to visualize how certain airport networks are connected across multiple states, countries, or continents as well as visualizing airport networks for certain sets of airlines. We will also find the most important airports to the structure. To determine how security funding should be distributed to different airports, we want to determine which airports, when removed, would have the most drastic effect on the PageRank scores.
# Dataset Acquisition and Processing

- Our input dataset came from [Open Flights](https://www.kaggle.com/datasets/open-flights/flight-route-database)/is a CSV file containing flights between different airports via different airlines. It contains 9 different columns. The first and second columns contain the airline identifiers. The third and fourth columns contain departure airport identifiers. The fifth and sixth columns contain the destination airport identifiers. The last few columns are irrelevant for our project. The data set contains 59036 routes between 3209 airports on 531 airlines spanning the globe. It is important to note that all routes are directional.
# Data Correction
- To parse our input data, we will first check to see if the correct data types are used in each category and that each item has a value. We will start out by simply removing these entries (removing a flight) since each individual entry is not very significant to remove in a dataset of over 60,000 entries. Additionally, because our analysis of the dataset heavily relies on certain data points such as airport ID, filling these points with some normalized values could mess with our conclusions. We will also likely drop certain columns, because not all categories are relevant to our analyses. (ex. Codeshare and stops columns in our dataset)
# Data Storage
- Our input data comes in a CSV file, 
  We will use a map data structure as an intermediate data structure and our final output will depend on a directed graph data structure. The map data structure will essentially serve the same purpose as a graph adjacency matrix. The keys will be all the airports and the values will be vectors of structs containing flight data relating to that particular airport. This intermediate data structure can easily be manipulated by various functions we will implement and eventually be converted into a directed graph data structure.
  The worst case space complexity usage for the map data structure is O(airlines * airports^2 ).

# Graph Algorithms
## BFS 
- Inputs: startNode, endNode
- Output: vector of nodes in path (empty if path does not exist)
- Theoretical time complexity O(V + E)
- Target time complexity O(V^2 + E) (worst of both implementation cases)

## Dijkstra’s algorithm 
- The input will be the departure airport and destination airport, as well as preferred airlines. The output will be the shortest path between the 2 nodes. The Theoretical time complexity should be O(|V|^2) in the worst case using the Array implementation.
- To produce a graph with weighted edges required for Dijkstra's algorithm, we will divide each column of the adjacency matrix by the sum of the entries in that column. Since our dataset contains flight data rather than airport data, there will be no columns that sum to zero, so that edge case will not have to be considered.
## PageRank (centrality algorithm) 
- We will implement the PageRank algorithm to determine the most central airports, or the probability of ending up at a given airport by taking random flights. In order to do this, we will use the convergence of the probabilities of a Markov matrix. 
- The time complexity is O(K\*N), K = number of iterations, N = space requirement, so (K\*airlines*airports^2). 
- The space complexity is O(airlines*airports^2).

- All of these will be used to find traversals between certain nodes of the directed graph of flights. 
- We will also print out the amount of time that each of the functions take to figure out which algorithm is preferred. 

# Timeline
- Mid-Project deadline: April 15th (3 weeks until)
## First week - April 2nd
- Data acquisition: find dataset
- Data storage and processing: implement a method of storing and retrieving the data
## Second week - April 8th
- Data processing: Implement a method for converting the retrieved data into a graph
- Implement either the BFS algorithm (whichever we decide)
## Third week - April 15th
- Complete Dijkstra’s algorithm

## Before May 6th
- Complete PageRank algorithm
- Complete visualization
 
