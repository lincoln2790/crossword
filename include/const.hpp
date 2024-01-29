#ifndef CONST_HPP
#define CONST_HPP

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

#define NUM_LETTERS 26

// Window Properties
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define MIN_WINDOW_DIM 360
#define CLUE_BOX_WIDTH WINDOW_WIDTH
#define CLUE_BOX_HEIGHT (WINDOW_HEIGHT * 0.25)
#define CLUE_BOX_X 0
#define CLUE_BOX_Y (WINDOW_HEIGHT * 0.75)


// Tile Properties
#define TILE_HEIGHT 20
#define TILE_WIDTH 20
#define TILE_SCALE 2

// Game Properties
#define MAX_WORD_LEN 255 
#define NUM_CLUES 1000

// Tile Texture
#define TILE_TEXTURE_COLS 15
#define A_COL_IND 0
#define A_ROW_IND 3

// Text Properties
//
#define BORDER_OFFSET 10
#define CLUE_FONT_SIZE 24
#define ACROSS_CLUE_TEXT_X (0 + BORDER_OFFSET)
#define ACROSS_CLUE_TEXT_Y (WINDOW_HEIGHT*0.75 + BORDER_OFFSET)
#define DOWN_CLUE_TEXT_X (WINDOW_WIDTH/2 + BORDER_OFFSET)
#define DOWN_CLUE_TEXT_Y (WINDOW_HEIGHT*0.75 + BORDER_OFFSET)


// Tile sprites
#define CW_CORRECT 0
#define CW_INCORRECT 1
#define CT_CORRECT 2
#define CT_INCORRECT 3
#define BG_CORRECT 4
#define BG_INCORRECT 5
#define CURSOR_CROSS_WORD_CORRECT 6
#define CURSOR_CROSS_WORD_INCORRECT 7

#define NUM_TILE_SPRITES 8


// Strings/file paths
#define RESOURCE_STR "./resources/"
const std::string TITLE_STR = "CROSSWORD";
const std::string TILE_TEXTURE_STR = RESOURCE_STR "tile_set_3.png";
const std::string ICON_STR =  RESOURCE_STR "nyt_logo.png";
const std::string FONT_STR =  RESOURCE_STR "cooper_black.ttf";
const std::string WORD_MAP_STR =  RESOURCE_STR "word_map.json";
//const std::string ANI_STR = RESOURCE_STR "ocean.png";
const std::string ANI_STR = RESOURCE_STR "Sprite-0005.png";
const std::string CLUE_BOX_STR = RESOURCE_STR "clue_box.png";
const std::string ACROSS_STR = "Across: \n";
const std::string DOWN_STR = "Down: \n";
constexpr const char* WORD_LIST_STR = RESOURCE_STR "word_list.txt";
constexpr const char* CLUE_LIST_STR = RESOURCE_STR "clue_list.txt";
constexpr const char* NYT_CLUES_STR = RESOURCE_STR "nytcrosswords_shuffled.csv";


enum state_t{
	IDLE,
	PLAYING
};
#endif
