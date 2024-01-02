
#include "../include/game.hpp"

game_t::game_t() :
	window(sf::VideoMode(WIDTH, HEIGHT), TITLE ,sf::Style::Titlebar | sf::Style::Close),
	state(IDLE)
	{
	window.setTitle(TITLE);
	sf::View view(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
	window.setView(view);
	
	tile_texture.loadFromFile(TILE_SET);
	tile_texture.setSmooth(true);
	
	//word_list.push_back(start_word);
	//std::map<char,std::vector<std::pair<std::string, int>>> word_map = build_word_map();
	//this->word_map = word_map;

	build_sprite_map();
	//this->sprite_map = sprite_map;
}


sf::Sprite game_t::get_tile_sprite(char letter){
	int x,y;
	if(letter == 0) {
		sf::Sprite blank_tile;
		blank_tile.setTexture(tile_texture);
		blank_tile.setScale(TILE_SCALE,TILE_SCALE);
		blank_tile.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
		return blank_tile;
	}
	if(letter >= 'a') letter = letter - 32;
	x = TILE_WIDTH*((3 + (letter - 'A'))%15);
	y = TILE_HEIGHT*(2 + ((3 + (letter - 'A')) >= 15));
	sf::Sprite tile;
	tile.setTexture(tile_texture);
	tile.setScale(TILE_SCALE,TILE_SCALE);
	tile.setTextureRect(sf::IntRect(x, y, TILE_WIDTH, TILE_HEIGHT));
	return tile;
}

void game_t::build_sprite_map(){
	for(char c = 'a'; c <= 'z'; c++){
		sprite_map.insert(std::make_pair(c, get_tile_sprite(c)));
	}

	sprite_map.insert(std::make_pair(0, get_tile_sprite(0)));

}
