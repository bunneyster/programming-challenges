/*
ID: stapark1
LANG: C++11
PROG: gift1
*/
#include <fstream>
#include <vector>
#include <unordered_map>

int main() {
  std::ofstream fout("gift1.out");
  std::ifstream fin("gift1.in");

  std::string current_line;

  int total_friends;
  fin >> total_friends;

  std::vector<std::string> names;
  for (int i = 0; i < total_friends; ++i) {
    fin >> current_line;
    names.push_back(current_line);
  }

  std::unordered_map<std::string, int> balances;
  std::string donor;
  int gift_total, recipient_count, gift_amount;
  for (int i = 0; i < total_friends; ++i) {
    fin >> donor >> gift_total >> recipient_count;

    if (recipient_count == 0) { continue; }
    gift_amount = gift_total / recipient_count;
    balances[donor] -= gift_amount * recipient_count;
    for (int j = 0; j < recipient_count; ++j) {
      fin >> current_line;
      balances[current_line] += gift_amount;
    }
  }

  for (const auto& n : names) {
    fout << n << ' ' << balances[n] << std::endl;
  }
  return 0;
}
