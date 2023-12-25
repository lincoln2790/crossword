#include "SFML/Graphics.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "../include/const.hpp"
#include "../include/word.hpp"
#include "../include/tile.hpp"
#include "../include/cursor.hpp"
#include "../include/func.hpp"
sf::Sprite get_tile(char letter, sf::Texture *tile_texture){
	int x,y;
	if(letter == 0) {
		sf::Sprite blank_tile;
		blank_tile.setTexture(*tile_texture);
		blank_tile.setScale(TILE_SCALE,TILE_SCALE);
		blank_tile.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
		return blank_tile;
	}
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
		if(word.is_correct) window->draw(it->sprite);
		else window->draw(it->blank_tile);
		//window->draw(it->blank_tile);
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
	//std::cout << s << std::endl;
	//for(int i = 0 ; i < v.size(); i++){
		//std::cout << v[i] << std::endl;
	//}
	int tile_index = v[rand() % v.size()];
	if(tile->is_horiz){
		 word_t w(tile_texture, s, tile->pos.x,tile->pos.y - TILE_HEIGHT*TILE_SCALE*tile_index ,false , word_list, false, word_map);
		 tile->crossing_word = &word_list->back();
		 //std::cout << &w << std::endl;
		 return w;
	} else {
		word_t w(tile_texture, s, tile->pos.x - TILE_WIDTH*TILE_SCALE*tile_index,tile->pos.y, true, word_list, false, word_map);
		 tile->crossing_word = &word_list->back();
		 //std::cout <<&w  << std::endl;
		 return w;
	}

	
}
void crossword_dfs(word_t *root_word, std::set<word_t*> *visited_words, sf::RenderWindow *window, int is_correct){
	visited_words->insert(root_word);
	if(root_word->is_correct == is_correct) draw_word(*root_word, window);
	for(auto it = root_word->tiles.begin(); it != root_word->tiles.end(); ++it){
		for(auto it : *visited_words){
		}
		if(it->crossing_word != NULL ) {
		//if((it->crossing_word != NULL) and (visited_words->find(it->crossing_word) == visited_words->end())){

			//draw_word(*(it->crossing_word), window);
			crossword_dfs(it->crossing_word, visited_words, window, is_correct);
		}
	}
}

		

void draw_cursor_word(cursor_t *cursor, sf::RenderWindow *window, sf::Texture *tile_texture){
	for(auto it = cursor->word->tiles.begin(); it != cursor->word->tiles.end();++it){
		sf::Sprite cursor_tile = get_tile(it->cursor_letter, tile_texture);
		cursor_tile.setPosition(it->pos);
		if(it != cursor->tile_it) cursor_tile.setColor(sf::Color(255, 255, 255, 128));
		window->draw(cursor_tile, tile_texture);
	}
}
