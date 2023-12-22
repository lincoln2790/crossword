#include "../include/const.hpp" 
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
