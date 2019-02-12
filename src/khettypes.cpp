#include <khettypes.h>

Move Move::minInit()
{
   Move move;
   move.value = -10000000;
   return move;
}
Move Move::maxInit()
{
    Move move;
    move.value = 10000000;
    return move;
}
