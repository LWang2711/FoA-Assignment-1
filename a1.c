#include <stdio.h>

#define map_size 5

int FillMap();

int main(void) {
    int map_details = FillMap();

    printf("%d", map_details[0][0]);
}

int FillMap() {
    unsigned int start[2], end[2], blocks;

    scanf("%d %d\n%d %d\n%d", &start[0], &start[1], &end[0], &end[1], &blocks);

    int map_details[] = {start, end, blocks};

    return map_details;
}