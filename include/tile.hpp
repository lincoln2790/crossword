#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "const.hpp"
#include "word.hpp"

class word_t;

class tile_t{
    public:
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::Sprite blank_sprite;
	word_t *cross_word_p;
	int is_horiz;
	int is_correct;
	int cross_word_ind;
	char letter;
	char cursor_letter;
	
    tile_t(char l, float x, float y, int is_horiz, int is_correct, sf::Sprite s, sf::Sprite b);
};

#endif
