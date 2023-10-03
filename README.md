# TECT: Explicitly Controlled Testing

You can test C code without hiding control flow in macros.

## Example

Macros `tect_once` and `tect_report` hide checking and reporting logic.

```c
#include <tect.h>

static int check_example() {
  const int answer = 6 * 9;

  if (!tect_once(answer == 42)) // Only triggers once by hiding global state.
    return tect_report("answer == %d", answer); // Appends to the output log.

  if (!tect_once(3 == 4)) // We next check this.
    return tect_report();

  return 0; // 0 => test done. Other return values are yours to interpret.
}

int main() {
  while (check_example())
    ;
}
```

Running this yields:

```shell
main.c:7: check_example: !tect_once(answer == 42); answer == 54
main.c:10: check_example: !tect_once(3 == 4);
```

See `main.c` for more thorough examples. Run `main.c` with `make run`.

TODO(#5) Reference inspiration

## Counter-example

A pastiche of other C testing tools looks something like this:
TODO(#5) Counter-example
TODO(#5) Reference list of examples

## Install

From `Ubuntu 23.04`,

```shell
sudo apt install clang-format gcc-13 make

```
