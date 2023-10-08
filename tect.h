// ### `tect_once` (function-like macro)
//
// `(expression) -> int`
//
// Return assertion's integral value, and print when it is _first_ false.
//
// You should follow `tect_once` by calling `tect_report` as follows:
//
// ```c
// int check_example() {
//   const int result = square(4);
//
//   if (!tect_once(result == 16))
//     return tect_report("result == %d", result);
//
//   if (!tect_once(square(0) == 0))
//     return tect_report();
//
//   return 0;
// }
// ```
//
// To fully run this test, use a loop such as:
//
// ```c
//  while (check_example())
//    ;
// ```
//
// We track the first activation in a mutating static variable.
//
// On a false assertion, our printed message adapts `assert`'s style.
//
#define tect_once(assertion)                                                   \
  ({                                                                           \
    static bool has_been_false = false;                                        \
    const bool pass = (bool)(assertion) | has_been_false;                      \
    if (!__builtin_expect(pass, 1)) {                                          \
      has_been_false = true;                                                   \
      __builtin_printf(unstable_tect_once_format, __FILE__, __LINE__,          \
                       __FUNCTION__, (#assertion));                            \
    }                                                                          \
    (int)__builtin_expect(pass, 1);                                            \
  })

// ### `tect_report` (function-like macro)
//
// `(const char *format, ...args) -> int, or () -> int`
//
// Call `printf` with any arguments, print `'\n'`, and return (int) 1.
//
// See `tect_once` for usage.
//
#define tect_report(...)                                                       \
  ({                                                                           \
    __VA_OPT__(__builtin_printf(__VA_ARGS__);)                                 \
    __builtin_printf("\n");                                                    \
    (int)1;                                                                    \
  })

/* unstable_tect_* => Don't rely on this. Could be misnamed "private API". */
static const char *unstable_tect_once_format = "%s:%d: %s: !tect_once(%s); ";

// [//]: # (Avoid trailing newlines)
