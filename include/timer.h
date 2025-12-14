#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

struct timer {
  int active;
  double work_done;
  // Time stored as seconds
  //
  struct timespec start;
  struct timespec end;
  size_t start_cycles;
  size_t end_cycles;
  double elapsed;
  // Freq stored as Hz
  double freq;
};

void timer_start(struct timer* t, double work_done);
void timer_stop(struct timer* t);
void timer_print(struct timer* t);
double timer_elapsed(struct timer* t);
double timer_calc_ipc(struct timer* t);
