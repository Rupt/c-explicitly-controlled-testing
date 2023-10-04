CCARGS := -std=gnu2x -Wall -Wextra -Werror -O1
CC := gcc-13

.PHONY: run
run: example_one example_two
	./example_one
	./example_two

.PHONY: fmt
fmt: *.h *.c
	clang-format -Werror -i $^

.PHONY: clean
clean:
	rm -f example_two

README.md: README.template.md example_one.c example_one.log
	cp $< $@
	sed -e "/SCRIPT_CONTENT/{r example_one.c" -e "d}" -i $@
	sed -e "/SCRIPT_OUTPUT/{r example_one.log" -e "d}" -i $@

%: %*.c tect.h
	${CC} $(CCARGS) -o $@ $<

%.log: %
	./$< > $@
