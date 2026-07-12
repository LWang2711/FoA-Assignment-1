# Level 2 - Naive Pathfinding Limitations and Discussion

## When oes this pathfinding method fail despite expectation?

The algorithm as described only moves in the direction from the start to the end. This means that when getting blocked in a row or column, the pathfinder can only navigate around a block if that step is in the direction of the end. This means that the algorithm cannot move in the opposite direction of the end to get around a group of blocks to eventually reach the exit. A smarter algorithm would have accounted for being able to move in the opposite direction, but this algorithm seems to be purely greedy.

Consider the input:

1 1
4 4
2
1 2
2 1

Which gives the output:

=================================
Level 2:
=================================
SimpleDirections took 0 steps and got stuck.

[ ][ ][ ][ ][ ]
[ ][S][X][ ][ ]
[ ][X][ ][ ][ ]
[ ][ ][ ][ ][ ]
[ ][ ][ ][ ][E]

Even though there is clearly a path to the end, the algorithm cannot reach it since the pathfinder can only move in the direction of the exit.

There are many more cases where since the algorithms always tries and match the rows first, may lead to the pathfinding heading in a direction where it will get stuck in the future. Had it just navigated columns first, it may have been able to reach the end:

Consider the input:

1 1
4 4
2
4 1
3 2

Giving the output:

=================================
Level 2:
=================================
SimpleDirections took 2 steps and got stuck.

[ ][ ][ ][ ][ ]
[ ][S][ ][ ][ ]
[ ][+][ ][ ][ ]
[ ][+][X][ ][ ]
[ ][X][ ][ ][E]

## Analysis of efficiency for larger maps

For larger maps, this many be a clear issue since the pathfinder will move a lot of steps in a direction which may cause it to get stuck in the future. This exacerbates what was highlighted before, that the algorithm isn't desgined to know the actual "human" best way forward. So it just heads in an intuively "bad" direction for a long time if the map is larger. Other than that, a larger map doesn't make this algorithm any more or less naive, rather it struggles in small and large maps alike.

