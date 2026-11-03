#include "../include/game.hpp"
#include "../include/word_map.hpp"
game_t::game_t() :
	window(sf::VideoMode(DEFAULT_WINDOW_DIM, DEFAULT_WINDOW_DIM), TITLE_STR, sf::Style::Titlebar|sf::Style::Resize | sf::Style::Close),
	window_scale(1.0),
	view(sf::FloatRect(0.f, 0.f, DEFAULT_WINDOW_DIM, DEFAULT_WINDOW_DIM)),
	state(IDLE),
	points(0)
	{
	window.setTitle(TITLE_STR);
	window.setView(view);
	window.setVerticalSyncEnabled(true);
	tile_texture.loadFromFile(TILE_TEXTURE_STR);
	tile_texture.setSmooth(true);
	font.loadFromFile(FONT_STR);

	sf::Image icon;
	icon.loadFromFile(ICON_STR);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	across_clue_txt.setFont(font);
	across_clue_txt.setCharacterSize(CLUE_FONT_SIZE);
	across_clue_txt.setFillColor(WHITE);
	across_clue_txt.setPosition(ACROSS_CLUE_TEXT_X,ACROSS_CLUE_TEXT_Y);

	down_clue_txt.setFont(font);
	down_clue_txt.setCharacterSize(CLUE_FONT_SIZE);
	down_clue_txt.setFillColor(WHITE);
	down_clue_txt.setPosition(ACROSS_CLUE_TEXT_X,ACROSS_CLUE_TEXT_Y);

	points_txt.setFont(font);
	points_txt.setCharacterSize(CLUE_FONT_SIZE);
	points_txt.setFillColor(WHITE);
	points_txt.setPosition(ACROSS_CLUE_TEXT_X,ACROSS_CLUE_TEXT_Y);
	

	build_sprite_map();
	build_word_map();
	start();


}

void game_t::update_clue_txt(){
	if(cursor.word_p->is_across){
		across_clue_txt.setString(ACROSS_STR + cursor.word_p->clue_str + " (" + std::to_string(cursor.word_p->word_str.length()) + ")");
		down_clue_txt.setString(DOWN_STR + (cursor.tile_it->cross_word_p != NULL ? cursor.tile_it->cross_word_p->clue_str + " (" + std::to_string(cursor.word_p->word_str.length()) + ")": " - " ));
	}else{
		across_clue_txt.setString(ACROSS_STR +  (cursor.tile_it->cross_word_p != NULL ? cursor.tile_it->cross_word_p->clue_str + " (" + std::to_string(cursor.word_p->word_str.length()) + ")": " - " ));
		down_clue_txt.setString(DOWN_STR + cursor.word_p->clue_str + " (" + std::to_string(cursor.word_p->word_str.length()) + ")");
	}
}

void game_t::update_points_txt(){
	points_txt.setString(std::to_string(points));
}

void game_t::start(){
	across_clue_txt.setString(" ");
	down_clue_txt.setString(" ");
	cursor = cursor_t();
	word_list.clear();
	generate_start_word();
	cursor.set_pos(&(word_list.back()));
	generate_start_clues(&word_list.front());
	update_clue_txt();
	update_points_txt();

}

