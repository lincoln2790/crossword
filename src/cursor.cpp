#include "../include/cursor.hpp"
cursor_t::cursor_t(){
};

void cursor_t::set_pos(word_t *start_word){
	word = start_word;
	tile_it = word->tiles.begin();
};

int cursor_t::check(){
	auto it = word->tiles.begin();
	do{
		if(!(it->cursor_letter == it->letter || it->is_correct)) {
			return false;
		}
		++it;
	}
	while( it != word->tiles.end());

	return true;
}
