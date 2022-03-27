// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

static int N_jogada = 0;
static position_t anterior_position;
static direction_t anterior_play;

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t define_defender_play(int value, direction_t forbidden_play) {
  if (value <= 4 && forbidden_play.i != -1 && forbidden_play.j != 0){
    return (direction_t) DIR_UP;
  }
  else if (forbidden_play.i != 1 && forbidden_play.j != 0){
    return (direction_t) DIR_DOWN;
  }
  else {
    return (direction_t) DIR_UP;
  }
}

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {
  // TODO: unused parameters, remove these lines later
  UNUSED(defender_position);

  direction_t current_play = DIR_LEFT;

  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);

  /* using nano-seconds instead of seconds */
  srand((time_t)ts.tv_nsec);

  int sorted_value =  rand()%10;

  if (N_jogada == 0) {
    // if it's the first play
    N_jogada += 1;
    return (direction_t) DIR_LEFT;
  }
  else {
    if (defender_position.i != defender_position.i || defender_position.j != defender_position.j) {
      // if I didn't hit a barrier (if I changed my position in relation to the previous move)
      current_play = define_defender_play(sorted_value, (direction_t)  DIR_RIGHT);
    }
    else {
      // if I hit a barrier, I don´t want to do the same move as the previous player
      current_play = define_defender_play(sorted_value, (direction_t)  anterior_play);
    }
  }

  if (N_jogada == 4) {
    Spy attacker_position = attacker_spy;
  }

  anterior_position = defender_position;

  anterior_play = current_play;

  N_jogada += 1;

  return (direction_t) current_play;
}

/*----------------------------------------------------------------------------*/
