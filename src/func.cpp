#include "../include/const.hpp"
#include "../include/func.hpp"
#include "../include/word.hpp"
#include "../include/tile.hpp"
#include "SFML/Graphics.hpp"
#include <list>
sf::Sprite get_tile(char letter, sf::Texture *tile_texture){
	int x,y;
	x = TILE_WIDTH*((3 + (letter - 'A'))%15);
	y = TILE_HEIGHT*(2 + ((3 + (letter - 'A')) > 15));
	sf::Sprite tile;
	tile.setTexture(*tile_texture);
	tile.setScale(TILE_SCALE,TILE_SCALE);
	tile.setTextureRect(sf::IntRect(x, y, TILE_WIDTH, TILE_HEIGHT));
	return tile;
}
void draw_word(word_t word, sf::RenderWindow *window){
	for(std::list<tile_t>::iterator it = word.tiles.begin(); it != word.tiles.end(); ++it){
		window->draw(it->sprite);
	}
}
