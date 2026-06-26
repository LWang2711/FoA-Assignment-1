# FoA Assignment-1
Repo for all the source code and tests and output for assignment 1 of FoA which focuses on pathfinding and basic algorithmic thinking related to it.

Main idea is that we are in a 2-dimensional map with a maze overlapped on top.

## Input-Format
Inputs look like minimum three line .txt files:

- x and y of the **starting** position, given as two positive integers representing the row (y coordinate) and column (x coordinate).

- x and y of the **ending** position, as the same format as the starting positon above.

- One positive integer representing the number of block or obstacles on the map.

## Use-Instructions
Compile the source file as per:

clang a1.c -o a1.c

to assign the .c source code the same name but compiled as executable.

./a1.c < input.txt

to run it with input redirection operator <, which just means that you are running the executable and then automatically inputting hte .txt into the executed request.

## Assignment-Parts

### Level-1:-Mapping-Out-the-World
