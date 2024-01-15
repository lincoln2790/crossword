#ifndef GAME_HPP
#define GAME_HPP
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <list>
#include <string>
#include <iterator>
 
#include "const.hpp"
#include "tile.hpp"
#include "word.hpp"
#include "cursor.hpp"
class word_t;
class game_t{	
	public:
		sf::RenderWindow window;
		sf::View view;
		sf::Texture tile_texture;
		sf::Font font;
		sf::Text horiz_clue_txt;
		sf::Text vert_clue_txt;
		std::map<char, sf::Sprite> sprite_map;
		std::map<char,std::vector<std::pair<std::string, std::string>>> word_map;
		std::list<word_t> word_list;
		state_t state;
		cursor_t cursor;

		game_t();
		sf::Sprite get_tile_sprite(char letter);
		void build_sprite_map();
		void build_word_map();
		void generate_start_word();
		void draw_word_box(word_t word, sf::Color color);
		std::vector<int> find_letter_indices(std::string str, char letter);
		void draw_cursor_word();
		void generate_clue(std::list<tile_t>::iterator *tile_it_p, int cursor_ind, word_t *word_p);
		void handle_key_input(sf::Keyboard::Key key_code);
		void generate_start_clues(word_t *start_word_p);
		void draw_text();
		void update_view();
};

#endif
