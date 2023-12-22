
#include "../include/const.hpp"
#include "../include/func.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
tile_t::tile_t(sf::Sprite s, float x, float y ){
    pos = sf::Vector2f(x,y);
	sprite = s;
    sprite.setPosition(pos);
};



