#include "../include/game.hpp"

game_t::game_t() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE_STR ,sf::Style::Titlebar | sf::Style::Close),
	state(IDLE)
	{
	window.setTitle(TITLE_STR);
	sf::View view(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT));
	window.setView(view);
	window.setVerticalSyncEnabled(true);
	tile_texture.loadFromFile(TILE_TEXTURE_STR);
	tile_texture.setSmooth(true);
	font.loadFromFile("arial.ttf");
	
	horiz_clue_txt.setFont(font);
	horiz_clue_txt.setCharacterSize(24);
	horiz_clue_txt.setFillColor(WHITE);
	horiz_clue_txt.setString(" ");

	vert_clue_txt.setFont(font);
	vert_clue_txt.setCharacterSize(24);
	vert_clue_txt.setFillColor(WHITE);
	vert_clue_txt.setString(" ");
	vert_clue_txt.setPosition(200,0);
	
	build_sprite_map();
	build_word_map();
	generate_start_word();
	cursor.set_pos(&(word_list.back()));
	generate_start_clues(&word_list.front());
	if(cursor.word_p->is_horiz){
		horiz_clue_txt.setString(HORIZ_STR + cursor.word_p->clue_str);
		vert_clue_txt.setString(VERT_STR + (cursor.tile_it->cross_word_p != NULL ? cursor.tile_it->cross_word_p->clue_str : " - " ));
	}else{
		horiz_clue_txt.setString(HORIZ_STR +  (cursor.tile_it->cross_word_p != NULL ? cursor.tile_it->cross_word_p->clue_str : " - " ));
		vert_clue_txt.setString(VERT_STR + cursor.word_p->clue_str);
	}
	sf::Image icon;
	icon.loadFromFile(ICON_STR);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

}


