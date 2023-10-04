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
