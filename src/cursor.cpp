#include "../include/cursor.hpp"
cursor_t::cursor_t(){
};

void cursor_t::set_pos(word_t *start_word){
	word = start_word;
	tile_it = word->tiles.begin();
};
