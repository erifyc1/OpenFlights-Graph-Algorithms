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


## Running Instructions (with provided data)

1. Pull the latest version of the project from GitHub and run `make` 
2. Run `./main -csv` to generate the compressed airport data file.
3. Run any of the following commands:
##### Commands
| Command            | Description | Example |
| --------------------- |--------------------------------------- | ------------------------- |
| `./main -csv` | Generates a compressed flight file of the provided routes.csv for use in the algorithms. | `./main -csv` |
| `./main -dk <source> <destination>` | Returns shortest weighted path and path length between input airports. | `./main -dk STL LIL` |
| `./main -bfs <source> <destination>` | Returns the shortest path length between input airports. | `./main -bfs STL LIL` |
| `./main -pr <T/F>` | Returns most or least central airport, with T or F respectively. | `./main -pr T` |
### Running Instructions (with custom data)
1. Pull the latest version of the project from GitHub and run `make` 
2. Replace `/data/routes.csv` with an appropriately formatted flight dataset.
3. Run `./main -csv` to generate the compressed airport data file.
4. Run any of the available commands.

### Running Test Suite
1. Pull the latest version of the project from GitHub and run `make test` 
2. Run `./test` (tests are located in `/tests/tests.cpp`)

### Tests included
- *************