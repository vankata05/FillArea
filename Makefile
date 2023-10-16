run: tests
	./tests

tests: unit.o unity.o
	gcc -o tests unit.o unity.o

unit.o: unit.c
	gcc -Wall -c -o unit.o unit.c

unity.o: ./Unity/src/unity.c
	gcc -Wall -c -o unity.o ./Unity/src/unity.c

clean:
	rm -f tests unit.o unity.o