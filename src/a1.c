/*
a1.c

Source code for FoA assigment 1 where the focus in algorithmic pathfinding.
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAP_SIZE 5

#define COORD_DIM 2

void FillMap(char MAP[MAP_SIZE][MAP_SIZE], int start[COORD_DIM], int end[COORD_DIM]);
void PrintMap(char MAP[MAP_SIZE][MAP_SIZE]);
void SimpleDirections(char MAP[MAP_SIZE][MAP_SIZE], int start[COORD_DIM], int end[COORD_DIM]);
int DirectionalMove(int curr_dim, int target_dim);
void PrintHeader(int level);
bool ArrayEqual(int array1[], int array2[], int len);
bool WithinBounds(int coords[2]);
bool BlockPresent(int num_blocks, int curr_position[COORD_DIM], int block_coords[num_blocks][COORD_DIM]);

int main(void) {
    int start[2], end[2];
    char MAP[MAP_SIZE][MAP_SIZE];

    FillMap(MAP, start, end);

    int level = 1;

    PrintHeader(level);

    PrintMap(MAP);
 
    printf("\nThe starting position is at MAP[%d][%d]\n", start[0], start[1]);
    printf("The ending position is at MAP[%d][%d]\n", end[0], end[1]);

    level = 2;

    PrintHeader(level);

    SimpleDirections(MAP, start, end);

    PrintMap(MAP);

    return 0;
}

/* 
Mutate input integer array and integer to be filled with starting and ending coordinates,
and the number of blocks on the map.

Parameters:
    start is two int array which store the vertical and horizontal coords of starting position
    end is same vain as start but for ending position coords 
    num_blocks is pointer to int to allow pass by pointer to alter blocks in main

Returns:
    nothing, function is purely for mutating coords and counts so that it persists in main
*/
void FillMap(char MAP[MAP_SIZE][MAP_SIZE], int start[2], int end[2]) {

    do {
        printf("Please enter the coordinates of the starting position: ");
        scanf("%d %d", &start[0], &start[1]);
    } while (!WithinBounds(start));

    do {
        printf("Please enter the coordinates of the ending position: ");
        scanf("%d %d", &end[0], &end[1]);
    } while (!WithinBounds(end));

    int num_blocks;

    do {
        printf("Please enter how many obstacles will be on the map: ");
        scanf("%d", &num_blocks);
    } while (num_blocks > (int) (pow(MAP_SIZE, 2) - 2)); // there cannot be more blocks than available spaces on the map
    // factoring in space for start and end

    // store block coords as same format as input
    int block_coords[num_blocks][COORD_DIM];

    for (int block = 0; block < num_blocks; block++) {
        printf("Please enter the coordinates of block %d: ", block + 1);
        scanf("%d %d", &block_coords[block][0], &block_coords[block][1]);
    }

    for (int row = 0; row < MAP_SIZE; row++) {
        for (int col = 0; col < MAP_SIZE; col++) {
            int curr_pos[] = {row, col}; // could use pointer for better aliasing?

            if (ArrayEqual(curr_pos, start, COORD_DIM)) {
                MAP[row][col] = 'S';
            } else if (ArrayEqual(curr_pos, end, COORD_DIM)) {
                MAP[row][col] = 'E';
            } else if (BlockPresent(num_blocks, curr_pos, block_coords)) {
                MAP[row][col] = 'X';
            } else {
                MAP[row][col] = ' ';
            }
        }
    }
}

/*
Prints the map with start, end, and block in ASCII form.

Parameter:
    MAP tracks what object is at each position via char indicators, and is two dimensional
    array of specified size.

Returns:
    nothing, purely for printing out MAP in ASCII form.
*/
void PrintMap(char MAP[MAP_SIZE][MAP_SIZE]) {
    for (int row = 0; row < MAP_SIZE; row++) {
        for (int col = 0; col < MAP_SIZE; col++) {
            printf("[%c]", MAP[row][col]);
        }
        printf("\n");
    }
}

