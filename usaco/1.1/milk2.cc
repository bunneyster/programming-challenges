/*
ID: stapark1
LANG: C++11
PROG: milk2
*/
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

struct punchcard {
  int time;
  int bound;  // +1 for starting, -1 for ending
} start_card, end_card;

int main() {
  std::ifstream fin("milk2.in");
  std::ofstream fout("milk2.out");

  int n;
  fin >> n;

  // Read and store punchcards into schedule.
  std::vector<punchcard> schedule;
  int start, end;
  for (int i = 0; i < n; ++i) {
    fin >> start >> end;
    start_card = { start, 1 };
    end_card = { end, -1 };
    schedule.push_back(start_card);
    schedule.push_back(end_card);
  }

  // Sort punchcards.
  struct {
    bool operator()(punchcard a, punchcard b) {
      if (a.time == b.time) {
        return b.bound < a.bound;
      }
      return a.time < b.time;
    }
  } card_sort;
  std::sort(schedule.begin(), schedule.end(), card_sort);

  // for (auto card : schedule) {
  //   std::cout << card.time << ", " << card.bound << std::endl;
  // }

  // Calculate milking times.
  int cow_counter = 1;
  int milk_start = schedule.at(0).time;
  int max_milk = 0;
  int max_idle = 0;
  int i = 1;
  while (i < schedule.size()) {
    // std::cout << "Card: " << schedule.at(i).time << ", " << schedule.at(i).bound << std::endl;
    cow_counter += schedule.at(i).bound;
    // std::cout << "Cow counter: " << cow_counter << std::endl;
    if (cow_counter == 0) {
      if (schedule.at(i).time - milk_start > max_milk) {
        max_milk = schedule.at(i).time - milk_start;
        // std::cout << "New max milk: " << max_milk << std::endl;
      }
      if (i < schedule.size() - 1) {
        if (schedule.at(i + 1).time - schedule.at(i).time > max_idle) {
          max_idle = schedule.at(i + 1).time - schedule.at(i).time;
          // std::cout << "New max idle: " << max_idle << std::endl;
        }
        milk_start = schedule.at(i + 1).time;
      }
    }
    i++;

    // std::cout << "Max milk: " << max_milk << std::endl;
    // std::cout << "Max idle: " << max_idle << std::endl;
  }

  fout << max_milk << " " << max_idle << std::endl;

  return 0;
}
