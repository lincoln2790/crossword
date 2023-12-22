
#include "../include/const.hpp"
#include "../include/func.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
word_t::word_t(sf::Texture *tile_texture, std::string letters, float x, float y){
	for(int l = 0; l < letters.length(); l++){
		tile_t tile(get_tile(letters[l], tile_texture), x+20*l, y+20*l);
		tiles.push_back(tile);
	}
}

