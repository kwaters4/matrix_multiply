#include <timer.h>

int main(){

  struct timer a;
  timer_start(&a, 10);
  sleep(1);
  timer_stop(&a);
  double elapsed = timer_elapsed(&a);
  if (elapsed <= 0){
    printf("ERROR: Something went wrong, negative elapsed time");
    return -1;
  }
  return 0;

}
