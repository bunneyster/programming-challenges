/*
ID: stapark1
LANG: C++11
PROG: dualpal
*/
#include <fstream>
#include <vector>
#include <iostream>

// Get base-converted digits in reverse order in output.
void _b(int input, int base, std::vector<int>& output) {
  for (; input / base > 0; input /= base) {
    output.push_back(input % base);
  }
  output.push_back(input % base);
}

bool is_pal(std::vector<int>& thing) {
  for (size_t i = 0; i < thing.size() / 2; i++) {
    if (thing.at(i) != thing.at(thing.size() - i - 1)) {
      return false;
    }
  }
  return true;
}

bool has_2_palindromes(int input) {
  int palindrome_count = 0;
  std::vector<int> converted;
  for (int base = 2; base <= 10; base++) {
    _b(input, base, converted);
    if (is_pal(converted)) { palindrome_count++; }
    if (palindrome_count == 2) { return true; }
    converted.clear();
  }
  return false;
}

int main() {
  std::ifstream fin("dualpal.in");
  std::ofstream fout("dualpal.out");

  int n, s;
  fin >> n >> s;

  int s_i = s + 1;
  for (size_t n_i = 0; n_i < n; s_i++) {
    if (has_2_palindromes(s_i)) {
      n_i++;
      fout << s_i << std::endl;
    }
  }
  return 0;
}
