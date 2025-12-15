#include <timer.h>

int main(){

  struct timer a;
  timer_start(&a, 10);
  sleep(1);
  timer_stop(&a);
  if (a.freq <= 0){
    printf("ERROR: Something went wrong, negative CPU Freq calculated");
    return -1;
  }
  return 0;

}
