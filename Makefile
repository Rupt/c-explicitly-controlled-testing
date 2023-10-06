CCARGS := -std=gnu2x -Wall -Wextra -Werror -O1
CC := gcc-13

.PHONY: run
run: example_one.out example_two.out
	./example_one.out
	./example_two.out

.PHONY: fmt
fmt: *.h *.c
	clang-format -Werror -i $^

.PHONY: check
check: example_one.log example_two.log
	grep -qE "answer == 42.+answer == 54" example_one.log
	grep -q "3 == 4" example_one.log
	grep -qE "negative checks.+: 2" example_two.log
	grep -q "^example_one.c" example_one.log
	grep -q "^example_two.c" example_two.log
	! grep -q "^example_two.c" example_one.log
	! grep -q "^example_one.c" example_two.log

README.md: README.template.md example_one.c example_one.log tect.h
	sed -e "/SCRIPT_CONTENT/{r example_one.c" -e "d}" \
	    -e "/SCRIPT_OUTPUT/{r example_one.log" -e "d}" $< > $@
	echo >> $@ # newline
	grep -E "^\/\/ ?" tect.h | sed -E "s|^\/\/ ?||" >> $@

%.out: %.c tect.h
	${CC} $(CCARGS) -o $@ $<

%.log: %.out
	./$< > $@
