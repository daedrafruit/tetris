make: clean build run

build: src/tetris.c
	#gcc -g -o tetris tetris.c 
	gcc -g -Iinclude -lSDL3 -lglfw -o tetris src/render.c

run: build
	./tetris

clean:
	rm -f tetris
