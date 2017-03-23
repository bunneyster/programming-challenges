/*
ID: stapark1
PROG: ride
LANG: C++11
*/
#include <fstream>
#include <string>

int score(const std::string& name) {
  int result = 1;
  for (auto c : name) {
    result = result * (c - 'A' + 1);
  }
  return result % 47;
}

int main() {
  std::ofstream fout("ride.out");
  std::ifstream fin("ride.in");

  std::string comet;
  std::string group;

  fin >> comet >> group;
  fout << (score(comet) == score(group) ? "GO" : "STAY") << std::endl;
  return 0;
}
