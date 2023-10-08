/* Reproduce the partial example from "tect.h". */
#include "tect.h"

int square(int num) { return num & /* error */ num; }

int check_example() {
  const int result = square(4);

  if (!tect_once(result == 16))
    return tect_report("result == %d", result);

  if (!tect_once(square(0) == 0))
    return tect_report();

  return 0;
}

int main() {
  while (check_example())
    ;
}
