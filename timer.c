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

#endif

#ifdef FRDM

void start_cylce_count()
{
    // Generate an interrupt every millisecond; start cycle count.
    uint16_t ret = SysTick_Config(SystemCoreClock/1000);
    if (ret)
    {
        PRINTF("start_cycle_count(): ERROR: Cannot start cycle count.\n");
    } 
}

void print_elapsed_count(char msg[256])
{
    uint32_t ret = (SystemCoreClock/1000) - SysTick->VAL; // stope cycle count
    PRINTF("%s - Elapsed cycle count was: %d cycles\n", msg, ret);
}

/*void SysTick_Handler(void)
{
}*/

#endif
