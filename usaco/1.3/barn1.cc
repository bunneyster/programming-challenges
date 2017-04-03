/*
ID: stapark1
LANG: C++11
PROG: barn1
*/
#include <fstream>
#include <vector>
#include <algorithm> // std::sort
#include <iostream>

struct gap {
  int length;
  int last_stall;
  bool operator <(const gap& other) const {
    return length > other.length;
  }
} g;

int main() {
  std::ifstream fin("barn1.in");
  std::ofstream fout("barn1.out");

  int max_boards, total_stalls, total_cows;
  fin >> max_boards >> total_stalls >> total_cows;

  // Return early if enough boards to cover each cow individually.
  if (max_boards >= total_cows) {
    fout << total_cows << std::endl;
    return 0;
  }

  // Collect stall numbers and sort them.
  std::vector<int> stalls;
  int stall;
  for (size_t c = 0; c < total_cows; c++) {
    fin >> stall;
    stalls.push_back(stall);
  }
  std::sort(stalls.begin(), stalls.end());

  // Collect gaps.
  std::vector<gap> gaps;
  int prev_stall = 1;
  for (auto stall : stalls) {
    g = { stall - prev_stall - 1, stall };
    gaps.push_back(g);
    prev_stall = stall;
  }

  // Start by covering all stalls with one large board.
  int covered_length = gaps.back().last_stall - gaps.front().last_stall + 1;

  // std::cout << "Original length: " << covered_length << std::endl;
  // for (auto g : gaps) {
  //   std::cout << "[" << g.length << ", " << g.last_stall << "]" << std::endl;
  // }
  // std::cout << std::endl;

  // Sort gaps from largest to smallest.
  std::sort(gaps.begin(), gaps.end());

  // for (auto g : gaps) {
  //   std::cout << "[" << g.length << ", " << g.last_stall << "]" << std::endl;
  // }

  for (size_t b = 0; (b < max_boards - 1) && (b < gaps.size() - 1); b++) {
    covered_length -= gaps.at(b).length;
    // std::cout << "New length: " << covered_length << std::endl;
  }

  fout << covered_length << std::endl;
  return 0;
}
