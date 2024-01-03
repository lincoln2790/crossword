#ifndef WORD_H
#define WORD_H

#include <list>
class game_t;
class tile_t;

class word_t{
	public:
	std::list<tile_t> tiles;
	std::string word;
	int is_correct;
	int is_horiz;
	
	word_t(std::string letters, float x, float y, int is_horiz, int is_correct, game_t *game);
};

#endif
