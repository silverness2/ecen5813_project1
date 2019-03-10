#include <stdio.h>
#include <sys/time.h>
#include "timer.h"

long int get_time_usecs()
{
    struct timeval curr_time;
    gettimeofday(&curr_time, NULL);

    // Return time in microseconds.
    return ((curr_time.tv_sec * 1000000L) + curr_time.tv_usec);
}

long int elapsed_time(long int start, long int end)
{
    return (end - start);
}

void print_elapsed_time(long int time, char msg[256])
{
    printf("%s - Elapsed time was: %ld usecs\n", msg, time);
}
