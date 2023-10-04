CCARGS := -std=gnu2x -Wall -Wextra -Werror -O1
CC := gcc-13

.PHONY: run
run: main
	./main

.PHONY: fmt
fmt: *.h *.c
	clang-format -Werror -i $^

.PHONY: clean
clean:
	rm -f main

main: main.c tect.h
	${CC} $(CCARGS) -o $@ $<
