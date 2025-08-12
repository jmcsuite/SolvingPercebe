wish: wish.o executor.o
	gcc -o wish wish.o executor.o

wish.o: wish.c
	gcc -g -c -Wall -Werror wish.c

executor.o: executor.c
	gcc -g -c -Wall -Werror executor.c

clean:
	rm -f wish.o wish
