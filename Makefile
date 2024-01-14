#SRC_DIR := src
#OBJ_DIR := obj
#SRCS := cursor.cpp game.cpp main.cpp tile.cpp word.cpp
#SRCS_WITH_PATH := $(addprefix $(SRC_DIR)/,$(SRCS))
#OBJS := $(patsubst %.cpp,obj/%.o,$(SRCS))
#TARGET := crossword
#FLAGS :=  -IC:/SFML-2.5.1/include -DSFML_STATIC -fpermissive -mwindows
#LIBS :=  -LC:/SFML-2.5.1/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32


#all: $(TARGET)

#$(TARGET) : $(OBJS)
	#g++ -o crossword $(LIBS) $<

#$(OBJ_DIR)/%.o:  $(SRC_DIR)/%.cpp
	##@mkdir -p $(@D)
	#g++ $(FLAGS) -c -o $@ $<
	##g++ -c $(SRCS_WITH_PATH) $(FLAGS)
	##./crossword.exe

#clean:
	#rm -f *.exe *.o

#all: $(TARGET)

#$(TARGET): $(OBJS)
	#g++ $(LIBS) -o $@ $^ 

#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	#@mkdir -p $(@D)
	#g++ $(FLAGS) -c $@ $< 
	##./crossword.exe

#clean:
	#rm -f *.exe *.o
all:
	g++ -c src/*.cpp -IC:/SFML-2.5.1/include -DSFML_STATIC -fpermissive
	g++ *.o -o crossword -LC:/SFML-2.5.1/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -fpermissive 
	./crossword.exe

clean:
	rm -f *.exe *.o
