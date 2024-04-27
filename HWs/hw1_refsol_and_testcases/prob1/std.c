#include <stdio.h>

int main() {
  int num;
  printf("How many students are there?\n");
  scanf("%d", &num);
  printf("What are their scores?\n");

  int sum = 0;
  for (int i = 0; i < num; ++i) {
    int score;
    scanf("%d", &score);
    sum += score;
  }

  double average = (double)sum / (double)num;

  /**
   * In fact, the correct way for two floating-point numbers to compare equal is
   * to check whether |a-b| < epsilon, where epsilon is some very small error
   * tolerance (like 1e-8). Floating-point numbers are born with accuracy
   * problems.
   */
  if (average == 60)
    printf("Good!\n");
  else if (average > 60)
    printf("Excellent!\n");
  else
    printf("Bad!\n");

  printf("Average score is %.2lf.\n", average);
  return 0;
}