### Grade
Not Yet Competent (70%)

Must resubmit (for up to a 90% grade)!

### Comments
A well-written proposal overall, but unfortunately you have not mentioned how you will assign edge weights in your graph. This is the primary issue that needs to be fixed, along with specifying a traversal.

**Leading Question**
The leading question makes sense for the dataset, and can be answered by your proposed algorithms. It's also good that you have kept the visualization portion as an extra option depending on time. For this dataset, I assume your visualization would be something like a graphical projection onto a world map. 

However, you may want to add a component to your leading question about finding the most central/important airports, which would be solved via PageRank.

**Dataset**
The dataset is well described and the correction procedure is very clear. I would say using a map is a good choice for representing your graph, and the storage cost is also correct for the worst case (although for this dataset I would expect the actual storage cost to be much lower than that). 

**Algorithm**
Your algorithms are also clearly detailed. You should specify which traversal you plan to do between DFS and BFS. Based on your leading question, BFS makes more sense to me as the traversal to implement (for finding the shortest path in terms of airports visited).

Unfortunately, you have not detailed how you will assign weights to edges in your graph, which is a requirement for Dijkstra's algorithm. This is the only real issue with your proposal, and the reason you will need to resubmit it. For Dijkstra's, I would recommend either doing the array implementation (which has the O(|V|^2) complexity that you mention), or a priority queue implementation (which has O((|E|+|V|)log|V|) complexity). The most optimal implementation of Dijkstra's algorithm uses a Fibonnaci heap, which may be a bit more advanced.

Your description of PageRank looks good.
