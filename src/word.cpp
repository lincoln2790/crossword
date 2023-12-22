
#include "../include/const.hpp"
#include "../include/func.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
word_t::word_t(sf::Texture *tile_texture, std::string letters, float x, float y, char is_horiz){
	for(int l = 0; l < letters.length(); l++){
		if(is_horiz){
			tile_t tile(get_tile(letters[l], tile_texture), x+TILE_WIDTH*TILE_SCALE*l, y);
			tiles.push_back(tile);
		} else {
			tile_t tile(get_tile(letters[l], tile_texture), x, y+TILE_HEIGHT*TILE_SCALE*l);
			tiles.push_back(tile);
		}
	}
}

