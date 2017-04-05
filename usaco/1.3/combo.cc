/*
ID: stapark1
LANG: C++11
PROG: combo
*/
#include <fstream>
#include <vector>
#include <array>
#include <unordered_set>
#include <sstream>
#include <iostream>

typedef std::array<int, 3> combo;

namespace std {
  template <> struct hash<combo> {
    size_t operator()(const combo& c) const {
      return hash<int>()((c[0] * 10000) + (c[1] * 10) + c[2]);
    }
  };
}

int main() {
  std::ifstream fin("combo.in");
  std::ofstream fout("combo.out");

  int n;
  fin >> n;

  // Read in farmer and master combos.
  std::vector<combo> official_combos;
  combo c;
  int pos;
  for (size_t j = 0; j < 2; ++j) {
    for (size_t i = 0; i < 3; i++) {
      fin >> pos;
      c[i] = pos - 1;
    }
    official_combos.push_back(c);
  }

  // Calculate and store potential dial positions.
  std::unordered_set<combo> combos;
  for (auto oc : official_combos) {
    for (int i = -2; i < 3; i++) {
      for (int j = -2; j < 3; j++) {
        for (int k = -2; k < 3; k++) {
          c[0] = (n + oc[0] + i) % n;
          c[1] = (n + oc[1] + j) % n;
          c[2] = (n + oc[2] + k) % n;
          // std::cout << "[ " << oc[0] << ", " << oc[1] << ", " << oc[2] << " ]" << std::endl;
          // std::cout << "  -> [ " << c[0] << ", " << c[1] << ", " << c[2] << " ]" << std::endl;
          combos.insert(c);
        }
      }
    }
  }

  // for (auto c : combos) {
  //   std::cout << "[ " << c[0] << ", " << c[1] << ", " << c[2] << " ]" << std::endl;
  // }

  fout << combos.size() << std::endl;

  return 0;
}
