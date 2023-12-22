#include <SFML/Graphics.hpp>
#include "../include/const.hpp"
#include "../include/func.hpp"
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
		sf::Sprite tile = get_tile('W',&tile_texture);
		window.draw(tile);
		window.display();
	}
	return 0;
}
