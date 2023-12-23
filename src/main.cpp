#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
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
#include "../include/func.hpp"
int main() {


	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE ,sf::Style::Titlebar | sf::Style::Close);
	window.setTitle(TITLE);
	sf::View view(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
	window.setView(view);
	sf::Texture tile_texture;
	if(!tile_texture.loadFromFile(TILE_SET)){
		return 1;
	}
	tile_texture.setSmooth(true);

	sf::Sprite sprite;
	sprite.setTexture(tile_texture);
	int num_words;
	
	std::map<char,std::vector<std::pair<std::string, int>>> word_map = read_file(&num_words);
	
	auto it = word_map.begin();
    std::advance(it, rand() %(word_map.size()-1));
	std::list<word_t> word_list;
	std::string start_word = it->second.at(rand() % it->second.size()).first;
	std::cout << start_word << std::endl << std::endl;
	word_t(&tile_texture,start_word,3*TILE_WIDTH, HEIGHT/2,true, &word_list, true, &word_map);
	//word_t second_word = generate_clue(&(*(root_word.tiles.begin())), &word_map, &tile_texture);
	//(*(root_word.tiles.begin())).crossing_word = &second_word;
	enum class state_t{
		IDLE,
		PLAYING
	};
	state_t game_state = state_t::IDLE;
	srand(time(NULL));
	
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch(game_state){
						case state_t::IDLE:
							if(event.type == sf::Event::KeyPressed){
								if(event.key.code == sf::Keyboard::Key::Space){
									game_state = state_t::PLAYING;
								}
							}
							break;
						case state_t::PLAYING:
							
							//if(event.type == sf::Event::KeyPressed){
								//if(event.key.code == sf::Keyboard::Key::Space){
									//view.move(sf::Vector2f(10.f, 10.f));
									//window.setView(view);

								//}

							//}
							break;
					}
					break;
				default:
					break;
					
			}
		}
		window.clear(sf::Color::White);
		switch(game_state){
			case state_t::IDLE:
				break;
			case state_t::PLAYING:
				//word_t word(&tile_texture, word_map['a'].at(rand() % word_map['a'].size()).first, 100, 100,0);
				for(auto it = word_list.begin(); it != word_list.end(); ++it){
					draw_word(*it, &window);
				}
				draw_word(*(word_list.begin()), &window);
				//draw_word(*(word_list.begin()++), &window);
				//draw_word(*(word_list.begin()++), &window);
				//draw_word(*(root_word.tiles.begin())->crossing_word, &window);
				//draw_word(second_word, &window);
				break;
		}
		//tile_t tile(get_tile('V', &tile_texture), 80,200);
		//window.draw(tile.sprite);
		window.display();
	}
	return 0;
}
