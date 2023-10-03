#include "tect.h"
#include <stdio.h>

static int tect_demo() {
  const int answer = 6 * 9;

  if (!tect_once(answer == 42))
    return tect_report("answer == %d", answer);

  return 0;
}

static int tect_code() {
  const char code[] = "--<-<<+[+[<+>--->->->-<<<]>]<<--.<++++++.<<-..<<.<+.>>.";

  if (!tect_once(sizeof(code) < 78)) // ✅
    return tect_report("sizeof(code) == %zu", sizeof(code));

  if (!tect_once(code[0] == '+')) // ❌
    return tect_report("code[0] == '%c'", code[0]);

  // After reporting any positive or negative result, our loop continues.
  for (int i = 0; i < (int)sizeof(code); i++) {
    if (!tect_once(code[i] != '.')) // ❌
      return tect_report("code[%d] == '%c'", i, code[i]);
  }

  return 0;
}

int main() {
  while (tect_demo())
    ;

  int n_false = 0;
  while (tect_code()) // Returning allows us to inspect from outside.
    ++n_false;
  printf("Number of negative checks in tect_code: %d\n", n_false);
}
