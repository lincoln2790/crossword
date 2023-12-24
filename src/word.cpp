#include <set>
#include <list>
#include "../include/const.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
#include "../include/func.hpp"
word_t::word_t(sf::Texture *tile_texture, std::string letters, float x, float y, int is_horiz, std::list<word_t> *word_list, int is_correct , std::map<char, std::vector<std::pair<std::string, int>>>* word_map){
	word = letters;
	
	this->is_correct = is_correct;
	
	for(int l = 0; l < letters.length(); l++){
		if(is_horiz){
			tile_t tile(get_tile(letters[l], tile_texture), x+TILE_WIDTH*TILE_SCALE*l, y, letters[l], is_horiz, get_tile(0,tile_texture));
			tiles.push_back(tile);
		} else {
			tile_t tile(get_tile(letters[l], tile_texture), x, y+TILE_HEIGHT*TILE_SCALE*l, letters[l], is_horiz, get_tile(0, tile_texture));
			tiles.push_back(tile);
		}
		if(is_correct){
			word_t w = generate_clue(&tiles.back(), word_map,tile_texture, word_list);
		}
	}
word_list->push_back(*this);
}

