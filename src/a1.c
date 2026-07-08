/*
a1.c

Source code for FoA assigment 1 where the focus in algorithmic pathfinding
 */

#include <stdio.h>
#include <stdbool.h>

#define MAP_SIZE 5

void FillMap(int start[2], int end[2], int *num_blocks);
void PrintMargin(void);
bool ArrayEqual(int array1[], int array2[], int len);
bool WithinBounds(int coords[2]);

int main(void) {
    int start[2], end[2], blocks;

    FillMap(start, end, &blocks); // fill starting and ending coords and number of blocks
    // note that the spec says that the coords are indexed from 0

    PrintMargin();
    printf("Level 1:\n");
    PrintMargin();

    for (int row = 0; row < MAP_SIZE; row++) {
        for (int col = 0; col < MAP_SIZE; col++) {
            int curr_pos[] = {row, col};

            printf("[");

            if (ArrayEqual(curr_pos, start, 2)) {
                printf("S");
            } else if (ArrayEqual(curr_pos, end, 2))
            {
                printf("E");
            } else {
                printf(" ");
            }
            
            printf("]");
        }
        printf("\n");
    }

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
    nothing, function is purely for mutating coords and counts in main
*/
void FillMap(int start[2], int end[2], int *num_blocks) {
    printf("Please enter the coordinates of the starting position, ending position, and number of obstacles: ");

    scanf("%d %d", &start[0], &start[1]);
    scanf("%d %d", &end[0], &end[1]);
    scanf("%d", num_blocks); // num_blocks itself is already an address
}

/*
Print to terminal the ASCII margin with adjustable length.

Parameters and return are void since it prints out a margin.
*/
void PrintMargin(void) {
    int margin_len = 33;

    for (int i = 0; i < margin_len; i++) {
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


