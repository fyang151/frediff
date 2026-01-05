main: src/main.c src/find_middle.c
	gcc -Wall src/main.c src/find_middle.c -o bin/main

run: main
	./bin/main
	
clean:
	rm -f bin/main
