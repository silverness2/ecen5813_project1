/*******************************************************************************
 *
 * Copyright (C) 2019 by Shilpi Gupta
 *
 ******************************************************************************/

/*
 * @file ui.c
 * @brief
 *
 * @author Shilpi Gupta
 * @date March 11, 2019
 * @version Sprint 3
*/

#include "macro.h"
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

void exit_prog()
{
    exit(EXIT_SUCCESS);
}

void show_greeting()
{
    PRINTF("\n\nWelcome to Interactive Memory Manipulation!\n\n");
}

void show_prompt()
{
    PRINTF("\nPlease enter a memory command, or type \"help\" for more info."
           "\n");
    PRINTF(">> ");
}

void show_help()
{
    PRINTF("\n-----------------------------------------\n");
    PRINTF("Help Menu\n\n");

    PRINTF("help\n\tShow all commands.\n\n");

    PRINTF("alloc num_words\n\tAllocate num_words of memory (1 word = "
           "32 bits) to be used by\n\tapplication.\n\n");

    PRINTF("free\n\tFree previously allocated words of memory.\n\n");

    PRINTF("wa address value\n\tWrite value at address. Use \"show\" "
           "to list addresses.\n\n");

    PRINTF("wo word_offset value\n\tWrite value to memory at word_offset."
           "\n\n");

    PRINTF("show [word_offset num_words]\n\tDisplay contents of memory in 32-"
           "bit words in hexadecimal format by\n\tspecifying num_words "
           "to display starting at word_offset. No arguments \n\tshows all."
           "\n\n");

    PRINTF("invert word_offset\n\tInvert all memory bits at word_offset using "
           "bitwise NOT and show time to\n\tperform operation.\n\n");

    PRINTF("wap address length seed\n\tWrite a pseudo-random "
           "pattern in a memory area specified by address and\n\tlength using "
           "a seed number and display time to perform operation.\n\n");

    PRINTF("wop word_offset length seed\n\tWrite a pseudo-random pattern in a "
           "memory area specified by word_offset\n\tand length "
           "using a seed number and display time to perform operation.\n\n");

    PRINTF("vap address length seed\n\tVerify a pseudo-random "
           "pattern in a memory area specified by address and\n\tlength using "
           "a seed number and display time to perform operation.\n\n");

    PRINTF("vop word_offset length seed\n\tVerify a pseudo-random "
           "pattern in a memory area specified by word_offset\n\tand length "
           "using a seed number and display time to perform operation.\n\n");

    PRINTF("exit\n\tExit the program.");
    PRINTF("\n-----------------------------------------\n");
    PRINTF("\n");
}

int is_valid_num_args(int num_user_args, int num_cmd_args)
{
    if (num_user_args != num_cmd_args)
    {
        PRINTF(ERROR_MISSING_ARG);
        return 0;
    }
    return 1;
}