sf::Sprite game_t::get_tile_sprite(char letter){
	int x,y;
	if(letter < 'a') { //special tile sprites ie. not letters
		sf::Sprite blank_sprite;
		blank_sprite.setTexture(tile_texture);
		blank_sprite.setScale(TILE_SCALE,TILE_SCALE);
		blank_sprite.setTextureRect(sf::IntRect(TILE_WIDTH*letter, 0, TILE_WIDTH, TILE_HEIGHT));
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
	for(int i = 0; i < NUM_TILE_SPRITES; i++){
		sprite_map.insert(std::make_pair(i, get_tile_sprite(i)));
	}
}


void game_t::build_word_map(){
	word_map_t loadedObject;
	std::ifstream is(WORD_MAP_STR);
	cereal::JSONInputArchive archive(is);
	archive(loadedObject);
	
	//for (auto pair = loadedObject.word_map.begin(); pair != loadedObject.word_map.end(); ++pair){
		//std::cout << pair->first <<std::endl;
		 //if(!pair->second.empty()){
			 //for (const auto& str : pair->second) {
				 //std::cout << str.first << "|" << str.second << "\n ";
			 //}
		 //}
		 //std::cout << std::endl;
		 //std::cout << std::endl;
		 //std::cout << std::endl;
	//}
	word_map = loadedObject.word_map;
}

void game_t::generate_start_word(){
	char rand_char = (rand() % NUM_LETTERS) + 'a';
	int rand_word = rand() % (word_map[rand_char].size());
	std::string start_str = word_map[rand_char][rand_word].first;
	std::string start_clue = word_map[rand_char][rand_word].second;
	parse_clue_text(&start_clue);
	
	word_t start_word(start_str, start_clue,3*TILE_WIDTH, DEFAULT_WINDOW_DIM/2,true, true, this);

}

void game_t::draw_word_box(word_t word, int letter_code){
	sf::Sprite tile_sprite = get_tile_sprite(letter_code);
	for(auto it = word.tile_list.begin(); it != word.tile_list.end(); ++it){
		//sf::Sprite tile = it->blank_sprite;
		//tile.setColor(color);
		tile_sprite.setPosition(it->pos);
		//sprite.set
		window.draw(tile_sprite);
	}
}

std::vector<int> game_t::find_letter_indices(std::string str, char letter){
	std::vector<int> ind_vec;
	for(int i = 0; i < str.size(); i++){
		if(str[i] == letter) ind_vec.push_back(i);
	}
	return ind_vec;
}

void game_t::parse_clue_text(std::string *clue){
    int last_space_index;
    int stop_index = CLUE_LINE_LENGTH - 1;
    int transport_flag = 0;
    for(int i = 0; i < clue->length(); i++){
        if(transport_flag == 1){
            if(clue->at(i) == ' '){
                last_space_index = i;
                transport_flag = 0;
                clue->at(i) = '\n';
                stop_index = i + CLUE_LINE_LENGTH;
            }
            continue;
        }
        if(clue->at(i) == ' '){
            last_space_index = i;  
        }
        if(i == stop_index){
            std::cout << stop_index << "\n";
            if(clue->at(last_space_index) == '\n'){
                // moving to end of current word
                transport_flag = 1; 
            } else{
                clue->at(last_space_index) = '\n';
                stop_index = last_space_index + CLUE_LINE_LENGTH - 1;
            }
        }
    }
}

void game_t::generate_clue(std::list<tile_t>::iterator *tile_it_p, int cursor_index, word_t *word_p){
	int rand_ind = rand() % word_map[(*tile_it_p)->letter].size();
	std::string s = word_map[(*tile_it_p)->letter].at(rand_ind).first;
	std::string clue = word_map[(*tile_it_p)->letter].at(rand_ind).second;

	parse_clue_text(&clue);

	std::vector<int> v = find_letter_indices(s, (*tile_it_p)->letter);
	int tile_index = v[rand() % v.size()];
	
	if((*tile_it_p)->is_across){
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
		sf::Sprite cursor_tile;
		sf::Sprite letter_tile;
		if(it->cross_word_p != NULL){
			if(it->cross_word_p->is_correct)   
				draw_word_box(*it->cross_word_p, CURSOR_CROSS_WORD_CORRECT);
			else
				draw_word_box(*it->cross_word_p, CURSOR_CROSS_WORD_INCORRECT);
		}

		if(it != cursor.tile_it){
			if(it->is_correct){
				cursor_tile = sprite_map[CW_CORRECT];
			} else {
				cursor_tile = sprite_map[CW_INCORRECT];
			}
		}else {
			if(it->is_correct){
				cursor_tile = sprite_map[CT_CORRECT];
			} else {
				cursor_tile = sprite_map[CT_INCORRECT];
			}
		}
		cursor_tile.setPosition(it->pos);
		window.draw(cursor_tile);

		if(it->is_correct){
			letter_tile = sprite_map[it->letter];
		} else if (it->cursor_letter >= 'a'){

			letter_tile = sprite_map[it->cursor_letter];
		}

		letter_tile.setPosition(it->pos);
		window.draw(letter_tile);
	}
	
}


void game_t::handle_correct_word(){
	
	int cursor_index = 0;
	points += cursor.word_p->word_str.length();
	update_points_txt();
	for(auto it = cursor.word_p->tile_list.begin(); it != cursor.word_p->tile_list.end(); ++it){
		if(it->cross_word_p == NULL){
			generate_clue(&it, cursor_index, cursor.word_p);
			//std::cout << it->cross_word_ind <<std::endl;

			it->is_correct = true;
		}
		//std::cout << it.crossing_word;
		cursor_index++;

	}
	cursor.word_p->is_correct = true;
	auto it = cursor.word_p->tile_list.begin();
	std::advance(it, cursor.tile_it->cross_word_ind);
	cursor.tile_it = it;

	
}

void game_t::handle_key_input(sf::Keyboard::Key key_code){
	if(key_code == sf::Keyboard::Key::Up ||key_code == sf::Keyboard::Key::Down ||key_code == sf::Keyboard::Key::Left ||key_code == sf::Keyboard::Key::Right ){
		std::list<tile_t>::iterator boundary_it;
		if(key_code == sf::Keyboard::Key::Up || key_code == sf::Keyboard::Key::Left){
			boundary_it = cursor.word_p->tile_list.begin();
		} else if (key_code == sf::Keyboard::Key::Down || key_code == sf::Keyboard::Key::Right){
			boundary_it = --cursor.word_p->tile_list.end();
		}
		int input_along_word = (cursor.word_p->is_across &&  (key_code == sf::Keyboard::Key::Left || key_code == sf::Keyboard::Key::Right) ) || (!cursor.word_p->is_across &&  (key_code == sf::Keyboard::Key::Up || key_code == sf::Keyboard::Key::Down));
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
	else if (key_code == sf::Keyboard::Key::Enter){
		if(cursor.tile_it->cross_word_p != NULL){
			cursor.word_p = cursor.tile_it->cross_word_p;
			auto it = (cursor.word_p->tile_list.begin());
			std::advance(it, cursor.tile_it->cross_word_ind);
			cursor.tile_it = it;
		}
	}
	else if (key_code == sf::Keyboard::Key::RShift){
		if(cursor.tile_it != cursor.word_p->tile_list.begin()){
			cursor.tile_it = cursor.word_p->tile_list.begin();
		} else {
			cursor.tile_it = --cursor.word_p->tile_list.end();
		}
	}
	else if(key_code == sf::Keyboard::Key::Backspace){
		cursor.tile_it->cursor_letter = 0;

		if(cursor.tile_it != cursor.word_p->tile_list.begin()){
			std::advance(cursor.tile_it, -1);
		}
	}
	else if(key_code == sf::Keyboard::Key::Space){ 
		// reveal letter
		if(!cursor.word_p->is_correct && points >= REVEAL_COST){
			points -= REVEAL_COST;
			cursor.tile_it->is_correct = 1;
			if(cursor.check()){
				handle_correct_word();
			}
			std::advance(cursor.tile_it, 1);
			while(!cursor.word_p->is_correct && (cursor.tile_it == (cursor.word_p->tile_list.end()) || cursor.tile_it->is_correct)){
				if(cursor.tile_it == cursor.word_p->tile_list.end()){
					cursor.tile_it = cursor.word_p->tile_list.begin();
				}
				if(cursor.tile_it->is_correct){
					std::advance(cursor.tile_it, 1);
				}
			}
		}
	} else if(key_code == sf::Keyboard::Key::Escape){
		this->state = IDLE;
	}
	update_clue_txt();
	
}



void game_t::generate_start_clues(word_t *start_word_p){
	int i = 0;
	for(auto it = start_word_p->tile_list.begin(); it != start_word_p->tile_list.end(); ++it){
		generate_clue(&it, i++, start_word_p);
	}
}

void game_t::draw_text(){
	sf::Vector2i across_clue_pixel_pos(ACROSS_CLUE_TEXT_X*window_scale,ACROSS_CLUE_TEXT_Y*window_scale);
	sf::Vector2i down_clue_pixel_pos(DOWN_CLUE_TEXT_X*window_scale,DOWN_CLUE_TEXT_Y*window_scale);
	sf::Vector2i points_pixel_pos(POINTS_TEXT_X*window_scale,POINTS_TEXT_Y*window_scale);

	sf::Vector2f across_clue_world_pos = window.mapPixelToCoords(across_clue_pixel_pos);
	sf::Vector2f down_clue_world_pos = window.mapPixelToCoords(down_clue_pixel_pos);
	sf::Vector2f points_world_pos = window.mapPixelToCoords(points_pixel_pos);
	
	across_clue_txt.setPosition(across_clue_world_pos.x, across_clue_world_pos.y);
	down_clue_txt.setPosition(down_clue_world_pos.x, down_clue_world_pos.y);
	points_txt.setPosition(points_world_pos.x, points_world_pos.y);
	window.draw(across_clue_txt);
	window.draw(down_clue_txt);
	window.draw(points_txt);

}


void game_t::update_view(){
	int x, y;
	if(!cursor.word_p->is_across){
		x = cursor.word_p->tile_list.begin()->pos.x + TILE_WIDTH/2;
		y =  cursor.word_p->tile_list.begin()->pos.y + cursor.word_p->tile_list.size() * TILE_HEIGHT ;
	} else {
		x =  cursor.word_p->tile_list.begin()->pos.x + cursor.word_p->tile_list.size() * TILE_WIDTH ;
		y = cursor.word_p->tile_list.begin()->pos.y + TILE_HEIGHT/2;
	}
	//std::cout << cursor.word_p->tile_list.begin()->pos.y + cursor.word_p->tile_list.size() * TILE_HEIGHT << std::endl;
	view.move(view.getCenter().x < x ? 2 : view.getCenter().x > x ? -2 : 0
			, view.getCenter().y < y ? 2 : view.getCenter().y > y ? -2 : 0);
	//std::cout << view.getCenter().x << std::endl;
	window.setView(view);

	//if(is_cursor.word_p->tile_list.size();
	//
}
