#include "../include/cursor.hpp"

cursor_t::cursor_t(){
};

void cursor_t::set_pos(word_t *start_word){
	word_p = start_word;
	tile_it = word_p->tiles.begin();
};

int cursor_t::check(){
	auto it = word_p->tiles.begin();
	do{
		if(!(it->cursor_letter == it->letter || it->is_correct)) {
			return false;
		}
		++it;
	}
	while( it != word_p->tiles.end());

	return true;
}
