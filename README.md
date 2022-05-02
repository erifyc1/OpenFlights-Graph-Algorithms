# MiniGamerways
## CS225 Final Project by
- Andrew Elysee (aelys2)
- Evan Coats (efcoats2)
- Jacob Stolker (stolker2)
## Project Files and Deliverables

### Code
- airport.cpp/h
- data_handler.cpp/h
- dijkstra.cpp/h
- heap.cpp/h
- utils.cpp/h
- main.cpp

### Tests
- tests/tests.cpp
### Data
- data/routes.csv
    - raw csv data
- data/compressed.txt
    - compressed format generated by program

### Report
- /Documents/results.md
### Video Presentation
- https://drive.google.com/file/d/12sbATG_VpfpU_FLi245id5Cjbs4Ck70g/view?usp=sharing


## Running Instructions

1. Pull the latest version of the project from GitHub and run `make`
2. Run the executable with one of the following commands:
#### table 

| Command | Description | Example |
| ------------------ |--------------------------------------------------------------------- | --------------------- |
| `./main -csv` | Generates a compressed file version of the provided data/routes.csv to be used in the algorithms. | `./main -csv` |
| `./main -dk <source> <destination>` | Returns shortest weighted path between source and destination airports and the weighted path length. | `./main -dk STL LIL` |
| `./main -bfs <source> <destination>` | Returns the length of the shortest path between source and destination airports. | `./main -bfs STL LIL` |
| `./main -pr <T/F>` | Returns most or least central/important airport. T = centralized. F = decentralized. | `./main -pr T` |


#### table end
Running Instructions – You should provide full instructions on how to build and run your executable, including how to define the input data and output location for each method. You should also have instructions on how to build and run your test suite, including a general description on what tests you have created. It is in your best interest to make the instructions (and the running of your executables and tests) as simple and straightforward as possible.