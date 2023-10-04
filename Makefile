CCARGS := -std=gnu2x -Wall -Wextra -Werror -O1
CC := gcc-13

.PHONY: run
run: example_one.out example_two.out
	./example_one.out
	./example_two.out

.PHONY: test
test: example_one.log example_two.log
	# Logs must include expected reports
	grep -qE "answer == 42.+answer == 54" example_one.log
	grep -q "3 == 4" example_one.log
	grep -qE "negative checks in.+: 2" example_two.log
	# Logs must reference the corresponding source files
	grep -q "^example_one.c" example_one.log
	grep -q "^example_two.c" example_two.log
	! grep -q "^example_two.c" example_one.log
	! grep -q "^example_one.c" example_two.log

.PHONY: fmt
fmt: *.h *.c
	clang-format -Werror -i $^

.PHONY: clean
clean:
	rm -f *.out *.log

README.md: README.template.md example_one.c example_one.log tect.h
	# Substitute markers
	cp $< $@
	sed -e "/SCRIPT_CONTENT/{r example_one.c" -e "d}" -i $@
	sed -e "/SCRIPT_OUTPUT/{r example_one.log" -e "d}" -i $@
	# Append in-source documentation
	echo >> $@ # One new line
	grep -E "^// ?" tect.h | sed -E "s|^// ?||" >> $@

%.out: %.c tect.h
	${CC} $(CCARGS) -o $@ $<

%.log: %.out
	./$< > $@
