#include <set>
#include <list>
#include "../include/const.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
#include "../include/cursor.hpp"
#include "../include/func.hpp"
#include "../include/game.hpp"
//word_t::word_t(sf::Texture *tile_texture, std::string letters, float x, float y, int is_horiz, std::list<word_t> *word_list, int is_correct , std::map<char, std::vector<std::pair<std::string, int>>>* word_map){
word_t::word_t(std::string letters, float x, float y, int is_horiz, int is_correct, game_t *game) :
	word(letters),
	is_correct(is_correct),
	is_horiz(is_horiz)
	{
	
	
	//std::cout << letters << std::endl;
	for(int i = 0; i < letters.length(); i++){
		char l = letters[i];
		if(is_horiz){
			//std::cout << x << std::endl;
			//std::cout <<  << std::endl;
			tile_t tile(l, x+TILE_WIDTH*TILE_SCALE*i, y, is_horiz, is_correct, game->sprite_map[l], game->sprite_map[0]);
			tiles.push_back(tile);
		} else {
			tile_t tile(l, x, y+TILE_HEIGHT*TILE_SCALE*i, is_horiz, is_correct, game->sprite_map[l], game->sprite_map[0]);
			tiles.push_back(tile);
		}
		if(is_correct){
			game->generate_clue(&(--tiles.end()), i);
		}
		
	}
	game->word_list.push_back(*this);
}

