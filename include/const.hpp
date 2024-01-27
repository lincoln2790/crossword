#ifndef CONST_H
#define CONST_H

#include <string>
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
/*
Naming Conventions
- All CAPS for constants and #define variables
Suffixes
- _STR for std::string constants or constexpr const char*
- _t for class types
- _ind for int type indices
- _it for iterators
- _p for pointers
- _str for std::string
- _pos for sf::Vector2f positions

Prefixes
- is_ for boolean (ints)
*/

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TILE_HEIGHT 20
#define TILE_WIDTH 20
#define TILE_SCALE 2
#define MAX_WORD_LEN 255 
#define TILE_TEXTURE_COLS 15
#define A_COL_IND 0
#define A_ROW_IND 3
#define NUM_LETTERS 26
#define NUM_CLUES 1000
#define RESOURCE_STR "./resources/"
#define CW_CORRECT 0
#define CW_INCORRECT 1
#define CT_CORRECT 2
#define CT_INCORRECT 3
#define BG_CORRECT 4
#define BG_INCORRECT 5
#define CURSOR_CROSS_WORD_CORRECT 6
#define CURSOR_CROSS_WORD_INCORRECT 7

#define NUM_TILE_SPRITES 8


const std::string TITLE_STR = "CROSSWORD";
const std::string TILE_TEXTURE_STR = RESOURCE_STR "tile_set_3.png";
const std::string ICON_STR =  RESOURCE_STR "nyt_logo.png";
const std::string FONT_STR =  RESOURCE_STR "cooper_black.ttf";
const std::string WORD_MAP_STR =  RESOURCE_STR "word_map.json";

const std::string HORIZ_STR = "HORIZONTAL: \n";
const std::string VERT_STR = "VERTICAL: \n";
constexpr const char* WORD_LIST_STR = RESOURCE_STR "word_list.txt";
constexpr const char* CLUE_LIST_STR = RESOURCE_STR "clue_list.txt";
constexpr const char* NYT_CLUES_STR = RESOURCE_STR "nytcrosswords_shuffled.csv";


enum state_t{
	IDLE,
	PLAYING
};
#endif
