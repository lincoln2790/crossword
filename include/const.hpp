#ifndef CONST_H
#define CONST_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
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
#define A_COL_IND 3
#define A_ROW_IND 2
#define NUM_LETTERS 26


const std::string TITLE_STR = "CROSSWORD";
const std::string TILE_TEXTURE_STR = "images/tile_set.png";
const std::string ICON_STR = "images/nyt_logo.png";
const std::string HORIZ_STR = "HORIZONTAL: \n";
const std::string VERT_STR = "VERTICAL: \n";
constexpr const char* WORD_LIST_STR = "word_list.txt";
constexpr const char* CLUE_LIST_STR = "clue_list.txt";

const sf::Color RED = sf::Color(255, 0, 0, 255);
const sf::Color L_RED = sf::Color(255, 128, 128, 255);
const sf::Color L_GREY = sf::Color(191, 191, 191, 255);
const sf::Color WHITE = sf::Color(255, 255, 255, 255);
const sf::Color GREY = sf::Color(128, 128, 128, 255);

enum state_t{
	IDLE,
	PLAYING
};
#endif
