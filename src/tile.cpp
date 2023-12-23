
#include "../include/const.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
#include "../include/func.hpp"
tile_t::tile_t(sf::Sprite s, float x, float y, char l, int is_horiz){
    pos = sf::Vector2f(x,y);
	sprite = s;
    sprite.setPosition(pos);
	letter = l;
};



