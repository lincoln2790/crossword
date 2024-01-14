#include "../include/tile.hpp"

tile_t::tile_t(char l, float x, float y, int is_horiz, int is_correct, sf::Sprite s, sf::Sprite b):
	letter(l),
	is_horiz(is_horiz),
	is_correct(is_correct),
	sprite(s),
	blank_tile(b),
	cursor_letter(0),
	crossing_word(NULL)
{
    pos = sf::Vector2f(x,y);
	sprite.setPosition(pos);
	blank_tile.setPosition(pos);
	
};



