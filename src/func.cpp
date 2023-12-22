#include "../include/const.hpp"
#include "../include/func.hpp"
#include "../include/word.hpp"
#include "../include/tile.hpp"
#include "SFML/Graphics.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
sf::Sprite get_tile(char letter, sf::Texture *tile_texture){
	int x,y;
	if(letter >= 'a') letter = letter - 32;
	x = TILE_WIDTH*((3 + (letter - 'A'))%15);
	y = TILE_HEIGHT*(2 + ((3 + (letter - 'A')) > 15));
	sf::Sprite tile;
	tile.setTexture(*tile_texture);
	tile.setScale(TILE_SCALE,TILE_SCALE);
	tile.setTextureRect(sf::IntRect(x, y, TILE_WIDTH, TILE_HEIGHT));
	return tile;
}
void draw_word(word_t word, sf::RenderWindow *window){
	for(std::list<tile_t>::iterator it = word.tiles.begin(); it != word.tiles.end(); ++it){
		window->draw(it->sprite);
	}
}

std::map<char, std::vector<std::pair<std::string, int>>> read_file(){
    std::map<char, std::vector<std::pair<std::string, int>>> map;
    std::ifstream file;

    file.open ("word_list_subset.txt");
    if (!file.is_open()) return map;

    std::string word;
    int w = 0;
    while (file >> word)
    {
        for(int i = 0; i < word.length(); i++){
            std::pair<std::string, int> pair(word, w);
            map[word[i]].push_back(pair);
        }
        w++;
    }
    // Accessing and printing the map contents
    // for (const auto& pair : map) {
    //     std::cout << pair.first << ": ";
    //     for (const auto& str : pair.second) {
    //         std::cout << str.first << "|" << str.second << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << map['a'].at(0).first << std::endl;
    return map;
}
