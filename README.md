# TECT: Explicitly Controlled Testing

You can test C code without hiding control flow in macros.

We illustrate this with a goofy example, written in GNU C23.

## Example

Macros `tect_once` and `tect_report` hide checking and reporting logic.

```c
#include <tect.h>

static int check_example() {
  const int answer = 6 * 9;

  if (!tect_once(answer == 42)) // Triggers at most _once_ by hiding state.
    return tect_report("answer == %d", answer); // Appends to the output log.

  if (!tect_once(3 == 4)) // We next check this.
    return tect_report();

  return 0; // => test done. Other return values are yours to interpret.
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

Note that we run `check_example` twice.
Returning and retrying gives you freedom to interpret and handle the test
status however the language allows.

This repeated-run style is _inspired by_ (and not an implementation of)
Andrei Alexandrescu's
["Unit Test Should Nest"](https://youtu.be/trGJsOcA4hY?t=2887),
which is inspired by
[Catch2](https://github.com/catchorg/Catch2).

See `main.c` for more thorough examples. Run `main.c` with `make run`.

## Counter-example

Common C testing tools construct domain-specific languages from macros
that hide both declarations and control flow.

For example, a pastiche of the C testing tools from
[Awesome C](https://github.com/oz123/awesome-c#testing)
could look like:

```c
DECLARE_TEST(context, "name") {
    CHECK(6 * 9 == 42);
    CHECK(3 == 4);
}

```

By hiding core language features, such designs make me I feel uncomfortably
incapable of composing these tools with core language features.

Our `tect` macros also hide state and output.
And they are arguably disgusting abuses of language extensions.a
But they do give control of control flow to users.

## Usage

Install from `Ubuntu 23.04`:

```shell
sudo apt install clang-format gcc-13 make

```

Build and execute:

```shell
make

```

Attach git pre-commit hooks:

```shell
ln -s pre-commit .git/hooks/pre-commit

```
