#ifndef TIMER_H
#define TIMER_H

long int get_time_usecs();
long int elapsed_time(long int start, long int end);
void print_elapsed_time(long int time, char msg[]);

#endif
