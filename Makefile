# Executable names:
EXE = main
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = utils.o main.o airport.o data_handler.o heap.o dijkstra.o

# Use the cs225 makefile template:
include cs225/make/cs225.mk