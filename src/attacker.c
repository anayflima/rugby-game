// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

static int N_jogada = 0;

static position_t anterior_position;
static direction_t anterior_play;

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t define_attacker_play(int value, direction_t forbidden_play) {
  if (value <= 2 && forbidden_play.i != 0 && forbidden_play.j != 1) {
    return (direction_t) DIR_RIGHT;
  }
  else if (value <= 4 && forbidden_play.i != -1 && forbidden_play.j != 1) {
    return (direction_t) DIR_UP_RIGHT;
  }
  else if (value <= 6 && forbidden_play.i != 1 && forbidden_play.j != 1) {
    return (direction_t) DIR_DOWN_RIGHT;
  }
  else if (value <= 8 && forbidden_play.i != 1 && forbidden_play.j != 0) {
    return (direction_t) DIR_DOWN;
  }
  else if (forbidden_play.i != -1 && forbidden_play.j != 0){
    return (direction_t) DIR_UP;
  }
  else {
    return (direction_t) DIR_RIGHT;
  }
}


direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {
  // TODO: unused parameters, remove these lines later
  UNUSED(defender_spy);

  direction_t current_play = DIR_RIGHT;

  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);

  /* using nano-seconds instead of seconds */
  srand((time_t)ts.tv_nsec);

  int sorted_value =  rand()%10;

  if (attacker_position.i != anterior_position.i || attacker_position.j != anterior_position.j) {
    // if I didn't hit a barrier (if I changed my position in relation to the previous move)
    current_play = define_attacker_play(sorted_value, (direction_t)  DIR_LEFT);
  }
  else {
    // if I hit a barrier, I don´t want to do the same move as the previous player
    current_play = define_attacker_play(sorted_value, (direction_t)  anterior_play);
  }

  // if (N_jogada == 4) {
  //   Spy defender_position = defender_spy;
  // }


  anterior_position = attacker_position;

  anterior_play = current_play;


  return (direction_t) current_play;
}

/*----------------------------------------------------------------------------*/
