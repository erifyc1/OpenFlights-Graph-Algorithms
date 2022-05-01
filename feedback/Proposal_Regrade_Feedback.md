### Grade
Competent (90%)

### Comments
The revised proposal looks good for the most part, but I had one comment/concern. You have included a weighting scheme for Dijkstra's algorithm, but personally I am somewhat unsure of what the goal of this weighting scheme is. If I am understanding your description correctly, you are essentially giving smaller edge weights to airports which have many connections. Additionally, all of the incoming edges for any given airport would have the same value. This could be a valid weighting scheme, however you should then explain in your final submission (or even the mid project check-in meeting) what the output of Dijkstra's algorithm actually signifies for your dataset.

I am approving the current version of the proposal, but I will mention that computing distances between airports via latitude and longitude (using something like Haversine distance) is commonly used for edge weights for this dataset, if you would like to consider that approach as well.
