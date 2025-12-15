#include <timer.h>

int main(){

  struct timer a;
  timer_start(&a, 1E9);
  sleep(1);
  timer_stop(&a);
  double work_per_clock = timer_calc_work_per_cycle(&a);
  if (work_per_clock <= 0.0){
    printf("ERROR: Something went wrong, negative work/clock calculated");
    return -1;
  }
  return 0;

}
