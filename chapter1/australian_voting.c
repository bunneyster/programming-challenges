#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATE_COUNT    20
#define MAX_NAME_LENGTH        80
#define MAX_BALLOT_COUNT       1000
#define MAX_BALLOT_CHAR_LENGTH 5 * MAX_CANDIDATE_COUNT

int num_candidates, num_ballots;
int highest_tally;  // highest tally seen so far
int lowest_tally;  // lowest tally seen so far
int tallies[MAX_CANDIDATE_COUNT];  // tallied votes for candidate at index i
int ballots[MAX_BALLOT_COUNT][MAX_CANDIDATE_COUNT];  // the ballots
char candidates[MAX_CANDIDATE_COUNT][MAX_NAME_LENGTH + 1]; // candidate names
size_t name_length;

void reset_tallies()
{
  for (int t = 0; t < num_candidates; ++t) {
    tallies[t] = 0;
  }

  highest_tally = 0;
  lowest_tally = MAX_BALLOT_COUNT * MAX_CANDIDATE_COUNT;
}

void read_candidate_names()
{
  for (int c = 0; c < num_candidates; ++c) {
    fgets(candidates[c], MAX_NAME_LENGTH + 1, stdin);
    name_length = strlen(candidates[c]);
    if (candidates[c][name_length - 1] == '\n')
      candidates[c][name_length - 1] = '\0';
  }
}

void read_ballots()
{
  char *vote;
  char ballot[MAX_BALLOT_CHAR_LENGTH];
  const char space[2] = " ";

  for (num_ballots = 0; num_ballots < MAX_BALLOT_COUNT; ++num_ballots) {
    if ((fgets(ballot, MAX_BALLOT_CHAR_LENGTH, stdin) == NULL) || (*ballot == '\n'))
      break;

    vote = strtok(ballot, space);
    for (int v = 0; (vote != NULL) && (v < num_candidates); ++v) {
      ballots[num_ballots][v] = atoi(vote);
      vote = strtok(NULL, space);
    }
  }
}

/* Tallies the highest-ranked uneliminated vote in the given ballot. */
void tally_ballot(int ballot[MAX_CANDIDATE_COUNT])
{
  int rank = 0;
  while (tallies[ballot[rank] - 1] == -1) { ++rank; }
  tallies[ballot[rank] - 1]++;
}

/* Store the highest and lowest tallies seen so far. */
void calculate_tally_bounds()
{
  lowest_tally = MAX_BALLOT_COUNT * MAX_CANDIDATE_COUNT;
  for (int i = 0; i < num_candidates; ++i) {
    if (tallies[i] == -1)
      continue;
    if (tallies[i] > highest_tally)
      highest_tally = tallies[i];
    if (tallies[i] < lowest_tally)
      lowest_tally = tallies[i];
  }
}

/* Eliminate weakest candidates and recount their votes. */
void calculate_next_round()
{
  int eliminated_candidates[MAX_CANDIDATE_COUNT];  // those eliminated this round
  int eliminated_count = 0;  // # of candidates eliminated so far this round

  for (int c = 0; c < num_candidates; ++c) {
    if (tallies[c] == -1)
      continue;
    if (tallies[c] == lowest_tally) {
      tallies[c] = -1;
      eliminated_candidates[eliminated_count++] = c;
    }
  }

  for (int e = 0; e < eliminated_count; ++e) {
    for (int b = 0; b < num_ballots; ++b) {
      if (ballots[b][0] == eliminated_candidates[e] + 1)
        tally_ballot(ballots[b]);
    }
  }
}

// Identify the highest tally.
void tally_votes()
{
  for (int b = 0; b < num_ballots; ++b) {
    tally_ballot(ballots[b]);
  }
  while ((highest_tally <= num_ballots / 2.0) && (highest_tally != lowest_tally)) {
    calculate_next_round();
    calculate_tally_bounds();
  }
}

int main()
{
  int num_cases;

  scanf("%d\n", &num_cases);
  for (int case_i = 0; case_i < num_cases; ++case_i) {
    if (case_i > 0)
      putchar('\n');

    scanf("%d\n", &num_candidates);
    reset_tallies();
    read_candidate_names();
    read_ballots();
    tally_votes();

    for (int c = 0; c < num_candidates; ++c) {
      if (tallies[c] == highest_tally)
        printf("%s\n", candidates[c]);
    }
  }

  return 0;
}
