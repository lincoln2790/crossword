
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include<iostream>
#include<fstream>
#include <time.h>
#include <stdlib.h>

#include "../include/const.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
#include "../include/cursor.hpp"
#include "../include/game.hpp"
int main() {
	game_t game;
	while(game.window.isOpen()){
		sf::Event event;
		while(game.window.pollEvent(event)){
			// events that can occur during all game states
			switch(event.type){
				case sf::Event::Closed:
					game.window.close();
					break;
			}
			
			switch(game.state){
				case game.state_t::IDLE:
					switch(event.type){
						case sf::Event::KeyPressed:
							switch(event.key.code){
								case sf::Keyboard::Key::Space:
									game.state = game.state_t::PLAYING;
									continue;
									//break;
							}
					}
					break;
				case game.state_t::PLAYING:
					switch(event.type){
						case sf::Event::TextEntered:
								//cursor.tile->cursor_letter = event.text.unicode;
							if((!game.cursor.word->is_correct) && (event.text.unicode >= 'a' && event.text.unicode <= 'z')){
								game.cursor.tile_it->cursor_letter = event.text.unicode;
								if(game.cursor.check()){
									std::cout << "CORRECT\n" <<std::flush;
									int cursor_index = 0;
									for(auto it = game.cursor.word->tiles.begin(); it != game.cursor.word->tiles.end(); ++it){
										if(!it->is_correct){
											game.generate_clue(&it, cursor_index, game.cursor.word);
											std::cout << it->cross_word_ind <<std::endl;

											it->is_correct = true;
										}
										//std::cout << it.crossing_word;
										cursor_index++;

									}
									game.cursor.word->is_correct = true;
									auto it = game.cursor.word->tiles.begin();
									std::advance(it, game.cursor.tile_it->cross_word_ind);
									game.cursor.tile_it = it;
									continue;
								}
								std::advance(game.cursor.tile_it, 1);
																	
								while(!game.cursor.word->is_correct && (game.cursor.tile_it == (game.cursor.word->tiles.end()) || game.cursor.tile_it->is_correct)){
									if(game.cursor.tile_it == game.cursor.word->tiles.end()){
										game.cursor.tile_it = game.cursor.word->tiles.begin();
									}
									if(game.cursor.tile_it->is_correct){
										std::advance(game.cursor.tile_it, 1);
									}
								}
							}
							break;
						case sf::Event::KeyPressed:
							game.move(event.key.code);
						break;
					}
			}
		}
		game.window.clear(sf::Color::Black);
		switch(game.state){
			case game.state_t::IDLE:
				break;
			case game.state_t::PLAYING:
			for(auto word : game.word_list){
				if(!word.is_correct) game.draw_word_box(word, GREY);

			}
			for(auto word : game.word_list){
				if(word.is_correct) game.draw_word_box(word, WHITE);

			}
			game.draw_cursor_word();
		}
		game.window.display();
		
	}
	return 0;
}
