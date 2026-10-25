// // #include "../include/const.hpp"
// // #include "../include/tile.hpp"
// // #include "../include/word.hpp"
// // #include "../include/cursor.hpp"
// // #include "../include/game.hpp"
// // #include "../include/animation.hpp"

#include <iostream>
// // #include <stdio>
#include <string>

int CLUE_LINE_LENGTH = 10;
void parse_clue_text(std::string *clue){
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
	
int main() {
    std::string test_string ("Strings are objects that represent sequences of characters The standard string class provides support for such objects with an interface similar to that of a standard container of bytes, but adding features specifically designed to operate with strings of single-byte");
        // characters The string class is an instantiation of the basic_string class template that uses char (i.e., bytes) as its character type, with its default char_traits and allocator types (see basic_string for more info on the template).Note that this class handles bytes independently of the encoding used: If used to handle sequences of multi-byte or variable-length characters (such as UTF-8), all members of this class (such as length or size), as well as its iterators, will still operate in terms of bytes (not actual encoded characters).");
    parse_clue_text(&test_string);
    std::cout << test_string;

    return 0;
}
