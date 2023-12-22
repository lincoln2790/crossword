#include <SFML/Graphics.hpp>
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
int main() {


	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE ,sf::Style::Titlebar | sf::Style::Close);
	window.setTitle(TITLE);
	
	sf::Texture tile_texture;
	if(!tile_texture.loadFromFile(TILE_SET)){
		return 1;
	}
	tile_texture.setSmooth(true);

	sf::Sprite sprite;
	sprite.setTexture(tile_texture);
		
	std::map<char,std::vector<std::pair<std::string, int>>> word_map = read_file();
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:

					break;
				default:
					break;
	
			}
		}
		window.clear(sf::Color::Black);
		word_t word(&tile_texture, word_map['a'].at(0).first, 100, 100,'a');
		draw_word(word, &window);
		
		//tile_t tile(get_tile('V', &tile_texture), 80,200);
		//window.draw(tile.sprite);
		window.display();
	}
	return 0;
}
