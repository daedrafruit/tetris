make: clean build run

build: src/tetris.c
	gcc -g -o tetris src/tetris.c 

run: build
	./tetris

clean:
	rm -f tetris
