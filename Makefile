CCARGS := -std=gnu2x -Wall -Wextra -Werror -O1
CC := gcc-13

.PHONY: run
run: main
	./main

.PHONY: fmt
fmt: *.h *.c 
	clang-format -Werror -style=Mozilla -i $^

.PHONY: clean
clean:
	rm -f main

main: main.c tect.h
	${CC} $(CCARGS) -o $@ $*.c
