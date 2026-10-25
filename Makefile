CXX := g++
SRC_DIR := src
OBJ_DIR := obj
SRCS := cursor.cpp game.cpp main.cpp tile.cpp word.cpp animation.cpp
SRCS_WITH_PATH := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(patsubst %.cpp,obj/%.o,$(SRCS))
TARGET := crossword
SERIALFLAGS := -I.\libraries\cereal-1.3.2\cereal-1.3.2\include -lstdc++
CXXFLAGS :=  -I./libraries/SFML-2.5.1/include -fpermissive -mwindows $(SERIALFLAGS) 

LDFLAGS :=  -L./libraries/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system 


all: $(TARGET)
	./$<
# 	rm -f *.exe $(OBJ_DIR)/*.o
	rm -f $(OBJ_DIR)/*.o

$(TARGET) : $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o:  $(SRC_DIR)/%.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

clean:
	rm -f *.exe $(OBJ_DIR)/*.o
	
wordmap:
	gcc -o build_word_map $(SRC_DIR)/word_mapper.cpp $(SERIALFLAGS)
	./build_word_map
	

debug:
	g++ -o test $(SRC_DIR)/debug.cpp
	./test

play:
	./crossword
