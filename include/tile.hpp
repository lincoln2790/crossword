#ifndef TILE_H
#define TILE_H
#include "word.hpp"
class word_t;
class tile_t{
    public:
        sf::Sprite sprite;
    	sf::Vector2f pos;
    tile_t(sf::Sprite s, float x, float y, char l, int is_horiz);
	word_t *crossing_word = NULL;
	int is_horiz;
	char letter;
};


#endif
