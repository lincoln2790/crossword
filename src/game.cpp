
#include "../include/game.hpp"

game_t::game_t() :
	window(sf::VideoMode(WIDTH, HEIGHT), TITLE ,sf::Style::Titlebar | sf::Style::Close),
	state(IDLE)
	{
	window.setTitle(TITLE);
	sf::View view(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
	window.setView(view);
	window.setVerticalSyncEnabled(true);
	tile_texture.loadFromFile(TILE_SET);
	tile_texture.setSmooth(true);
	
	build_sprite_map();
	build_word_map();
	get_start_word();
	cursor.set_pos(&(word_list.back()));
	generate_start_clues(&word_list.front());
	//sf::Image image;
	//image.loadFromFile("../images/nyt_logo.png");
	//window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
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
			if(word_map[word[i]].empty() || word_map[word[i]].back() != pair){
				word_map[word[i]].push_back(pair);
			}
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
}

void game_t::draw_word(word_t word){
	for(auto it = word.tiles.begin(); it != word.tiles.end(); ++it){
		//std::cout << &it->sprite << std::endl;
		sf::Sprite tile = it->blank_tile;
		if(it->is_correct) tile.setColor(sf::Color(255, 255, 255, 255));
		else tile.setColor(sf::Color(128, 128, 128, 255));
		window.draw(tile);
	}
}

std::vector<int> game_t::find_letter_indices(std::string s, char c){
	std::vector<int> v;
	for(int i = 0; i < s.size(); i++){
		if(s[i] == c) v.push_back(i);
	}
	return v;
}

void game_t::generate_clue(std::list<tile_t>::iterator *tile_it, int cursor_index, word_t *curr_word){
	int rand_ind = rand() % word_map[(*tile_it)->letter].size();
	std::string s = word_map[(*tile_it)->letter].at(rand_ind).first;
	std::vector<int> v = find_letter_indices(s, (*tile_it)->letter);
	int tile_index = v[rand() % v.size()];
	
	if((*tile_it)->is_horiz){
		 word_t w(s, (*tile_it)->pos.x,(*tile_it)->pos.y - TILE_HEIGHT*TILE_SCALE*tile_index ,false, false, this);
	} else {
		word_t w(s, (*tile_it)->pos.x - TILE_WIDTH*TILE_SCALE*tile_index,(*tile_it)->pos.y, true, false, this);
	}


	 (*tile_it)->crossing_word =&(word_list.back()); // this part works

	 //std::cout <<  (*tile_it)->crossing_word->word;
	 (*tile_it)->cross_word_ind = tile_index;
	 auto it = (*tile_it)->crossing_word->tiles.begin();
	 std::advance(it, tile_index);
	 it->is_correct = true;
	 it->crossing_word = curr_word;
	 it->cross_word_ind = cursor_index;
	 //it->cross_word_ind = tile_index;
	 std::cout <<(*tile_it)->cross_word_ind;
	 //std::cout <<  it->crossing_word->word;
	
	 //auto itt = (*tile_it)->crossing_word->tiles.begin();
	 //std::advance(itt, tile_index);

	 //std::cout <<  itt->crossing_word->word;
	 //it->is_correct = true;
	 //it->crossing_word = curr_word;
	 //std::advance(*it, -1*tile_index); // is this right?
	 //std::cout << (*it)->crossing_word->word <<std::endl;

	 //pointing the current word to the generated word;

	//connecting the generated word to the current cursor word
	 //auto it_cross = (*tile_it)->crossing_word->tiles.begin();
	 //std::advance(it_cross, tile_index);
	 //it_cross->is_correct = true;
	 //it_cross->crossing_word = curr_word;
	//std::cout << it_cross->crossing_word;

	 std::cout << (*tile_it)->crossing_word->word << std::endl;
	
}


void game_t::draw_cursor_word(){
	for(auto it = cursor.word->tiles.begin(); it != cursor.word->tiles.end();++it){
		sf::Sprite cursor_tile;

		if(cursor.word->is_correct){
			if(it == cursor.tile_it){
				cursor_tile = sprite_map[it->letter];
			}
		}else {
			if(it->is_correct){
				cursor_tile = sprite_map[it->letter];
			}else {
				cursor_tile = sprite_map[it->cursor_letter];
			}
		}

		cursor_tile.setPosition(it->pos);

		if(it != cursor.tile_it && !it->is_correct) cursor_tile.setColor(sf::Color(191, 191, 191, 255));
		else if(it == cursor.tile_it)   cursor_tile.setColor(sf::Color(255, 0, 0, 255));

		if(cursor.word->is_correct){
			if(it == cursor.tile_it){
				window.draw(cursor_tile);
			}else{
				window.draw(it->sprite);
			}
		}else {
			window.draw(cursor_tile);
		}
	}
}
void game_t::move(sf::Keyboard::Key key_code){
	if(key_code == sf::Keyboard::Key::Up ||key_code == sf::Keyboard::Key::Down ||key_code == sf::Keyboard::Key::Left ||key_code == sf::Keyboard::Key::Right ){
		std::list<tile_t>::iterator boundary_it;
		if(key_code == sf::Keyboard::Key::Up || key_code == sf::Keyboard::Key::Left){
			boundary_it = cursor.word->tiles.begin();
		} else if (key_code == sf::Keyboard::Key::Down || key_code == sf::Keyboard::Key::Right){
			boundary_it = --cursor.word->tiles.end();
		}
		int input_along_word = (cursor.word->is_horiz &&  (key_code == sf::Keyboard::Key::Left || key_code == sf::Keyboard::Key::Right) ) || (!cursor.word->is_horiz &&  (key_code == sf::Keyboard::Key::Up || key_code == sf::Keyboard::Key::Down));
		int is_forward =  (key_code == sf::Keyboard::Key::Down || key_code == sf::Keyboard::Key::Right) ? 1 : (key_code == sf::Keyboard::Key::Up || key_code == sf::Keyboard::Key::Left) ? -1 : 0;

		if(input_along_word ){
			if(cursor.tile_it != boundary_it)
			std::advance(cursor.tile_it,is_forward);
		} else if(cursor.tile_it->crossing_word != NULL){
			//std::cout <<cursor.tile_it->crossing_word <<std::endl; // crossing word is not initialised?
			//
			cursor.word = cursor.tile_it->crossing_word;
			auto it = (cursor.word->tiles.begin());
			std::advance(it, cursor.tile_it->cross_word_ind);

			std::cout << cursor.tile_it->cross_word_ind << std::endl;
			cursor.tile_it = it;
			//std::advance(cursor.tile_it, cursor.tile_it->cross_word_ind);
		}

	}
}

void game_t::generate_start_clues(word_t *start_word){
	int i = 0;
	for(auto it = start_word->tiles.begin(); it != start_word->tiles.end(); ++it){
		generate_clue(&it, i++, start_word);
	}
}

