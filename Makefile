build:
	gcc -Wall -o ./bin/ff ./src/main.c ./src/board.c

run:
	./bin/ff

clean:
	rm ./bin/ff
