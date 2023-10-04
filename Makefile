CCARGS := -std=gnu2x -Wall -Wextra -Werror -O1
CC := gcc-13

.PHONY: run
run: example_readme main
	./example_readme
	./main

.PHONY: fmt
fmt: *.h *.c
	clang-format -Werror -i $^

.PHONY: clean
clean:
	rm -f main

README.md: README.template.md example_readme.c example_readme.log
	cp $< $@
	sed -e "/SCRIPT_CONTENT/{r example_readme.c" -e "d}" -i $@
	sed -e "/SCRIPT_OUTPUT/{r example_readme.log" -e "d}" -i $@

%: %*.c tect.h
	${CC} $(CCARGS) -o $@ $<

%.log: %
	./$< > $@
