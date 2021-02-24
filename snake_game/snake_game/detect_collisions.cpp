#include "detect_collisions.h"

bool detect_collisions::collision_with_block(SDL_Rect block, SDL_Rect snake_head)
{
    //checking all pixels both rects
    for (int x = block.x,x2= snake_head.x; x < block.x + block.w; ++x,++x2)
    {
        for (int y = block.y, y2 = snake_head.y; y < block.y + block.h; ++y, ++y2)
            if (x == x2 && y == y2)//if pixels coordinates equals
                return true;//return true
    }
    return false;
}
