wish: wish.o executor.o directory.o
	gcc -o wish wish.o executor.o directory.o

wish.o: wish.c
	gcc -g -c -Wall -Werror wish.c

executor.o: executor.c
	gcc -g -c -Wall -Werror executor.c

directory.o: directory.c
	gcc -g -c -Wall -Werror directory.c

clean:
	rm -f wish.o wish
