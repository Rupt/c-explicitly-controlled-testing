CCARGS := -std=gnu2x -Wall -Wextra -Werror -O1
CC := gcc

.PHONY: help
help:
	@echo "TODO(#6)"

.PHONY: demo
demo: main
	./main

%: %*.c tect.h
	${CC} $(CCARGS) -o $@ $*.c

.PHONY: fmt
fmt: *.c *.h
	clang-format -Werror -style=Mozilla -i $^

.PHONY: clean
clean:
	rm -f main
