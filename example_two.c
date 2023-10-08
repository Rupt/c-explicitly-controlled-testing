#include "tect.h"
#include <stdio.h>

int check_some_code() {
  const char code[] = "--<-<<+[+[<+>--->->->-<<<]>]<<--.<++++++.<<-..<<.<+.";

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
  int n_false = 0;
  while (check_some_code()) // Returning lets us inspect externally.
    ++n_false;
  printf("Number of negative checks in check_some_code: %d\n", n_false);
}
