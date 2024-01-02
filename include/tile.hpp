#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "word.hpp"
class word_t;
class tile_t{
    public:
        sf::Sprite sprite;
    	sf::Vector2f pos;
		sf::Sprite blank_tile;
    tile_t(sf::Sprite s, float x, float y, char l, int is_horiz, sf::Sprite b, int is_correct);
	word_t *crossing_word = NULL;
	int is_horiz;
	int is_correct;
	char letter;
	char cursor_letter;
	static void get_tile_sprite(char c);
	
};


#endif
