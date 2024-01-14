#include "../include/word.hpp"
#include "../include/game.hpp"

word_t::word_t(std::string letters, std::string clue, float x, float y, int is_horiz, int is_correct, game_t *game) :
	word_str(letters),
	clue_str(clue),
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
			tile_list.push_back(tile);
		} else {
			tile_t tile(l, x, y+TILE_HEIGHT*TILE_SCALE*i, is_horiz, is_correct, game->sprite_map[l], game->sprite_map[0]);
			tile_list.push_back(tile);
		}
	}
	
	game->word_list.push_back(*this);
}

