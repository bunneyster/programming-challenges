/*
ID: stapark1
LANG: C++11
PROG: palsquare
*/
#include <fstream>
#include <vector>
#include <cmath>  // For std::pow
#include <algorithm> // For std::reverse
#include <iostream>

char base_char(int num) {
  if (num < 10) {
    return '0' + num;
  } else {
    return 'A' + (num - 10);
  }
}

void _b(int input, int base, std::string& output) {
  for (; input / base > 0; input /= base) {
    output += base_char(input % base);
  }
  output += base_char(input % base);

  std::reverse(output.begin(), output.end());
}

bool is_pal(std::string& thing) {
  for (size_t i = 0; i < thing.size(); i++) {
    if (thing.at(i) != thing.at(thing.size() - i - 1))
      return false;
  }
  return true;
}

struct palsquare {
  std::string origin;
  std::string square;
};

int main() {
  std::ifstream fin("palsquare.in");
  std::ofstream fout("palsquare.out");

  int base;
  fin >> base;

  std::vector<palsquare> results;
  std::string i_b;
  std::string square_b;
  for (size_t i = 1; i < 301; i++) {
     _b(std::pow(i, 2), base, square_b);
     if (is_pal(square_b)) {
       _b(i, base, i_b);
       palsquare ps = { i_b, square_b };
       results.push_back(ps);
     }
     i_b.clear();
     square_b.clear();
  }

  for (auto r : results) {
    fout << r.origin << " " << r.square << std::endl;
  }

  return 0;
}
