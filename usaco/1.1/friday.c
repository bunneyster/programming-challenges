/*
ID: stapark1
LANG: C
PROG: friday
*/
#include <stdio.h>

int n;  // The number of years since 1900 (0, 400).
int counts[7];  // The occurrences of Friday 13th for each day of the week.

// Return 0 if the element is included in the array, and 1 otherwise.
int is_included_in(int *array, int array_size, int element) {
  for (int i = 0; i < array_size; ++i) {
    if (array[i] == element)
      return 0;
  }
  return 1;
}

// Return 0 if the year is a leap year, and 1 otherwise.
int is_leap_year(int year) {
  if (year % 400 == 0)
    return 1;
  return year % 4 == 0;
}

/*
  E.g. For January, 1901: days_this_month(1, 1);
*/
int days_this_month(int month, int year) {
  int thirty_day_months[4] = {4, 6, 9, 11};
  int result;
  if (is_included_in(thirty_day_months, month) == 0) {
    result = 30;
  } else if (month == 2) {
    if (is_leap_year(year) == 0) {
      result = 29;
    } else {
      result = 28;
    }
  } else {
    result = 31;
  }
  return result;
}

int main() {
  FILE *fin  = fopen("friday.in", "r");
  FILE *fout = fopen("friday.out", "w");

  fscanf(fin, "%d", &n);
  for (int i = 0; i < 12; ++i) {
    printf("%d\n", days_this_month(i + 1, 1900));
  }


  return 0;
}
