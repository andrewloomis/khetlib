#include <khettypes.h>

Move Move::minInit()
{
   Move move;
   move.value = -1000000000;
   return move;
}
Move Move::maxInit()
{
    Move move;
    move.value = 1000000000;
    return move;
}
