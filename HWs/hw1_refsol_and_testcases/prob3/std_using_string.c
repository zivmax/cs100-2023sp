#include <stdio.h>

const char digits[][10] = {"",     "one", "two",   "three", "four",
                           "five", "six", "seven", "eight", "nine"};
const char teens[][10] = {"ten",      "eleven",  "twelve",  "thirteen",
                          "fourteen", "fifteen", "sixteen", "seventeen",
                          "eighteen", "nineteen"};
const char tys[][10] = {"",      "",      "twenty",  "thirty", "forty",
                        "fifty", "sixty", "seventy", "eighty", "ninety"};

void spell(int num) {
  if (num < 100) {
    switch (num / 10) {
      case 0:
        printf("%s", digits[num % 10]);
        break;
      case 1:
        printf("%s", teens[num % 10]);
        break;
      default:
        printf("%s", tys[num / 10]);
        if (num % 10 != 0) {
          printf("-%s", digits[num % 10]);
        }
        break;
    }
  } else if (num < 1000) {
    printf("%s hundred", digits[num / 100]);
    if (num % 100 != 0) {
      printf(" and ");
      spell(num % 100);
    }
  } else {
    spell(num / 1000);
    printf(" thousand");
    if (num % 1000 != 0) {
      if ((num / 100) % 10 == 0) {
        printf(" and ");
      } else {
        printf(" ");
      }
      spell(num % 1000);
    }
  }
}

int main() {
  int num;
  scanf("%d", &num);
  if (num == 0) {
    printf("zero");
  } else {
    spell(num);
  }
  printf("\n");
  return 0;
}