// ## test_once (function-like macro)
//
// Return assertion's integral value, and print when it is *first* false.
//
// You should follow this with `test_report`, as follows:
//
// ```c
// static int
// test_example()
// {
//     int x = 5;
//
//     if (!test_once(2 + 2 == x))
//         return test_report("x == %d.", x);
//     if (!test_once(2 + 2 == 4))
//         return test_report();
//
//     return 0;
// }
// ```
//
// To fully run this test, use a loop such as:
//
// ```c
//     while(test_example())
//         ;
// ```
//
// We track the first activation in a mutating static variable.
//
// On a false assertion, our printed message adapts `assert`'s style.
//
// (expression) -> int
#define test_once(assertion)                                                   \
  ({                                                                           \
    static bool has_been_false = false;                                        \
    const bool pass = (bool)(assertion) | has_been_false;                      \
    if (!__builtin_expect(pass, 1)) {                                          \
      has_been_false = true;                                                   \
      __builtin_printf(                                                        \
        unstable_test_format, __FILE__, __LINE__, __FUNCTION__, (#assertion)); \
    }                                                                          \
    (int)__builtin_expect(pass, 1);                                            \
  })

// ## test_report (function-like macro)
//
// Call printf with any arguments, print '\n', and return a nonzero integer.
//
// See `test_once` for usage advice.
//
// (const char *format, ...) -> int, or () -> int
#define test_report(...)                                                       \
  ({                                                                           \
    __VA_OPT__(__builtin_printf(__VA_ARGS__);)                                 \
    __builtin_printf("\n");                                                    \
    1;                                                                         \
  })

static const char* unstable_test_format = "%s:%d: %s: Test `%s` is false; ";

static int
test_demo()
{
  int x = 11;

  if (!test_once(x == 3))
    return test_report();
  if (!test_once(x == 5))
    return test_report("x == %d", x);
  if (!test_once(0 <= x && x <= 9))
    return test_report("x == %d", x);
  if (!(test_once(0 <= x) && test_once(x <= 9)))
    return test_report("x == %d", x);
  if (!test_once(x == x))
    return test_report();

  return 0;
}

static int
test_example()
{
  int x = 5;
  if (!test_once(2 + 2 == x))
    return test_report("x == %d.", x);
  if (!test_once(2 + 2 == 4))
    return test_report();
  return 0;
}

int
main()
{
  while (test_demo())
    ;
  while (test_example())
    ;
}
