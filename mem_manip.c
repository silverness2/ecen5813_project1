#include "mem_manip.h"
#include <stdio.h> // printf
#include <stdlib.h> // malloc, free, NULL
#include <string.h>

void alloc_mem(char **words, int num_words)
{
    // Check no memory allocated.
    if (*words != NULL)
    {
        printf("alloc_mem(): ERROR: Cannot allocate memory because memory " \
               "already allocated. Please free memory first.\n");
        return;
    }

    // Allocate memory.
    *words = malloc(num_words * BYTES_PER_WORD);

    // Check success.
    if (*words == NULL)
    {
        printf("alloc_mem(): ERROR: Unable to allocate %d words of memory.\n", \
               num_words);
	return;
    }
    else
    {
        printf("alloc_mem(): Allcoated %d words (%d bytes) of memory.\n", \
               num_words, (num_words*BYTES_PER_WORD));
    }
}

void free_mem(char **words)
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
