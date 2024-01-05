build:
	gcc -Wall -o ./bin/ff ./src/main.c ./src/display.c ./src/queue.c `sdl2-config --cflags --libs` 

run:
	./bin/ff

clean:
	rm ./bin/ff
