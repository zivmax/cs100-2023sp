#include <stdio.h>

void print_num(int x) {
  switch (x) {
    case 0:
      printf("zero");
      break;
    case 1:
      printf("one");
      break;
    case 2:
      printf("two");
      break;
    case 3:
      printf("three");
      break;
    case 4:
      printf("four");
      break;
    case 5:
      printf("five");
      break;
    case 6:
      printf("six");
      break;
    case 7:
      printf("seven");
      break;
    case 8:
      printf("eight");
      break;
    case 9:
      printf("nine");
      break;
  }
}

// print words that above 10 (including 1~9*10 and 10+1~9)
void print_ten(int x) {
  switch (x) {
    case 6:
    case 7:
    case 8:
    case 9:
      print_num(x);
      printf(x == 8 ? "y" : "ty");
      break;
    case 10:
      printf("ten");
      break;
    case 2:
      printf("twenty");
      break;
    case 3:
      printf("thirty");
      break;
    case 4:
      printf("forty");
      break;
    case 5:
      printf("fifty");
      break;
    case 11:
      printf("eleven");
      break;
    case 12:
      printf("twelve");
      break;
    case 13:
      printf("thirteen");
      break;
    case 15:
      printf("fifteen");
      break;
    case 14:
    case 16:
    case 17:
    case 18:
    case 19:
      print_num(x - 10);
      if (x != 18)
        putchar('t');
      printf("een");
  }
}

void print_hundred(int x) {
  if (x >= 100) {
    print_num(x / 100);
    printf(" hundred");
    x %= 100;
    if (x) {
      printf(" and ");
    } else {
      return;
    }
  }
  if (x >= 20) {
    print_ten(x / 10);
    x %= 10;
    if (x)
      putchar('-');
    else
      return;
  }
  if (x >= 10) {
    print_ten(x);
  } else {
    print_num(x);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  if (n == 0) {
    printf("zero\n");
    return 0;
  }
  int thou = n / 1000;
  if (n >= 1000) {
    print_hundred(thou);
    printf(" thousand");
    n %= 1000;
    if (n) {
      putchar(' ');
    } else {
      printf("\n");
      return 0;
    }
  }
  if (n < 100)
    printf("and ");
  print_hundred(n);
  printf("\n");
  return 0;
}
