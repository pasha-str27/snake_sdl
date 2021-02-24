#include "Snake.h"

Snake::Snake(SDL_Renderer * main_renderer,int block_size)
{
    head.load_from_file("images/head.png", main_renderer);
    this->block_size = block_size;
}

std::vector<SDL_Rect> Snake::get_positions_boby_parts()
{
    return body_parts;
}

texture& Snake::get_snake_head()
{
    return head;
}

void Snake::change_positions()
{
    if (body_parts.size() == 0)
        return;

    for (int i = body_parts.size() - 1; i>=1 ; --i)
    {
        body_parts[i] = body_parts[i-1];
    }
    body_parts[0] = { head.get_position_x(),head.get_position_y() ,44,44};
}

void Snake::add_new_body_part()
{
    body_parts.push_back({ head.get_position_x(),head.get_position_y(),block_size,block_size });
}

Snake::~Snake()
{
    head.free();
}
