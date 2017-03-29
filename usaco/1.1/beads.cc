/*
ID: stapark1
LANG: C++11
PROG: beads
*/
#include <fstream>
#include <vector>
#include <iostream>

struct bucket {
  char color;
  int length;
};

int main() {
  std::ifstream fin("beads.in");
  std::ofstream fout("beads.out");

  int bead_count;
  std::string necklace;
  fin >> bead_count >> necklace;

  // Populate lengths and colors vectors.
  std::vector<bucket> buckets;
  int current_bucket = -1;
  char prev_color = 'x';
  for (auto b : necklace) {
    if (prev_color != b) {
      current_bucket++;
      bucket next_bucket = { b, 1 };
      buckets.push_back(next_bucket);
    } else {
      buckets[current_bucket].length++;
    }
    prev_color = b;
  }

  // Return early if 3 or fewer buckets.
  if (buckets.size() < 4) {
    fout << necklace.size() << std::endl;
    return 0;
  }

  // Connect ends of necklace.
  if (buckets.back().color == buckets.front().color) {
    buckets.front().length += buckets.back().length;
    buckets.pop_back();
  }

  // Return early if 3 or fewer buckets.
  if (buckets.size() < 4) {
    fout << necklace.size() << std::endl;
    return 0;
  }

  // Aggregate sandwiches.
  prev_color = 'x';
  int i = 0;
  while (i < buckets.size()) {
    // Return early if 3 or fewer buckets.
    if (buckets.size() < 4) {
      fout << necklace.size() << std::endl;
      return 0;
    }

    bucket current_bucket = buckets.at(i);
    if (current_bucket.color == 'w') {
      int prev_i = (i - 1 + buckets.size()) % buckets.size();
      int next_i = (i + 1) % buckets.size();
      bucket prev_bucket = buckets.at(prev_i);
      bucket next_bucket = buckets.at(next_i);
      if (prev_bucket.color == next_bucket.color) {
        buckets.at(prev_i).length += (current_bucket.length + next_bucket.length);
        if (next_i > i) {
          buckets.erase(buckets.begin() + next_i);
          buckets.erase(buckets.begin() + i);
        } else {
          buckets.erase(buckets.begin() + i);
          buckets.erase(buckets.begin() + next_i);
        }
      } else {
        i = i + 2;
      }
    } else {
      i++;
    }
  }

  int max_length = 0;
  int length = 0;
  char left, current;
  for (int i = 0; i < buckets.size(); ++i) {
    int prev_i = (i - 1 + buckets.size()) % buckets.size();
    bucket current_bucket = buckets.at(i % buckets.size());
    length = 0;
    left = buckets.at(prev_i).color;
    current = current_bucket.color;
    if (current_bucket.color == 'w') {
      for (int l = prev_i; ((buckets.at(l).color == 'w') || (buckets.at(l).color == left)) && (l != i); l = (l - 1 + buckets.size()) % buckets.size()) {
        length += buckets.at(l).length;
      }
      for (int r = i; ((buckets.at(r).color == 'w') || (buckets.at(r).color != left)) && (r != prev_i); r = (r + 1 + buckets.size()) % buckets.size()) {
        length += buckets.at(r).length;
      }
    } else {
      for (int l = prev_i; ((buckets.at(l).color == 'w') || (buckets.at(l).color != current)) && (l != i); l = (l - 1 + buckets.size()) % buckets.size()) {
        length += buckets.at(l).length;
      }
      for (int r = i; ((buckets.at(r).color == 'w') || (buckets.at(r).color == current)) && (r != prev_i); r = (r + 1 + buckets.size()) % buckets.size()) {
        length += buckets.at(r).length;
      }
    }
    if (length > max_length) { max_length = length; }
  }

  fout << max_length << std::endl;
  return 0;
}
