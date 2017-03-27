/*
ID: stapark1
LANG: C++11
PROG: friday
*/
#include <fstream>
#include <iostream>

int is_leap_year(int year) {
  if (year % 400 == 0) {
    return 1;
  } else if (year % 100 == 0) {
    return 0;
  } else {
    return year % 4 == 0;
  }
}

const int offsets[] = { 3, 0, 3, 2, 3, 2, 3, 3, 2, 3, 2, 3 };
int offset(int year, int month) {
  int result = offsets[month];
  if (is_leap_year(year) && (month == 1)) { result += 1; }
  return result;
}

int main() {
  std::ofstream fout("friday.out");
  std::ifstream fin("friday.in");

  int frequencies[7] = {0};
  int num_years;
  fin >> num_years;

  int current_day = 0;  // Saturday
  for (int y = 0; y < num_years; ++y) {
    for (int m = 0; m < 12; ++m) {
      frequencies[current_day]++;
      current_day = (current_day + offset(1900 + y, m)) % 7;
    }
  }

  for (int d = 0; d < 7; ++d) {
    fout << frequencies[d];
    if (d < 6) {
      fout << ' ';
    } else {
      fout << std::endl;
    }
  }
  return 0;
}
