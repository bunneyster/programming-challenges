/*
ID: stapark1
LANG: C++11
PROG: crypt1
*/
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cmath>  // std::pow
#include <iostream>

bool has_valid_digits(int max_digits, int number, const std::unordered_set<int>& valid_digits) {
  int upper_bound = std::pow(10, max_digits);
  if (number / upper_bound > 0) { return false; }

  int digit;
  for (size_t i = 1; i < upper_bound; i *= 10) {
    digit = (number / i) % 10;
    if (valid_digits.find(digit) == valid_digits.end()) { return false; }
  }
  return true;
}

int main() {
  std::ifstream fin("crypt1.in");
  std::ofstream fout("crypt1.out");

  int n, d;
  fin >> n;
  std::unordered_set<int> digits;
  for (size_t i = 0; i < n; i++) {
    fin >> d;
    digits.insert(d);
  }

  std::unordered_map<int, std::vector<int>> partials;
  int multiplicand, multiplier, product;
  for (auto i : digits) {
    for (auto j : digits) {
      for (auto k : digits) {
        multiplicand = (100 * i) + (10 * j) + k;
        // std::cout << "Multiplicand: " << multiplicand << std::endl;
        for (auto d : digits) {
          product = multiplicand * d;
          // std::cout << "Testing product: " << product << std::endl;
          if (has_valid_digits(3, product, digits)) {
            // std::cout << "Valid multiplier: " << d << std::endl;
            partials[multiplicand].push_back(product);
            // partial_products.insert(product);
          }
        }
      }
    }
  }

  int count = 0;
  for (auto partial : partials) {
    for (auto p1 : partial.second) {
      for (auto p2 : partial.second) {
        if (has_valid_digits(4, p1 + (10 * p2), digits)) {
          // std::cout << partial.first << " --> " << p1 + (10 * p2) << std::endl;
          count++;
        }
      }
    }
  }

  fout << count << std::endl;

  return 0;
}
