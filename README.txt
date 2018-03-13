Division of labor:

We got together several times to work on Othello; we both implemented
the different bot algorithms separately but chose to use Lia's
implementation for all (sad) algorithms as hers gave better results.
Bots included the heuristic function, original implementation, and
hard-coded two layer minima function. Our alpha-beta pruning still
does not function properly.

Advances to algorithm:

We couldn't get our Othello bot to function better than the really basic
heuretic/hardcoded minimax, which is a Little Bit Tragic.

The general idea I went with was that minimaxing to any > 1 degree with a
sufficiently thorough heuretic would be able to beat ConstantTimePlayer,
because we knew we wouldn't rly have the time or talent to implement
something that could actually win.

I followed the general idea from my previous heuretic for this one: tons
of extra points for corners, general extra points for sides, etc. The
implementation seemed a little worse this time, partially because I wasn't
adding the score as the move was being made anymore (that kind of
temporary measure makes more sense for Othello, since it matters if it's
newly put in vs. changed by the opponent). On top of that, I added an
alpha-beta pruning algorithm, which is pretty standard and
self-explanatory.

Unfortunately, the implementation went wonky somewhere, because the
algorithm will barely beat ConstantTimePlayer when set to depth 2 and
loses spectacularly when set to dept 4. The min-maxing part seems fine,
from the copious debugging I did, but it gets messed up when it's brought
back to the maxing or something, and there might be something wrong with
the scoring system as well.
