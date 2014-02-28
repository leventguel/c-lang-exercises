/* my_delay.h */
#include <sys/time.h>
#define FRAME_LEN 50000
static struct timeval st, rt;
static int delay(int i) {
  struct timeval timeout;
  if (i>0) {
    timeout.tv_usec = i % (unsigned long) 1000000;
    timeout.tv_sec = i / (unsigned long) 1000000;
    select(0, NULL, NULL, NULL, &timeout);
  }
  return (i>0 ? i : 0);
}
static int time_diff(void) {
  int diff;
  gettimeofday(&rt, NULL);
  diff = (1000000*(rt.tv_sec-st.tv_sec))+(rt.tv_usec-st.tv_usec);
  st = rt;
  return diff;
}
