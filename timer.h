#ifndef TIMER_H
#define TIMER_H

#include "macro.h"

#ifdef LINUX
long int get_time_usecs();
long int elapsed_time(long int start, long int end);
void print_elapsed_time(long int time, char msg[]);
#else
void InitSystick();
void print_elapsed_count(char msg[]);
void set_cycle_count(uint32_t count);
#endif

#endif
