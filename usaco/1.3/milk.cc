/*
ID: stapark1
LANG: C++11
PROG: milk
*/
#include <fstream>
#include <algorithm>  // std::sort
#include <vector>
#include <iostream>

struct inventory {
  int price;
  int quantity;
  bool operator <(const inventory& other) const {
    return price < other.price;
  }
} inv;

int main() {
  std::ifstream fin("milk.in");
  std::ofstream fout("milk.out");

  int total_milk, total_farmers;
  fin >> total_milk >> total_farmers;

  // Collect farmer inventories.
  std::vector<inventory> inventories;
  int price, quantity;
  for (size_t i = 0; i < total_farmers; i++) {
    fin >> price >> quantity;
    inv = { price, quantity };
    inventories.push_back(inv);
  }

  // Sort inventories from cheapest to priciest.
  std::sort(inventories.begin(), inventories.end());

  int cost = 0;
  int remaining = total_milk;
  for (auto i : inventories) {
    if (remaining - i.quantity > 0) {
      cost += i.price * i.quantity;
      remaining -= i.quantity;
    } else {
      cost += i.price * remaining;
      fout << cost << std::endl;
      return 0;
    }
  }
  fout << 0 << std::endl;
  return 0;
}
