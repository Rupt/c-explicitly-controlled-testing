#include "tect.h"

static int test_demo() {
  const int answer = 6 * 9;

  if (!test_once(answer == 42))
    return test_report("answer == %d", answer);

  return 0;
}

static int test_code() {
  const char code[] = "--<-<<+[+[<+>--->->->-<<<]>]<<]--.";

  if (!test_once(sizeof(code) < 78)) // ✅
    return test_report("sizeof(code) == %zu", sizeof(code));

  if (!test_once(code[0] == '+')) // ❌
    return test_report("code[0] == '%c'", code[0]);

  // After reporting any positive or negative result, we continue...
  int n_open_brackets = 0;
  for (int i = 0; i < (int)sizeof(code); i++) {
    switch (code[i]) {
    case '[':
      ++n_open_brackets;
      break;
    case ']':
      --n_open_brackets;
      break;
    }
    if (n_open_brackets > 0)
      continue;

    // ...to report on further checks. We must only close matched brackets.
    if (!test_once(code[i] != ']')) // ❌
      return test_report("code[%d] == '%c'", i, code[i]);
  }

  return 0;
}

int main() {
  while (test_demo())
    ;
  while (test_code())
    ;
}
