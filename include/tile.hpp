#ifndef TILE_H
#define TILE_H
#include "word.hpp"
class word_t;
class tile_t{
    public:
        sf::Sprite sprite;
    	sf::Vector2f pos;
		sf::Sprite blank_tile;
    tile_t(sf::Sprite s, float x, float y, char l, int is_horiz, sf::Sprite b);
	word_t *crossing_word = NULL;
	int is_horiz;
	char letter;
	
};


#endif