sf::Sprite game_t::get_tile_sprite(char letter){
	int x,y;
	if(letter == 0) {
		sf::Sprite blank_sprite;
		blank_sprite.setTexture(tile_texture);
		blank_sprite.setScale(TILE_SCALE,TILE_SCALE);
		blank_sprite.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
		return blank_sprite;
	}
	if(letter >= 'a') letter = letter - ('a' - 'A');
	x = TILE_WIDTH*((A_COL_IND + (letter - 'A'))% TILE_TEXTURE_COLS);
	y = TILE_HEIGHT*(A_ROW_IND + ((A_COL_IND + (letter - 'A')) >= TILE_TEXTURE_COLS));
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
	std::ifstream clue_file;
	//file.open ("word_list.txt");
	file.open (WORD_LIST_STR);
	clue_file.open(CLUE_LIST_STR);
	std::string word;
	std::string clue_str;
	int w = 0;
	for(char c = 'a'; c <= 'z' ; c++){
		word_map[c] = {} ;
	}
	while (file >> word){
		std::getline(clue_file, clue_str);
		//std::cout << clue << std::endl;
		for(int i = 0; i < word.length(); i++){
			std::pair<std::string, std::string> pair(word,clue_str);
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

void game_t::generate_start_word(){
	char rand_char = (rand() % NUM_LETTERS) + 'a';
	int rand_word = rand() % (word_map[rand_char].size());
	std::string start_str = word_map[rand_char][rand_word].first;
	std::string start_clue = word_map[rand_char][rand_word].second;
	
	word_t start_word(start_str, start_clue,3*TILE_WIDTH, WINDOW_HEIGHT/2,true, true, this);

}

void game_t::draw_word_box(word_t word, sf::Color color){
	for(auto it = word.tile_list.begin(); it != word.tile_list.end(); ++it){
		//std::cout << &it->sprite << std::endl;
		sf::Sprite tile = it->blank_sprite;
		tile.setColor(color);
		//if(it->is_correct) tile.setColor(sf::Color(WHITE);
		//else tile.setColor(GREY);
		//
		window.draw(tile);
	}
}

std::vector<int> game_t::find_letter_indices(std::string str, char letter){
	std::vector<int> ind_vec;
	for(int i = 0; i < str.size(); i++){
		if(str[i] == letter) ind_vec.push_back(i);
	}
	return ind_vec;
}

void game_t::generate_clue(std::list<tile_t>::iterator *tile_it_p, int cursor_index, word_t *word_p){
	int rand_ind = rand() % word_map[(*tile_it_p)->letter].size();
	std::string s = word_map[(*tile_it_p)->letter].at(rand_ind).first;
	std::string clue = word_map[(*tile_it_p)->letter].at(rand_ind).second;
 
	std::vector<int> v = find_letter_indices(s, (*tile_it_p)->letter);
	int tile_index = v[rand() % v.size()];
	
	if((*tile_it_p)->is_horiz){
		 word_t w(s, clue, (*tile_it_p)->pos.x,(*tile_it_p)->pos.y - TILE_HEIGHT*TILE_SCALE*tile_index ,false, false, this);
	} else {
		word_t w(s, clue, (*tile_it_p)->pos.x - TILE_WIDTH*TILE_SCALE*tile_index,(*tile_it_p)->pos.y, true, false, this);
	}


	 (*tile_it_p)->cross_word_p =&(word_list.back()); // this part works

	 (*tile_it_p)->cross_word_ind = tile_index;
	 auto it = (*tile_it_p)->cross_word_p->tile_list.begin();
	 std::advance(it, tile_index);
	 it->is_correct = true;
	 it->cross_word_p = word_p;
	 it->cross_word_ind = cursor_index;
	 //std::cout << (*tile_it_p)->cross_word_p->word << std::endl;
	 //std::cout << (*tile_it_p)->cross_word_p->word << std::endl;
	 
}


void game_t::draw_cursor_word(){
	for(auto it = cursor.word_p->tile_list.begin(); it != cursor.word_p->tile_list.end();++it){
		if(it->cross_word_p != NULL){
			if(it->cross_word_p->is_correct)   
			draw_word_box(*it->cross_word_p, WHITE);
			else
			draw_word_box(*it->cross_word_p, L_RED);
		}
		
		sf::Sprite cursor_tile;

		if(cursor.word_p->is_correct){
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

		if(it != cursor.tile_it && !it->is_correct) cursor_tile.setColor(L_GREY);
		else if(it == cursor.tile_it)   cursor_tile.setColor(RED);

		if(cursor.word_p->is_correct){
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
void game_t::handle_key_input(sf::Keyboard::Key key_code){
	if(key_code == sf::Keyboard::Key::Up ||key_code == sf::Keyboard::Key::Down ||key_code == sf::Keyboard::Key::Left ||key_code == sf::Keyboard::Key::Right ){
		std::list<tile_t>::iterator boundary_it;
		if(key_code == sf::Keyboard::Key::Up || key_code == sf::Keyboard::Key::Left){
			boundary_it = cursor.word_p->tile_list.begin();
		} else if (key_code == sf::Keyboard::Key::Down || key_code == sf::Keyboard::Key::Right){
			boundary_it = --cursor.word_p->tile_list.end();
		}
		int input_along_word = (cursor.word_p->is_horiz &&  (key_code == sf::Keyboard::Key::Left || key_code == sf::Keyboard::Key::Right) ) || (!cursor.word_p->is_horiz &&  (key_code == sf::Keyboard::Key::Up || key_code == sf::Keyboard::Key::Down));
		int is_forward =  (key_code == sf::Keyboard::Key::Down || key_code == sf::Keyboard::Key::Right) ? 1 : (key_code == sf::Keyboard::Key::Up || key_code == sf::Keyboard::Key::Left) ? -1 : 0;

		if(input_along_word ){
			if(cursor.tile_it != boundary_it)
			std::advance(cursor.tile_it,is_forward);
		} else if(cursor.tile_it->cross_word_p != NULL){
			//std::cout <<cursor.tile_it->cross_word_p <<std::endl; // crossing word is not initialised?
			//
			cursor.word_p = cursor.tile_it->cross_word_p;
			auto it = (cursor.word_p->tile_list.begin());
			std::advance(it, cursor.tile_it->cross_word_ind);

			//std::cout << cursor.tile_it->cross_word_ind << std::endl;
			cursor.tile_it = it;
		}

	}
	else if (key_code == sf::Keyboard::Key::Tab){
		if(cursor.tile_it->cross_word_p != NULL){
			cursor.word_p = cursor.tile_it->cross_word_p;
			auto it = (cursor.word_p->tile_list.begin());
			std::advance(it, cursor.tile_it->cross_word_ind);
			cursor.tile_it = it;
		}
	}
	else if (key_code == sf::Keyboard::Key::Num0){
		cursor.tile_it = cursor.word_p->tile_list.begin();
	}
	else if(key_code == sf::Keyboard::Key::Backspace){
		cursor.tile_it->cursor_letter = 0;

		if(cursor.tile_it != cursor.word_p->tile_list.begin()){
			std::advance(cursor.tile_it, -1);
		}
	}
	if(cursor.word_p->is_horiz){
		horiz_clue_txt.setString(HORIZ_STR + cursor.word_p->clue_str);
		vert_clue_txt.setString(VERT_STR + (cursor.tile_it->cross_word_p != NULL ? cursor.tile_it->cross_word_p->clue_str : " - " ));
	}else{
		horiz_clue_txt.setString(HORIZ_STR +  (cursor.tile_it->cross_word_p != NULL ? cursor.tile_it->cross_word_p->clue_str : " - " ));
		vert_clue_txt.setString(VERT_STR + cursor.word_p->clue_str);
	}
}

void game_t::generate_start_clues(word_t *start_word_p){
	int i = 0;
	for(auto it = start_word_p->tile_list.begin(); it != start_word_p->tile_list.end(); ++it){
		generate_clue(&it, i++, start_word_p);
	}
}

void game_t::draw_text(){
	window.draw(horiz_clue_txt);
	window.draw(vert_clue_txt);
}
