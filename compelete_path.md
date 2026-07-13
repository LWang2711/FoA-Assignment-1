# Level 4 - Thinking about a Generalised Complete Path

## Reliability of Closest Neighbour Pathfinding

The closest neighbour process will not always work. It it just a normal generalised version of the naive pathfinding, but can easily get stuck too. The reason that it can get stuck despite there being a possible path is due to the inability to backtrack it's steps.

The map has objects either being 'S', 'E', ' ', '+'. The pathfinder can only move onto ' ' spaces and is not designed to be able to retrace its steps in case of getting stuck.

For example, the input:

0 0
4 4
2
3 4
4 3

Has the output:

Level 3:
=================================
[S][+][+][+][+]
[ ][ ][ ][ ][+]
[ ][ ][ ][X][+]
[ ][ ][ ][ ][X]
[ ][ ][ ][ ][E]

Where it gets stuck, whereas the simple directions pathfinding will not get stuck. This is not because closest neighbour process cannot move in the opposite direction of end - in fact it doesn't even know where end is - rather that it cannot backtrack onto where a '+' has already being laid. Technically speaking, simple directions path finding also cannot backtrack, but this isn't a specific issue since in the case of being only allowed to move in the direction of end, the pathfinder will never attempt to backtrack anyways.

## Possible Improvements to Closest Neighbours

As previously said, the issue is that we are not allowed to backtrack. To fix this, we simply extend the order of hierarchy for each direction. Intuitively this look like:

- Check if your neighbour is empty as per ' ', and if yes then move to it.
- We check the neighbours in the following order:
    1. Above
    2. Right
    3. Down
    4. Left
- We then check if your neighbour has already being stepped on as per '+' using the same hierarchy as above.
- We end the function when we find the end or there are no ' ' nor '+' neighbours left to move to.

Using this above hierarchy is crucial since it guarantees that any available empty spot is moved to first before considering retracing it's steps; to prevent an infinite loop of constantly retracing the pathfinding steps.

The pseudocode is actually minimal but also very delicate if actually implemented. Within ```ClosestFreeNeighbour```, none of the overall recursive stucture needs to be changed. Rather, the iteration needs to be doubled up to include '+' after every empty direction has being considered. However, we need a separate for loop since we need to check all of the four directions for empty spaces before checking them for already step on spaces. The pseudocode might be as follows:

if there are no remaining ' ' neighbours:
    for directional index in all directions:
        check neighbour object in directional index direction
        if neighbour object is '+':
            set current position as neigbour position
            return recursive call with new current position
            break
        else if neighbour object is 'E':
            break


