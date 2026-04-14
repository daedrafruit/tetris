make: clean build run

build: tetris.c
	gcc -g -o tetris tetris.c 

run: build
	./tetris

clean:
	rm -f tetris
