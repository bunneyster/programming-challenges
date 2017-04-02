/*
ID: stapark1
LANG: C++11
PROG: namenum
*/
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>

std::unordered_map<int, std::string> keymap = {
  { 2, "ABC" },
  { 3, "DEF" },
  { 4, "GHI" },
  { 5, "JKL" },
  { 6, "MNO" },
  { 7, "PRS" },
  { 8, "TUV" },
  { 9, "WXY" }
};

int main() {
  std::ifstream dict("dict.txt");
  std::ifstream fin("namenum.in");
  std::ofstream fout("namenum.out");

  std::string serial;
  fin >> serial;

  std::unordered_set<std::string> valid_names;
  std::string name;
  while (std::getline(dict, name)) {
    valid_names.insert(name);
  }

  std::vector<std::string> stubs;
  std::vector<std::string> queue;
  std::string stub;
  stubs.push_back("");
  for (auto n : serial) {  // For each integer
    // for (auto stub : stubs) {  // For each stub in q1
    //   for (auto c : keymap[n - '0']) {  // For each mapped character
    //     queue.push_back(stub + c);
    //   }
    // }

    while (!stubs.empty()) {
      stub = stubs.back();
      stubs.pop_back();
      for (auto c : keymap[n - '0']) {  // For each mapped character
        queue.push_back(stub + c);
      }
    }

    stubs.swap(queue);
    queue.clear();
    // for (auto s : stubs) {
    //   std::cout << s << std::endl;
    // }
  }

  std::sort(stubs.begin(), stubs.end());

  std::vector<std::string> results;
  for (auto name : stubs) {
    if (valid_names.find(name) != valid_names.end()) {
      results.push_back(name);
    }
  }
  if (results.empty()) {
    fout << "NONE" << std::endl;
  } else {
    for (auto name : results) {
      fout << name << std::endl;
    }
  }

  return 0;
}
