/*
ID: stapark1
LANG: C++11
PROG: transform
*/
#include <fstream>
#include <iostream>

void print(int n, char square[10][10]) {
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      std::cout << square[i][j];
    }
    std::cout << std::endl;
  }
}

// 90 degree rotation
void t1(int n, char in[10][10], char out[10][10]) {
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      out[j][n - i - 1] = in[i][j];
    }
  }
}

// // 180 degree rotation
// void t2(int n, char in[10][10], char out[10][10]) {
//   for (size_t i = 0; i < n; i++) {
//     for (size_t j = 0; j < n; j++) {
//       out[n - i - 1][j] = in[i][j];
//     }
//   }
// }
//
// // 270 degree rotation
// void t3(int n, char in[10][10], char out[10][10]) {
//   for (size_t i = 0; i < n; i++) {
//     for (size_t j = 0; j < n; j++) {
//       out[n - j - 1][i] = in[i][j];
//     }
//   }
// }

// horizontal reflection
void t4(int n, char in[10][10], char out[10][10]) {
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      out[i][n - j - 1] = in[i][j];
    }
  }
}

std::string equals;
bool matches(int n, char a[10][10], char b[10][10]) {
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {

      equals = (a[i][j] != b[i][j]) ? " != " : " == ";
      std::cout << "[" << i << "][" << j << "]: " << a[i][j] << equals << b[i][j] << std::endl;
      if (a[i][j] != b[i][j]) { return false; }
    }
  }
  return true;
}

void duplicate(char origin[10][10], char copy[10][10]) {
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      copy[i][j] = origin[i][j];
    }
  }
}

char rotated[10][10], dup[10][10];
int rotation_count(int n, int rotations, char in[10][10], char out[10][10]) {
  t1(n, in, rotated);
  print(n, rotated);
  if (matches(n, rotated, out)) {
    return rotations;
  } else {
    if (rotations == 3) { return -1; }
    duplicate(rotated, dup);
    return rotation_count(n, ++rotations, dup, out);
  }
}

char temp[10][10];
int combo(int n, char in[10][10], char out[10][10]) {
  // #1-3
  int num_rotations = rotation_count(n, 1, in, out);
  if (num_rotations > 0) { return num_rotations; }

  // #4
  t4(n, in, temp);
  if (matches(n, temp, out)) { return 4; }

  // #5
  int num_rotations_2 = rotation_count(n, 1, temp, out);
  if (num_rotations_2 > 0) { return 5; }

  // #6
  if (num_rotations == 0) { return 6; }

  // #7
  return 7;
}

int main() {
  std::ifstream fin("transform.in");
  std::ofstream fout("transform.out");

  int n;
  fin >> n;

  char input[10][10], output[10][10];
  std::string row;
  for (size_t i = 0; i < n; i++) {
    fin >> row;
    for (size_t j = 0; j < n; j++) {
      input[i][j] = row[j];
    }
  }
  for (size_t i = 0; i < n; i++) {
    fin >> row;
    for (size_t j = 0; j < n; j++) {
      output[i][j] = row[j];
    }
  }
  fout << combo(n, input, output) << std::endl;
  return 0;
}
