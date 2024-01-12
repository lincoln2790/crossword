#ifndef CONST_H
#define CONST_H

#include <SFML/Graphics.hpp>

const std::string TITLE = "CROSSWORD";
const std::string TILE_SET = "images/tile_set.png";
const std::string WORD_LIST = "../word_list_subset.txt";
const std::string HORIZ_STR = "HORIZONTAL: \n";
const std::string VERT_STR = "VERTICAL: \n";

const sf::Color RED = sf::Color(255, 0, 0, 255);
const sf::Color L_RED = sf::Color(255, 128, 128, 255);
const sf::Color L_GREY = sf::Color(191, 191, 191, 255);
const sf::Color WHITE = sf::Color(255, 255, 255, 255);
const sf::Color GREY = sf::Color(128, 128, 128, 255);

#define WIDTH 800
#define HEIGHT 600
#define TILE_HEIGHT 20
#define TILE_WIDTH 20
#define TILE_SCALE 2
#define MAX_WORD_LEN 255 

#endif
