#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <timer.h>

static inline uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

double calc_freq() {
    struct timespec start, end;
    uint64_t c1, c2;

    clock_gettime(CLOCK_MONOTONIC, &start);
    c1 = rdtsc();
    sleep(1);
    c2 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) +
        (end.tv_nsec - start.tv_nsec) * 1e-9;

    double freq = (c2 - c1) / elapsed;
    return freq;
}

void timer_start(struct timer* t, double work_done){
  t->active = 1;
  t->freq = calc_freq();
  t->work_done = work_done;
  t->start = (double) clock() / CLOCKS_PER_SEC;
}

void timer_stop(struct timer* t){
  t->end = (double) clock() / CLOCKS_PER_SEC;
  t->elapsed = t->end - t->start;
  t->active = 0;
}

void timer_reset(struct timer* t){
  t->active = 0;
  t->work_done = 0;
  t->start = 0;
  t->end = 0;
  t->elapsed = 0;
}

double timer_elapsed(struct timer* t){
  if (t->active == 1){
    printf("WARNING: Timer was not stopped, now it is\n");
    timer_stop(t);
  }
  return(t->elapsed);
}

void timer_print(struct timer *t){
  printf("active     : %d\n", t->active);
  printf("work_done  : %f \n", t->work_done);
  printf("start      : %f \n", t->start);
  printf("end        : %f \n", t->end);
  printf("elapsed (s): %f \n", t->elapsed);
  printf("freq (Hz)  : %f \n", t->freq);
};

double timer_calc_ipc(struct timer* t){
  if (t->active == 1){
    printf("WARNING: Timer was not stopped, now it is\n");
    timer_stop(t);
  }
  return (t->work_done / (t->freq * t->elapsed));
}



