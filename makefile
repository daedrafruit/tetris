make: clean build run

build: tetris.c
	#gcc -g -o tetris tetris.c 
	gcc -g -lSDL3 -lglfw -o tetris render.c

run: build
	./tetris

clean:
	rm -f tetris
