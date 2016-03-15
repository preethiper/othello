To make my AI tournament-worthy (or at least more tournament-worthy than the
pitiful thing I submitted last week was), I did the following things:

1. Changed the weightage of each possible location (i.e., the heuristic)
   drastically. Corners were weighted VERY heavily (i.e, at 140), while
   positions right next to corners were weighted as low as -40 (because if
   the opponent captures a corner you could be wrecked). Edge locations that
   weren't right next to corners were given weights between and including
   5 and 20, and locations in the middle of the board were given weights of 3.
   This definitely worked because now the AI consciously (or consciously for an
   inanimate object) attempts to get the corners first (even though it may
   take a while), and it also actively avoids positions that are known to suck
   (such as the spots next to the corners).
2. Finally got around to doing Minimax and figuring out the ideal depth (which
   ended up being 2 (counting our turn and their turn as one level, not two
   separate levels)). Seeing as I didn't do minimax before and was just
   picking corners blindly without really predicting my next move, I was pretty
   sure that by looking ahead a few moves (in this case, 4 moves), my AI would
   do better.
3. Being an absolute noob at alpha-beta pruning. Because we are trying to find
   the first move that maximizes our score and minimizes the opponent's score 
   (such that our score ends up being greater than that of our opponent's), we
   stop traversal when we think that any move we find after the "best" move is
   not going to be any better.
4. Attempting to optimize the amount of time needed to look up the score by
   putting it into a hashmap. While this may not be the ideal solution due
   to the number of warnings I get for doing the long long type, 
   because hashmaps give the value of a given key in constant time, this 
   was a good way to look up the score quickly without recalculating it--so
   this entire process is a bit like memoization.
