all: mysort

mysort:
	gcc -Wall -Wextra -Werror -pedantic -std=c99 -g -c helpers.c sort.c
	gcc -Wall -Wextra -Werror -pedantic -std=c99 -g -o mysort *.o main.c
	
clean:
	rm -f mysort helpers.o sort.o
	
.PHONY clean

