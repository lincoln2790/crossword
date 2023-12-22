#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../include/const.hpp"
#include "../include/func.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
#include <map>
#include <vector>
#include <string>
#include <utility>
#include<iostream>
#include<fstream>
#include <time.h>
#include <stdlib.h>
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
	std::cout << it->first;
	word_t root_word = word_t(&tile_texture,it->second.at(rand() % it->second.size()).first,3*TILE_WIDTH, HEIGHT/2, true);
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
		window.clear(sf::Color::Black);
		switch(game_state){
			case state_t::IDLE:
				break;
			case state_t::PLAYING:
				//word_t word(&tile_texture, word_map['a'].at(rand() % word_map['a'].size()).first, 100, 100,0);
				
				draw_word(root_word, &window);
				
				break;
		}
		//tile_t tile(get_tile('V', &tile_texture), 80,200);
		//window.draw(tile.sprite);
		window.display();
	}
	return 0;
}
