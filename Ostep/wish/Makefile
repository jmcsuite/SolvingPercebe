wish: wish.o executor.o directory.o path_handler.o redirect.o
	gcc -o wish wish.o executor.o directory.o path_handler.o redirect.o

wish.o: wish.c
	gcc -g -c -Wall -Werror wish.c

executor.o: executor.c executor.h
	gcc -g -c -Wall -Werror executor.c

directory.o: directory.c directory.h
	gcc -g -c -Wall -Werror directory.c

path_handler.o: path_handler.c path_handler.h
	gcc -g -c -Wall -Werror path_handler.c

redirect.o: redirect.c redirect.h
	gcc -g -c -Wall -Werror redirect.c

clean:
	rm -f wish.o wish path_handler.o directory.o executor.o redirect.o
