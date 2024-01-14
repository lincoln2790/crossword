#ifndef CURSOR_HPP
#define CURSOR_HPP

#include "const.hpp"
#include "tile.hpp"
#include "word.hpp"

class cursor_t{
	public:
		word_t *word;
		std::list<tile_t>::iterator tile_it;

		cursor_t();
		void set_pos(word_t *start_word);
		int check();
};
#endif
