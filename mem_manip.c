/*******************************************************************************
 *
 * Copyright (C) 2019 by Shilpi Gupta
 *
 ******************************************************************************/

/*
 * @file mem_manip.c
 * @brief Library definitions for interactive memory manipulaton.
 *
 * @author Shilpi Gupta
 * @date February 24, 2019
 * @version Sprint 2
*/

#include "mem_manip.h"
#include <stdio.h> // printf
#include <stdlib.h> // malloc, free, NULL
#include <string.h>
#include <sys/time.h>
#include <stdbool.h>

long int get_time_usecs()
{
    struct timeval curr_time;
    gettimeofday(&curr_time, NULL);

    // Return time in microseconds.
    return ((curr_time.tv_sec * 1000000L) + curr_time.tv_usec);
}

void alloc_mem(int32_t **words, int total_words)
{
    // Check no memory allocated.
    if (*words != NULL)
    {
        printf("alloc_mem(): ERROR: Cannot allocate memory because memory " \
               "already allocated. Please free memory first.\n");
        return;
    }

    // Allocate memory.
    *words = malloc(total_words * sizeof(int32_t));

    // Check success.
    if (*words == NULL)
    {
        printf("alloc_mem(): ERROR: Unable to allocate %d words of memory.\n", \
               total_words);
	return;
    }
    else
    {
        printf("alloc_mem(): Allcoated %d words (%d bytes) of memory.\n", \
               total_words, (total_words * (int32_t)sizeof(int32_t)));
    }
}

void free_mem(int32_t **words)
{
    // Free memory.
    if (*words)
    {
        free(*words);
        *words = NULL;
        printf("free_mem(): Freed all allocated memory.\n");
    }
    else
    {
        printf("free_mem(): No memory to free.\n");
    }
}

void write(const int value, int word_offset, int **words, int total_words)
{
    if (*words == NULL)
    {
        printf("write(): ERROR: Cannot write. No memory allocated.\n");
        return;
    }

    if (word_offset >= total_words)
    {
        printf("write(): ERROR: Cannot write. Invalid memory location.\n");
        return;
    }

    *(*words + word_offset) = value;
}

void write_a(const int value, int32_t *addr, int **words, int total_words)
{
    if (*words == NULL)
    {
        printf("write(): ERROR: Cannot write. No memory allocated.\n");
        return;
    }

    bool found = false;
    for (int i = 0; i < total_words; i++)
    {
        if (addr == (*words + i))
        {
            found = true;
            *(*words + i) = value;
            break;
        }
    }

    if (found == false)
    {
        printf("write(): ERROR: Invalid memory address provided. Valid "
               "addresses are:\n");
        for (int i = 0; i < total_words; i++)
        {
	    printf("At offset %d, address is: %p\n", i,
                   (*words + i));
        }
    }
}

void show(int word_offset, int num_words, const int32_t *words,
          int total_words)
{
    if (words == NULL)
    {
        printf("show(): ERROR: Cannot show. No memory allocated.\n");
        return;
    }

    if (word_offset >= total_words || word_offset + num_words > total_words)
    {
        printf("write(): ERROR: Cannot show. Invalid memory location.\n");
        return;
    }

    for (int i = word_offset; i < word_offset + num_words; i++)
    {

        printf("At word=%d and address=%p, int value=%d and hex value="
               "0x%04x\n", i, (words + i), *(words + i), *(words + i));

       // printf("At offset: %d, value is: %d (hex is: 0x%04x)\n", i,
         //      *(words + i), *(words + i));
    }
}

void invert(int word_offset, int32_t **words, int total_words)
{
    if (*words == NULL)
    {
        printf("invert(): ERROR: Cannot write. No memory allocated.\n");
        return;
    }

    if (word_offset >= total_words)
    {
        printf("invert(): ERROR: Cannot write. Invalid memory location.\n");
        return;
    }
   
    *(*words + word_offset) =~ *(*words + word_offset);
}
