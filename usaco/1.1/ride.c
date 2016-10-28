/*
ID: stapark1
LANG: C
PROG: ride
*/
#include <stdio.h>

#define MAX_NAME_LENGTH 6
#define MOD 47

char comet[MAX_NAME_LENGTH + 1];
char group[MAX_NAME_LENGTH + 1];

int letter_to_number(char letter) {
  return letter - 'A' + 1;
}

int parse(char name[6]) {
  int result = 1;
  for (int i = 0; (i < MAX_NAME_LENGTH) && (name[i] != '\0'); ++i) {
    result = result * letter_to_number(name[i]);
  }
  return result % MOD;
}

int main() {
  FILE *fin  = fopen("ride.in", "r");
  FILE *fout = fopen("ride.out", "w");
  fscanf(fin, "%s\n%s", comet, group);
  fprintf(fout, "%s\n", (parse(comet) == parse(group)) ? "GO" : "STAY");
  return 0;
}
