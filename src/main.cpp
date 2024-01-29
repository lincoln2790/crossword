#include "../include/const.hpp"
#include "../include/tile.hpp"
#include "../include/word.hpp"
#include "../include/cursor.hpp"
#include "../include/game.hpp"
#include "../include/animation.hpp"

int main() {
	game_t game;
	animation_t ani(ANI_STR, 80, 80, 0, 0, &game, true);
	animation_t clue_box(CLUE_BOX_STR, CLUE_BOX_WIDTH, CLUE_BOX_HEIGHT, CLUE_BOX_X, CLUE_BOX_Y, &game, false);

	while(game.window.isOpen()){
		sf::Event event;
		while(game.window.pollEvent(event)){
			// events that can occur during all game states
			switch(event.type){
				case sf::Event::Closed:
					game.window.close();
					break;
			}
			
			switch(game.state){
				case IDLE:
					switch(event.type){
						case sf::Event::KeyPressed:
							switch(event.key.code){
								case sf::Keyboard::Key::Space:
									game.state = PLAYING;
									continue;
									//break;
							}
					}
					break;
				case PLAYING:
					switch(event.type){
						case sf::Event::TextEntered:
								//cursor.tile->cursor_letter = event.text.unicode;
							if((!game.cursor.word_p->is_correct) && (event.text.unicode >= 'a' && event.text.unicode <= 'z')){
								game.cursor.tile_it->cursor_letter = event.text.unicode;
								if(game.cursor.check()){
									int cursor_index = 0;
									for(auto it = game.cursor.word_p->tile_list.begin(); it != game.cursor.word_p->tile_list.end(); ++it){
										if(!it->is_correct){
											game.generate_clue(&it, cursor_index, game.cursor.word_p);
											//std::cout << it->cross_word_ind <<std::endl;

											it->is_correct = true;
										}
										//std::cout << it.crossing_word;
										cursor_index++;

									}
									game.cursor.word_p->is_correct = true;
									auto it = game.cursor.word_p->tile_list.begin();
									std::advance(it, game.cursor.tile_it->cross_word_ind);
									game.cursor.tile_it = it;
									continue;
								}
								std::advance(game.cursor.tile_it, 1);
								while(!game.cursor.word_p->is_correct && (game.cursor.tile_it == (game.cursor.word_p->tile_list.end()) || game.cursor.tile_it->is_correct)){
									if(game.cursor.tile_it == game.cursor.word_p->tile_list.end()){
										game.cursor.tile_it = game.cursor.word_p->tile_list.begin();
									}
									if(game.cursor.tile_it->is_correct){
										std::advance(game.cursor.tile_it, 1);
									}
								}
							}
							break;
						case sf::Event::KeyPressed:
							game.handle_key_input(event.key.code); 
							break;


						case sf::Event::Resized:

							// update the view to the new size of the window
							int window_width = game.window.getSize().x;
							int window_height = game.window.getSize().y;

							int new_dim = std::max(std::min(window_width, window_height), MIN_WINDOW_DIM);
							sf::Vector2u new_size(new_dim, new_dim);
							game.window.setSize(new_size);
							sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
							game.window.setView(sf::View(visibleArea));
							
							break;
                	
					//break;
				}
			}
		}
		//game.wiow.move(100.f, 100.f);
		//game.view.move(1.0f, 0.0f);
		//game.window.setView(game.view);
		game.window.clear(BACKGROUND_COLOR);
		
		game.update_view();
		switch(game.state){
			case IDLE:
				break;
			case PLAYING:
				ani.draw_sprite(0);
				
				
				//for(auto word : game.word_list){
					//if(!word.is_correct) game.draw_word_box(word, BG_INCORRECT);

				//}
				for(auto word : game.word_list){
					if(word.is_correct) game.draw_word_box(word, BG_CORRECT);

				}
				game.draw_cursor_word();
				clue_box.draw_sprite(0);
				game.draw_text();
				break;
		}
		game.window.display();
		
	}
	return 0;
}
