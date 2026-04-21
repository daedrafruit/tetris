#include <stdlib.h>
#include <sys/time.h>

double get_time_ms() {
  struct timeval time;
  gettimeofday(&time, NULL);
  double time_taken;
  time_taken = time.tv_sec * 1000 + time.tv_usec / 1000.0;
  return time_taken;
}


