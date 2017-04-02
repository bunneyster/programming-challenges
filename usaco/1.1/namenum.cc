/*
ID: stapark1
LANG: C++11
PROG: namenum
*/
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

std::unordered_map<int, std::string> keymap = {
  { '2', "ABC" },
  { '3', "DEF" },
  { '4', "GHI" },
  { '5', "JKL" },
  { '6', "MNO" },
  { '7', "PRS" },
  { '8', "TUV" },
  { '9', "WXY" }
};

// 5 -> 21000 = 12
void to_base_3(int n, int dec, std::vector<int>& memo) {
  while (dec / 3 > 0) {
    memo.push_back(dec % 3);
    dec = dec / 3;
  }
  memo.push_back(dec % 3);

  int fillers = n - memo.size();
  for (size_t i = 0; i < fillers; i++) {
    memo.push_back(0);
  }
}

int max_in_decimal(int n) {
  int result = 0;
  for (size_t i = 0; i < n; i++) {
    result += 2 * pow(3, i);
  }
  return result;
}

int main() {
  std::ifstream dict("dict.txt");
  std::ifstream fin("namenum.in");
  std::ofstream fout("namenum.out");

  std::string serial;
  fin >> serial;

  // Read and store valid names.
  std::unordered_set<std::string> valid_names;
  std::string name;
  while (std::getline(dict, name)) {
    valid_names.insert(name);
  }

  std::vector<std::string> results;
  std::vector<int> alpha_indices;
  for (size_t i = 0; i < max_in_decimal(serial.size()); i++) {  // For each index combo
    // std::cout << "Combo:" << i << std::endl;
    to_base_3(serial.size(), i, alpha_indices);
    name = "";
    for (size_t j = 0; j < serial.size(); j++) {
      name += keymap[serial[j]][alpha_indices.at(serial.size() - j - 1)];
    }
    alpha_indices.clear();
    // std::cout << "Name: " << name << std::endl;
    if (valid_names.find(name) != valid_names.end()) {
      results.push_back(name);
    }
  }

  std::sort(results.begin(), results.end());
  if (results.empty()) {
    fout << "NONE" << std::endl;
  } else {
    for (auto name : results) {
      fout << name << std::endl;
    }
  }

  return 0;
}
