
#include "../include/const.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
//#include "../include/func.hpp"
tile_t::tile_t(sf::Sprite s, float x, float y, char l, int is_horiz, sf::Sprite b){
    pos = sf::Vector2f(x,y);
	sprite = s;
    sprite.setPosition(pos);
	blank_tile = b;
    blank_tile.setPosition(pos);
	letter = l;
	this->is_horiz = is_horiz;
};



