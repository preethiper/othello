To make my AI tournament-worthy (or at least more tournament-worthy than the
was pitiful state I submitted last week was), I did the following things:

1. Changed the weightage of each possible location (i.e., the heuristic)
   drastically. Corners were weighted VERY heavily (i.e, at 140), while
   positions right next to corners were weighted as low as -40 (because if
   the opponent captures a corner you could be wrecked). Edge locations that
   weren't right next to corners were given weights between and including
   5 and 20, and locations in the middle of the board were given weights of 3.
2. Finally got around to doing Minimax and figuring out the ideal depth, which
   
