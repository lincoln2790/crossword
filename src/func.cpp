#include "../include/const.hpp"
#include "../include/word.hpp"
#include "../include/tile.hpp"
#include "../include/func.hpp"
#include "SFML/Graphics.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
sf::Sprite get_tile(char letter, sf::Texture *tile_texture){
	int x,y;
	if(letter >= 'a') letter = letter - 32;
	x = TILE_WIDTH*((3 + (letter - 'A'))%15);
	y = TILE_HEIGHT*(2 + ((3 + (letter - 'A')) >= 15));
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

std::map<char, std::vector<std::pair<std::string, int>>> read_file(int *num_words){
    std::map<char, std::vector<std::pair<std::string, int>>> map;
    std::ifstream file;

    file.open ("word_list.txt");
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
	*num_words = w;
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
std::vector<int> find_letter_indices(std::string s, char c){
	std::vector<int> v;
	for(int i = 0; i < s.size(); i++){
		if(s[i] == c) v.push_back(i);
	}
	return v;
}

word_t generate_clue(tile_t* tile, std::map<char,std::vector<std::pair<std::string, int>>>* word_map, sf::Texture *tile_texture, std::list<word_t> *word_list){
	std::string s =  (*word_map)[tile->letter].at(rand() % (*word_map)[tile->letter].size()).first;
	std::vector<int> v = find_letter_indices(s, tile->letter);
	std::cout << s << std::endl;
	//for(int i = 0 ; i < v.size(); i++){
		//std::cout << v[i] << std::endl;
	//}
	int tile_index = v[rand() % v.size()];
	if(tile->is_horiz){
		return word_t(tile_texture, s, tile->pos.x,tile->pos.y - TILE_HEIGHT*TILE_SCALE*tile_index ,false , word_list, false, word_map);
	} else {
		return word_t(tile_texture, s, tile->pos.x - TILE_WIDTH*TILE_SCALE*tile_index,tile->pos.y, true, word_list, false, word_map);
	}

	
}