/* 
Takes in the dimensions of a map and draws out the simple directional path and the number
of steps taken to go froms start to finish. Path may be not possible using basic directions in
which case path will terminate on step which gets stuck.

Parameters:
    MAP the two-dimensional array which contains where there is start, end, and blocks as chars.
    coords of both start and end in standard coordinate form of rows and cols respectively.

Returns:
    nothing, since only tracks the path and number of step and prints out both assuming not getting stuck
    otherwise will print out that it got stuck
*/
void SimpleDirections(char MAP[MAP_SIZE][MAP_SIZE], int start[COORD_DIM], int end[COORD_DIM]) {
    // don't know if there is any point of keeping two dimensions in array form instead of
    // separately for clarity purposes

    int curr_pos[COORD_DIM] = {start[0], start[1]};
    int tar_pos[COORD_DIM] = {end[0], end[1]};
    
    int step_count = 0;

    int next_pos[COORD_DIM]; // tracks index of next position of interest
    char next_obj; // tracks what object is at next position of interest

    while (curr_pos[0] != tar_pos[0]) { // move for rows first
        next_pos[0] = curr_pos[0] + DirectionalMove(next_pos[0], tar_pos[0]);
        next_obj = MAP[next_pos[0]][curr_pos[1]];

        // must make sure that next position is clear before changing any indicies or steps
        if (next_obj == ' ') { // if next row is clear to move
            MAP[next_pos[0]][curr_pos[1]] = '+';
            step_count++;
            curr_pos[0] = next_pos[0];
        } else if (next_obj == 'X') { // if row is blocked
            next_pos[1] = curr_pos[1] + DirectionalMove(curr_pos[1], tar_pos[1]);
            next_obj = MAP[curr_pos[0]][next_pos[1]];
            if (next_obj == 'X') { // case of getting stuck
                printf("SimpleDirections took %d steps and got stuck.\n\n", step_count);
                return;
            } else if (next_obj == ' ') { // if next col is clear to move
                MAP[curr_pos[0]][next_pos[1]] = '+';
                step_count++;
                curr_pos[1] = next_pos[1];
            }
        } else if (next_obj == 'E') { // if the target had been reached
            curr_pos[0] = tar_pos[0];
            step_count++;
            printf("SimpleDirections took %d steps to find the goal.\n\n", step_count);
        }
    }

    /* copy and paste forced repetition here which could maybe be refactored better? Switching out which
    one is current and which one is next based on whether rows or columns are to be navigated?*/
    // this most likely needs refactoring since it's super awkward, though not a real project though

    while (curr_pos[1] != tar_pos[1]) { // move for cols second
        next_pos[1] = curr_pos[1] + DirectionalMove(next_pos[1], tar_pos[1]);
        next_obj = MAP[curr_pos[0]][next_pos[1]];

        if (next_obj == ' ') {
            MAP[curr_pos[0]][next_pos[1]] = '+';
            step_count++;
            curr_pos[1] = next_pos[1];
        } else if (next_obj == 'X') { // if next col is blocked
            next_pos[0] = curr_pos[0] + DirectionalMove(curr_pos[0], tar_pos[0]);
            next_obj = MAP[next_pos[0]][curr_pos[1]];
            if (next_obj == 'X') { // case of getting stuck
                printf("SimpleDirections took %d steps and got stuck.\n\n", step_count);
                return;
            } else if (next_obj == ' ') { // if next row is clear to move
                MAP[next_pos[0]][curr_pos[1]] = '+';
                step_count++;
                curr_pos[0] = next_pos[0];
            }
        } else if (next_obj == 'E') { // if the target had been reached
            curr_pos[1] = tar_pos[1];
            step_count++;
            printf("SimpleDirections took %d steps to find the goal.\n\n", step_count);
        }
    }
}

/* 
Returns the index change value in one dimension which should be taken to go from an
origin to a target.

Parameters:
    curr_dim is the index position value of the origin position in whatever dimension.
    target_dim is the index position value of the target position in whatever dimension.

Returns:
    -1 if origin should move backwards towards target in dimension
    1 if origin should move forward towards target in dimension
    0 if origin has already reached target in dimension
*/
int DirectionalMove(int curr_dim, int target_dim) {
    int toward_step;

    if (curr_dim > target_dim) {
        toward_step = -1;
    } else if (curr_dim < target_dim) {
        toward_step = 1;
    } else {
        toward_step = 0;
    }

    return toward_step;
}

/*
Print to terminal the ASCII form of the level header with adjustable length.

Parameters and return are void since it prints out a margin.
*/
void PrintHeader(int level) {
    int margin_len = 33;

    for (int i = 0; i < margin_len * 2; i++) {
        if (i == margin_len) {
            printf("\nLevel %d:\n", level);
        }
        printf("=");
    }
    printf("\n");
}

/* 
Check whether two arrays containing ints of an expected same length are the same.

Parameters:
    array1 and array2 are both arrays containing ints which are expected to be at least
    the same size.

Return:
    true if array1 and array2 have the same elements.
    false if otherwise.
*/
bool ArrayEqual(int array1[], int array2[], int len) {
    for (int i = 0; i < len; i++) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }

    return true;
}

/* 
Checks whether coords are valid and within the bounds of map itself.

Parameters:
    coords is int array which are the y and x coordinates of anything on the map

Return:
    returns true if within the map geometry
    returns false if otherwise
*/
bool WithinBounds(int coords[2]) {
    if (coords[0] >= 0 && coords[0] < MAP_SIZE &&
        coords[1] >= 0 && coords[1] < MAP_SIZE) {
            return true;
        } else {
            return false;
        }
}


/*
Checks whether a position has a block on it.

Parameters:
    num_blocks the number of blocks as an int.
    curr_position in standard {row, col} form as int.
    block_coords which is a num_block by standard coord dimension two-dimensional array which stores
    the coords of all the blocks.

Returns:
    true if any of the blocks match current position.
    false if none of the blocks match the current position.
*/
bool BlockPresent(int num_blocks, int curr_position[COORD_DIM], int block_coords[num_blocks][COORD_DIM]) {
    for (int block = 0; block < num_blocks; block++) {
        if (ArrayEqual(block_coords[block], curr_position, COORD_DIM)) {
            return true;
        }
    }

    return false;
}


