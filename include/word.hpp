#ifndef WORD_H
#define WORD_H

#include <list>
#include <string>
#include "const.hpp"
#include "tile.hpp"

class tile_t; // words contain tiles, tiles contain a pointer to a crossing word
class game_t; // game contains word list, word constructor requires access to game's word list

class word_t{
	public:
	std::list<tile_t> tile_list;
	std::string word_str;
	std::string clue_str;
	int is_correct;
	int is_horiz;
	
	word_t(std::string word_str, std::string clue_str, float x, float y, int is_horiz, int is_correct, game_t *game_p);
};

#endif
