#include "macro.h"
#include <stdio.h>

#ifdef LINUX
#include <sys/time.h>
#endif

#ifdef FRDM
#include "fsl_device_registers.h"
#endif

#include "timer.h"

#ifdef LINUX

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
    PRINTF("%s - Elapsed time was: %ld usecs\n", msg, time);
}

#else

void start_cylce_count()
{
    uint16_t ret = SysTick_Config(16000000); // start the cycle count
    if (ret)
    {
        PRINTF("start_cycle_count(): ERROR: Cannot start cycle count.\n");
    } 
}

void print_elapsed_count(char msg[256])
{
    uint32_t ret = 16000000 - SysTick->VAL; // stops the cycle count
    PRINTF("%s - Elapsed cycle count was: %d cycles\n", msg, ret);
}

#endif
