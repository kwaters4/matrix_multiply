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

double get_cpu_counter() {
    uint64_t c1;
    c1 = rdtsc();
    return c1;
}

void timer_start(struct timer* t, double work_done){
  t->active = 1;
  t->start_cycles = get_cpu_counter();
  t->work_done = work_done;
  clock_gettime(CLOCK_MONOTONIC, &t->start);
  //t->start = (double) clock() / CLOCKS_PER_SEC;
}

void timer_stop(struct timer* t){
  clock_gettime(CLOCK_MONOTONIC, &t->end);
//  t->end = (double) clock() / CLOCKS_PER_SEC;
  t->end_cycles = get_cpu_counter();
  t->elapsed =
        (t->end.tv_sec - t->start.tv_sec) +
        (t->end.tv_nsec - t->start.tv_nsec) * 1e-9;
  t->active = 0;
}

double timer_elapsed(struct timer* t){
  if (t->active == 1){
    printf("WARNING: Timer was not stopped, now it is\n");
    timer_stop(t);
  }
  return(t->elapsed);
}

void timer_print(struct timer *t){
  printf("active       : %d\n", t->active);
  printf("work_done    : %f\n", t->work_done);
  printf("start        : %lld.%.9ld\n", (long long)t->start.tv_sec, t->start.tv_nsec);
  printf("end          : %lld.%.9ld\n", (long long)t->end.tv_sec, t->end.tv_nsec);
  printf("cycles (#)   : %ld\n", t->end_cycles - t->start_cycles);
  printf("elapsed (s)  : %f\n", t->elapsed);
};

double timer_calc_work_per_cycle(struct timer* t){
  if (t->active == 1){
    printf("WARNING: Timer was not stopped, now it is\n");
    timer_stop(t);
  }
  return (t->work_done / (t->end_cycles - t->start_cycles));
}



