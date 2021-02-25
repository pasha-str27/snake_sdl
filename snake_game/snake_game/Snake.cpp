#include "Snake.h"

void Snake::init(SDL_Renderer * main_renderer,int block_size)
{
    head.load_from_file("images/head.png", main_renderer);//load image
    this->block_size = block_size;
}

//getters
std::vector<SDL_Rect> Snake::get_positions_boby_parts()
{
    return body_parts;
}

texture& Snake::get_snake_head()
{
    return head;
}

//changing positions
void Snake::change_positions()
{
    if (body_parts.size() == 0)
        return;

    for (size_t i = body_parts.size() - 1; i>=1 ; --i)
        body_parts[i] = body_parts.at(i-1);
    
    body_parts[0] = { head.get_position_x(),head.get_position_y() ,44,44};
}

//adding new body part
void Snake::add_new_body_part()
{
    body_parts.push_back({ head.get_position_x(),head.get_position_y(),block_size,block_size });
}

//remove all body parts
void Snake::reset()
{
    body_parts.clear();
}


Snake::~Snake()
{
    head.free();//remove head
    body_parts.clear();//remove all body parts
}

//void Snake::set_step_x(int x)
//{
//    step_x = x;
//}
//
//void Snake::set_step_y(int y)
//{
//    step_y = y;
//}
//
//int Snake::get_step_y()
//{
//    return step_y;
//}
//
//int Snake::get_step_x()
//{
//    return step_x;
//}
