#include <math.h>
#include <stdio.h>

#define EPS 0.001

int main() {
  int x1, x2, y1, y2;
  scanf("(%d,%d)\n(%d,%d)", &x1, &y1, &x2, &y2);
  if (x1 == x2) {
    printf("x = %d.00", x1);
    return 0;
  }

  double k = 1.0 * (y1 - y2) / (x1 - x2);
  double b = y1 - k * x1;
  if (fabs(k) < EPS)
    k = 0;
  if (fabs(b) < EPS)
    b = 0;
  printf("y = %.2lfx %c %.2lf", k, (b < 0 ? '-' : '+'), fabs(b));
  return 0;
}