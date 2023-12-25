#include <set>
#include "../include/const.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
#include "../include/cursor.hpp"
#include "../include/func.hpp"
cursor_t::cursor_t(word_t *start_word){
	word = start_word;
	tile_it = word->tiles.begin();
};
