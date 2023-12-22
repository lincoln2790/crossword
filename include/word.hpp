#ifndef WORD_H
#define WORD_H
#include "tile.hpp"


#include <list>
class word_t{
	public:
	sf::Vector2f pos;
	std::list<tile_t> tiles;
	word_t(sf::Texture *tile_texture, std::string letters, float x, float y, char is_horiz);
};

#endif
