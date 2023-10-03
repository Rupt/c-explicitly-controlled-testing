#include "tect.h"

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
