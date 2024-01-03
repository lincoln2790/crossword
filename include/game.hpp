#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../include/const.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
#include "../include/cursor.hpp"
#include "../include/func.hpp"

class game_t{	
	public:
		game_t();
		sf::RenderWindow window;
		sf::Texture tile_texture;
		std::map<char, sf::Sprite> sprite_map;
		std::map<char,std::vector<std::pair<std::string, int>>> word_map;
		std::list<word_t> word_list;
		enum state_t{
			IDLE,
			PLAYING
		} state;


		sf::Sprite get_tile_sprite(char letter);
		
		void build_sprite_map();
		void build_word_map();
		void get_start_word();
		void draw_word(word_t word);


		
		
		
		
	
};
#endif
