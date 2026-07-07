#include <stdio.h>

#define MAP_SIZE 5

void FillMap(int start[2], int end[2], int *num_blocks);

int main(void) {
    int start[2], end[2], blocks;

    FillMap(start, end, &blocks);

    return 0;
}

void FillMap(int start[2], int end[2], int *num_blocks) {

    printf("Please enter the coordinates of the starting position, ending position, and number of obstacles: ");

    scanf("%d %d", &start[0], &start[1]);
    scanf("%d %d", &end[0], &end[1]);
    scanf("%d", num_blocks); // num_blocks itself is already an address or pointer variable
}