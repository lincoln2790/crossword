#include "../include/cursor.hpp"
cursor_t::cursor_t(word_t *start_word){
	word = start_word;
	tile_it = word->tiles.begin();
};
