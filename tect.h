// ### `tect_once` (function-like macro)
//
// `(expression) -> int`
//
// Return assertion's integral value, and print when it is _first_ false.
//
// You should follow this with `tect_report`, as follows:
//
// ```c
// static int check_example() {
//     const int answer = 6 * 9;
//
//     if (!tect_once(answer == 42))
//       return tect_report("answer == %d", answer);
//
//     if (!tect_once(3 == 4))
//       return tect_report();
//
//     return 0;
// }
// ```
//
// To fully run this test, use a loop such as:
//
// ```c
//     while(check_example())
//         ;
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

// ### tect_report (function-like macro)
//
// `(const char *format, ...) -> int, or () -> int`
//
// Call `printf` with any arguments, print `'\n'`, and return 1.
//
// See `tect_once` for usage.
//
#define tect_report(...)                                                       \
  ({                                                                           \
    __VA_OPT__(__builtin_printf(__VA_ARGS__);)                                 \
    __builtin_printf("\n");                                                    \
    1;                                                                         \
  })

static const char *unstable_tect_once_format = "%s:%d: %s: !tect_once(%s); ";
// [//]: # (Avoid trailing newlines)
