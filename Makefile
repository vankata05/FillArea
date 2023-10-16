run: tests
	./tests

tests: tests.o test1.o unity.o
	gcc -o tests tests.o test1.o unity.o

tests.o: tests.c
	gcc -Wall -c -o tests.o tests.c

test1.o: test1.c
	gcc -Wall -c -o test1.o test1.c

unity.o: ./Unity/src/unity.c
	gcc -Wall -c -o unity.o ./Unity/src/unity.c

clean:
	rm -f tests tests.o test1.o unity.o