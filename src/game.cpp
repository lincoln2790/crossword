
#include "../include/game.hpp"

game_t::game_t() :
	window(sf::VideoMode(WIDTH, HEIGHT), TITLE ,sf::Style::Titlebar | sf::Style::Close),
	state(IDLE)
	{
	window.setTitle(TITLE);
	sf::View view(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
	window.setView(view);
	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	tile_texture.loadFromFile(TILE_SET);
	tile_texture.setSmooth(true);
	
	//word_list.push_back(start_word);
	//std::map<char,std::vector<std::pair<std::string, int>>> word_map = build_word_map();
	//this->word_map = word_map;

	build_sprite_map();
	build_word_map();
	get_start_word();
	cursor.set_pos(&(word_list.front()));
	
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


void game_t::build_word_map(){
	std::ifstream file;
	file.open ("word_list.txt");
	std::string word;

	int w = 0;
	for(char c = 'a'; c <= 'z' ; c++){
		word_map[c] = {} ;
	}
	while (file >> word){
		for(int i = 0; i < word.length(); i++){
			std::pair<std::string, int> pair(word, w);
			//if(std::find(word_map[word[i]].begin(), word_map[word[i]].end(), pair) == word_map[word[i]].end()){
			if(word_map[word[i]].empty() || word_map[word[i]].back() != pair){
				word_map[word[i]].push_back(pair);
			}
				//std::cout << pair.first << std::endl;
		}
		w++;
	}
	// Accessing and printing the map contents
	 //for (const auto& pair : word_map) {
		 //std::cout << pair.first << ": ";
		 //if(!pair.second.empty()){
			 //for (const auto& str : pair.second) {
				 //std::cout << str.first << "|" << str.second << " ";
			 //}
		 //}
		 //std::cout << std::endl;
		 //std::cout << std::endl;
		 //std::cout << std::endl;
	 //}
}

void game_t::get_start_word(){
	char rand_char = (rand() % 26) + 'a';
	int rand_word = rand() % (word_map[rand_char].size());
	std::string start_str = word_map[rand_char][rand_word].first;
	word_t start_word(start_str,3*TILE_WIDTH, HEIGHT/2,true, true, this);
	

	//auto it = word_map.begin();
	//std::advance(it, rand() %(word_map.size()-1));
	//std::list<word_t> word_list;
	//std::string start_word_str = it->second.at(rand() % it->second.size()).first;
	////std::cout << start_word_str << std::endl << std::endl;
	//word_t start_word(&tile_texture,start_word_str,3*TILE_WIDTH, HEIGHT/2,true, &word_list, true, &word_map);
}

void game_t::draw_word(word_t word){
	for(auto it = word.tiles.begin(); it != word.tiles.end(); ++it){
		//std::cout << &it->sprite << std::endl;
		if(word.is_correct) window.draw(it->sprite);
		else window.draw(it->blank_tile);
		//window->draw(it->blank_tile);
	}
}

std::vector<int> game_t::find_letter_indices(std::string s, char c){
	std::vector<int> v;
	for(int i = 0; i < s.size(); i++){
		if(s[i] == c) v.push_back(i);
	}
	return v;
}

void game_t::generate_clue(std::list<tile_t>::iterator *tile_it, int cursor_index){
	
	int rand_ind = rand() % word_map[(*tile_it)->letter].size();
	std::string s = word_map[(*tile_it)->letter].at(rand_ind).first;
	//std::cout << s;
	//std::cout << " | ";
	//std::cout << tile->letter << std::endl;
	std::vector<int> v = find_letter_indices(s, (*tile_it)->letter);
	int tile_index = v[rand() % v.size()];
	if((*tile_it)->is_horiz){
		 word_t w(s, (*tile_it)->pos.x,(*tile_it)->pos.y - TILE_HEIGHT*TILE_SCALE*tile_index ,false, false, this);
		 auto it = word_list.back().tiles.begin();
		 std::advance(it, tile_index);
		 it->is_correct = true;
		 (*tile_it)->crossing_word = &(word_list.back());

		 auto it_cross = (*tile_it)->crossing_word->tiles.begin();
		 std::advance(it_cross, tile_index);
		 it_cross->is_correct = true;
		 it_cross->crossing_word = cursor.word;

		 std::cout << (*tile_it)->crossing_word->word << std::endl;
		 //return w;
	} else {
		word_t w(s, (*tile_it)->pos.x - TILE_WIDTH*TILE_SCALE*tile_index,(*tile_it)->pos.y, true, false, this);
		 auto it = word_list.back().tiles.begin();
		 std::advance(it, tile_index);
		 it->is_correct = true;
		 (*tile_it)->crossing_word = &(word_list.back());
		 auto it_cross = (*tile_it)->crossing_word->tiles.begin();
		 std::advance(it_cross, tile_index);
		 it_cross->is_correct = true;
		 it_cross->crossing_word = cursor.word;
		 //return w;

		 std::cout << (*tile_it)->crossing_word->word << std::endl;
	}

	
}

void game_t::draw_cursor_word(){
	for(auto it = cursor.word->tiles.begin(); it != cursor.word->tiles.end();++it){
		sf::Sprite cursor_tile;

		if(cursor.word->is_correct){
			if(it == cursor.tile_it){
				cursor_tile = sprite_map[it->letter];
				//window.draw(cursor_tile);
			}else{
				//window.draw(it->sprite);
			}
		}else {
			if(it->is_correct){
				cursor_tile = sprite_map[it->letter];
			}else {
				cursor_tile = sprite_map[it->cursor_letter];
			}
			//window.draw(cursor_tile);
		}

		cursor_tile.setPosition(it->pos);

		if(it != cursor.tile_it && !it->is_correct) cursor_tile.setColor(sf::Color(255, 255, 255, 128));
		else if(it == cursor.tile_it)   cursor_tile.setColor(sf::Color(255, 0, 0, 128));

		//if(!it->is_correct){
			//window.draw(cursor_tile);
		//if((cursor.word->is_correct && it == cursor.tile_it) ||(!cursor.word->is_correct)){
			//window.draw(cursor_tile);
		//}else if(cursor.word->is_correct){
			//window.draw(it->sprite);
		//}

		if(cursor.word->is_correct){
			if(it == cursor.tile_it){
				//cursor_tile = sprite_map[it->letter];
				window.draw(cursor_tile);
			}else{
				window.draw(it->sprite);
			}
		}else {
			if(it->is_correct){
				//cursor_tile = sprite_map[it->letter];
			}else {
				//cursor_tile = sprite_map[it->cursor_letter];
			}
			window.draw(cursor_tile);
		}
	}
	//cursor.tile_it->sprite.setColor(sf::Color(255,0,0,128));
	//window.draw(cursor.tile_it->sprite);
}
