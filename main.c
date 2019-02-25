/*******************************************************************************
 *
 * Copyright (C) 2019 by Shilpi Gupta
 *
 ******************************************************************************/

/*
 * @file main.c
 * @brief A program for interactive memory manipulaton.
 *
 * @author Shilpi Gupta
 * @date February 24, 2019
 * @version Sprint 2
*/

#include <stdio.h> // for getline
#include <stdlib.h> // for malloc, free, NULL
#include <string.h> // for strcmp
#include <stdint.h> // for int32_t
#include "mem_manip.h"

#define CMD_LEN 32

void show_greeting()
{
    printf("\n\nWelcome to Interactive Memory Manipulation!\n\n");
}

void show_prompt()
{
    printf("\nPlease enter a memory command, or type \"help\" for more info."
           "\n");
    printf(">> ");
}

void show_help()
{
    printf("\n-----------------------------------------\n");
    printf("Help Menu\n\n");

    printf("help\n\tShow all commands.\n\n");

    printf("alloc num_words\n\tAllocate num_words of memory (1 word = "
           "32 bits) to be used by\n\tapplication.\n\n");

    printf("free\n\tFree previously allocated words of memory.\n\n");

    printf("write_addr address value\n\tWrite value at address. Use \"show\" "
           "to list addresses.\n\n");

    printf("write word_offset value\n\tWrite value to memory at word_offset."
           "\n\n");

    printf("show [word_offset num_words]\n\tDisplay contents of memory in 32-"
           "bit words in hexadecimal format by\n\tspecifying num_words "
           "to display starting at word_offset. No arguments \n\tshows all."
           "\n\n");

    printf("invert word_offset\n\tInvert all memory bits at word_offset using "
           "bitwise NOT and show time to\n\tperform operation.\n\n");

    printf("write_pattern addresss length seed\n\tWrite a pseudo-random "
           "pattern in a memory area specified by address and\n\tlength using "
           "a seed number and display time to perform operation.\n\n");

    printf("verify_pattern addresss length seed\n\tVerify a pseudo-random "
           "pattern in a memory area specified by address and\n\tlength using "
           "a seed number and display time to perform operation.\n\n");

    printf("exit\n\tExit the program.");
    printf("\n-----------------------------------------\n");
    printf("\n");
}

int main(int argc, char **argv)
{
    int num_read_bytes = 0;
    size_t num_line_bytes = 0;
    char *line = NULL;
    int total_words = 0;
    int32_t *words = NULL;

    show_greeting();

    do {
        // Show prompt and read user input.
        show_prompt();
        num_read_bytes = getline(&line, &num_line_bytes, stdin);

        // Check for error.
        if (num_read_bytes < 0)
        {
            printf("Error reading input. Exiting.");
            free(line);
            line = NULL;
            return (EXIT_FAILURE);
        }

        // Process commands.
        //
        // Exit
        if (strcmp(line, "exit\n") == 0)
        {
            exit(EXIT_SUCCESS);
        }
        // Help
        else if (strcmp(line, "help\n") == 0)
        {
            show_help();
        }
        // Alloc
        else if (strncmp(line, "alloc", strlen("alloc")) == 0)
        {
            char cmd[CMD_LEN];
            int num_args = sscanf(line, "%s %d", cmd, &total_words);
            if (num_args != 2)
            {
               printf("ERROR: Missing argument.\n");
            }
            else
            {     
	        alloc_mem(&words, total_words);
            }
        }
        // Free
        else if (strcmp(line, "free\n") == 0)
        {
            free_mem(&words);
        }
        // Write (with address)
        else if (strncmp(line ,"write_addr", strlen("write_addr")) == 0)
        {
            char cmd[CMD_LEN];
            int32_t *addr = NULL;
            int32_t value;
            int num_args = sscanf(line, "%s %p %d", cmd, &addr, &value);
            if (num_args != 3)
            {
                printf("ERROR: Incorrect argument(s) provided.\n");
            }
            else
            {
               write_a(value, addr, &words, total_words);
            }
        }
        // Write (with offset)
        else if (strncmp(line ,"write", strlen("write")) == 0)
        {
            char cmd[CMD_LEN];
            int word_offset = 0;
            int32_t value;
            int num_args = sscanf(line, "%s %d %d", cmd, &word_offset, &value);
            if (num_args != 3)
            {
                printf("ERROR: Incorrect argument(s) provided.\n");
            }
            else
            {
               write(value, word_offset, &words, total_words);
            }
        }
        // Show
        else if (strncmp(line, "show", strlen("show")) == 0)
        {
            char cmd[CMD_LEN];
            int word_offset = 0, num_words = 0;
            int num_args = sscanf(line, "%s %d %d", cmd, &word_offset,
                                  &num_words);
            if (num_args == 1)
            {
                show(0, total_words, words, total_words);
            }
            else if (num_args != 3)
            {
                printf("ERROR: Incorrect arguments provided.\n");
            }
            else
            {
                show(word_offset, num_words, words, total_words);
            }
        }
        // Invert
        else if (strncmp(line, "invert", strlen("invert")) == 0)
        {
            char cmd[CMD_LEN];
            int word_offset = 0;
            int num_args = sscanf(line, "%s %d", cmd, &word_offset);
            if (num_args != 2)
            {
                printf("ERROR: Incorrect arguments provided.\n");
            }
            else
            {
                long int start_time, end_time;
                start_time = get_time_usecs();
                invert(word_offset, &words, total_words);
                end_time = get_time_usecs();

                printf("After inversion, value is now:\n");
                show(word_offset, 1, words, total_words);
          
                printf("Time to invert was: %ld usecs\n",
                       end_time - start_time);
            }
        }
        // Invalid
        else
        {
            printf("Invalid commnd. Please try again.\n");
        }

        // Free memory.
        free(line);
        line = NULL;
        num_line_bytes = 0;
    } while (1);
    
    return (EXIT_SUCCESS);
}
