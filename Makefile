.PHONY: fmt
fmt: tect.c
	clang-format -Werror -style=Mozilla -i $^
