[//]: # (WARNING: We generate README.md from README.template.md.)
[//]: # (Do not edit README.md directly.)

# TECT: Explicitly Controlled Testing

You can test C code without hiding control flow in macros.

We illustrate this with a silly little example, written in GNU C23.

## Example

Macros `tect_once` and `tect_report` hide checking and reporting logic.

[//]: # (Replace "SCRIPT_*" with generated content)

```c
// example_one.c
#include "tect.h"

static int check_for_tea_too() {
  const int answer = 6 * 9;

  if (!tect_once(answer == 42)) // Triggers at most _once_ by hiding state.
    return tect_report("answer == %d", answer); // Appends to the output log.

  if (!tect_once(3 == 4)) // We next check this.
    return tect_report();

  return 0; // => test done. Other return values are yours to interpret.
}

int main() {
  while (check_for_tea_too())
    ;
}
```

This outputs:

```text
example_one.c:6: check_for_tea_too: !tect_once(answer == 42); answer == 54
example_one.c:9: check_for_tea_too: !tect_once(3 == 4); 
```

Note that we run `check_example` twice.
Returning and retrying gives you freedom to interpret and handle the returned
value however the language allows.

See `example_two.c` for a more involved example.

This repeated-run style is _inspired by_ (and not an implementation of)
Andrei Alexandrescu's
["Unit Test Should Nest"](https://youtu.be/trGJsOcA4hY?t=2887),
which is inspired by
[Catch2](https://github.com/catchorg/Catch2).

## Non-Example

Common C testing tools use such powerful macros that their code does not
resemble C.

They instead define new, domain-specific languages, because their macros
hide both declarations and control flow.

For example, a pastiche of the C testing tools from
[Awesome C](https://github.com/oz123/awesome-c#testing)
could look like:

```c
DECLARE_TEST(context, "test_description") {
    CHECK(6 * 9 == 42);
    CHECK(3 == 4);
}

```

By hiding core language features, such designs make me I feel uncomfortably
incapable of composing these tools with core language features.

Our `tect` macros also hide state and output.

And they are arguably disgusting abuses of language extensions.

But they do give users control of control flow.

## Usage

Install tools in `Ubuntu 23.04`:

```shell
sudo apt install clang-format gcc-13 make

```

Build and run our examples:

```shell
make

```

Other make commands:

```shell
make test # Apply some basic checks to the example outputs.

make fmt # Auto-format C source files.

make clean # Remove build artifacts and log files.

make README.md # Generate `README.md` from the template file.

```

For development, please run `make -s README.md fmt test` before each commit.

## Documentation

We generate this section from comments in `tect.h`.

[//]: # (Append in-source documentation below)

### `tect_once` (function-like macro)

`(expression) -> int`

Return assertion's integral value, and print when it is _first_ false.

You should follow this with `tect_report`, as follows:

```c
static int check_example() {
    const int answer = 6 * 9;

    if (!tect_once(answer == 42))
      return tect_report("answer == %d", answer);

    if (!tect_once(3 == 4))
      return tect_report();

    return 0;
}
```

To fully run this test, use a loop such as:

```c
    while(check_example())
        ;
```

We track the first activation in a mutating static variable.

On a false assertion, our printed message adapts `assert`'s style.

### `tect_report` (function-like macro)

`(const char *format, ...) -> int, or () -> int`

Call `printf` with any arguments, print `'\n'`, and return 1.

See `tect_once` for usage.

[//]: # (Avoid trailing newlines)
