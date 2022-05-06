# Executable names:
EXE = main
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = utils.o heap.o airport.o data_handler.o dijkstra.o main.o

# Add dependencies for Eigen library
EIGEN = /Eigen
USER_CFLAGS = -I Eigen/Eigen


# Use the cs225 makefile template:
include cs225/make/cs225.mk