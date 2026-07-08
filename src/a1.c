/*
a1.c

Source code for FoA assigment 1 where the focus in algorithmic pathfinding
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

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

    // this needs to be a function, fuck
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

    printf("\nThe starting position is at MAP[%d][%d]\n", start[0], start[1]);
    printf("The ending position is at MAP[%d][%d]\n", end[0], end[1]);

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
void FillMap(int start[2], int end[2], int *num_blocks) {
    printf("Please enter the coordinates of the starting position, ending position, and number of obstacles: ");

    do {
        printf("Please enter the coordinates of the starting position: ");
        scanf("%d %d", &start[0], &start[1]);
    } while (!WithinBounds(start));

    do {
        printf("Please enter the coordinates of the ending position: ");
        scanf("%d %d", &end[0], &end[1]);
    } while (!WithinBounds(end));

    do {
        printf("Please how many obstacles will be on the map: ");
        scanf("%d", num_blocks); // num_blocks itself is already an address
    } while (*num_blocks > (int) (pow(MAP_SIZE, 2) - 2)); // there cannot be more blocks than available spaces on the map
    // factoring in space for start and end
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


