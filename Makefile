all:
	g++ -c src/*.cpp -IC:/SFML-2.5.1/include -DSFML_STATIC -fpermissive
	g++ *.o -o crossword -LC:/SFML-2.5.1/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -fpermissive 
	./crossword.exe

clean:
	rm -f *.exe *.o
