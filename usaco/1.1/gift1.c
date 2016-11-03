/*
ID: stapark1
LANG: C
PROG: gift1
*/
#include <stdio.h>
#include <string.h>

#define MAX_FRIEND_COUNT 10
#define MAX_NAME_LENGTH 14

int num_friends;
char names[MAX_FRIEND_COUNT][MAX_NAME_LENGTH + 1];
int balances[MAX_FRIEND_COUNT];

/* The nanes and current balancea of each friend. */
struct profile {
  char name[MAX_NAME_LENGTH + 1];
  int balance;
} profiles[MAX_FRIEND_COUNT];

void update_profile(char name[MAX_NAME_LENGTH + 1], int transaction) {
  int i = 0;
  while (strcmp(profiles[i].name, name) != 0) { ++i; }
  profiles[i].balance += transaction;
}

int main() {
  FILE *fin  = fopen("gift1.in", "r");
  FILE *fout = fopen("gift1.out", "w");

  fscanf(fin, "%d", &num_friends);
  for (int i = 0; i < num_friends; ++i) {
    fscanf(fin, "%s", profiles[i].name);
    profiles[i].balance = 0;
  }

  char gifter[MAX_NAME_LENGTH], recipient[MAX_NAME_LENGTH];
  int amount, num_recipients;
  while (fscanf(fin, "%s", gifter) == 1) {
    fscanf(fin, "%d %d", &amount, &num_recipients);
    if (num_recipients == 0)
      continue;
    update_profile(gifter, (amount / num_recipients) * num_recipients * -1);
    for (int i = 0; i < num_recipients; ++i) {
      fscanf(fin, "%s", recipient);
      update_profile(recipient, amount / num_recipients);
    }
  }

  for (int i = 0; i < num_friends; ++i) {
    fprintf(fout, "%s %d\n", profiles[i].name, profiles[i].balance);
  }
  return 0;
}
