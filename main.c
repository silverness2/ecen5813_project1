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
 * @date March 11, 2019
 * @version Sprint 3
 *
 * Attribution for function pointer typedef:
 * https://stackoverflow.com/questions/7670766/c-how-can-i-use-a-single-function-pointer-array-for-functions-with-variable-par
*/

#include "macro.h"
#include <stdio.h>
#include <stdlib.h> // for malloc, free, NULL
#include <string.h> // for strcmp
#include <stdint.h> // for int32_t
#include "ui.h"
#include "mem_manip.h"
#include "timer.h"

#ifdef FRDM
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"
#endif

#define CMD_LEN 32
#define LINE_LEN 1024

typedef void (*cmd_fp)(void);

struct Cmd
{
    char cmd[CMD_LEN];
    int num_args;
    cmd_fp fp;
};

struct Cmd cmd_list[] =
{
    {"exit", 1, (cmd_fp)exit_prog},   // 0
    {"help", 1, (cmd_fp)show_help},   // 1
    {"alloc", 2, (cmd_fp)alloc_mem},  // 2
    {"free", 1, (cmd_fp)free_mem},    // 3
    {"wa", 3, (cmd_fp)write_address}, // 4
    {"wo", 3, (cmd_fp)write_offset},  // 5
    {"show", 3, (cmd_fp)show},        // 6
    {"invert", 2, (cmd_fp)invert},    // 7
    {"wop", 4, (cmd_fp)write_offset_pattern},  // 8
    {"wap", 4, (cmd_fp)write_address_pattern}, // 9
    {"vop", 4, (cmd_fp)verify_offset_pattern}, // 10
    {"vap", 4, (cmd_fp)verify_address_pattern}  // 11
};

int main(int argc, char **argv)
{
    #ifdef FRDM
    // Init board hardware.
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    Init_Systick();
    #endif

    int total_words = 0;
    int32_t *words = NULL;
    int num_cmds = sizeof(cmd_list) / sizeof(cmd_list[0]);
 
    // Show a greeting on startup.
    show_greeting();

    do {
        // Show prompt.
        show_prompt();

        // Read user input and check for read error.
        char c;
        int count = 0;
        char line[LINE_LEN];
        while ((c = GETCHAR()) != '\n')
        {
           if (c == EOF)
           {
	       PRINTF("Error reading input. Exiting.");
               return (EXIT_FAILURE);
           }
           line[count] = c;
           count++;
        }
        line[count] = '\0';

        // Get command name.
        int cmd_num = -1;
        for (int i = 0; i < num_cmds; i++)
        {
            char cmd[CMD_LEN];
            int num_args = sscanf(line, "%s", cmd);
            if (num_args > 0 && strcmp(cmd, cmd_list[i].cmd) == 0)
            {
                cmd_num = i;
                break;
            }
        }
       
        char cmd[CMD_LEN];
        int num_args;
        int32_t *addr = NULL;
        int32_t value;
        int word_offset;
        int num_words;
        int seed;
        #ifdef LINUX
        long int start_time, end_time;
        #endif

        // Parse and process command.
        switch(cmd_num)
        {
        case 0: // exit
            (cmd_list[cmd_num].fp)();
            break;
        case 1: // help
            (cmd_list[cmd_num].fp)();
            break;
        case 2: // alloc
            num_args = sscanf(line, "%s %d", cmd, &total_words);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                ((fp_alloc_mem)cmd_list[cmd_num].fp)(&words, total_words);
            }
            break;
        case 3: // free
            num_args = sscanf(line, "%s", cmd);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                ((fp_free_mem)cmd_list[cmd_num].fp)(&words, total_words);
            }
            break;
        case 4: // wa
            num_args = sscanf(line, "%s %p %d", cmd, &addr, &value);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                ((fp_write_address)cmd_list[cmd_num].fp)(value, addr, &words, \
                                                         total_words);
            }
            break;
        case 5: // wo
            num_args = sscanf(line, "%s %d %d", cmd, &word_offset, &value);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                ((fp_write_offset)cmd_list[cmd_num].fp)(value, word_offset, \
                                                        &words, total_words);
            }
            break;
        case 6: // show
            num_args = sscanf(line, "%s %d %d", cmd, &word_offset, &num_words);
            if (num_args == 1)
            {
                ((fp_show)cmd_list[cmd_num].fp)(0, total_words, words, \
                                                total_words);
            }
            else
            {
                if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
                {
                    ((fp_show)cmd_list[cmd_num].fp)(word_offset, num_words, \
                                                    words, total_words);
                }
            }
            break;
        case 7: // invert
            num_args = sscanf(line, "%s %d", cmd, &word_offset);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                #ifdef LINUX
                start_time = get_time_usecs();
                #else
                set_cycle_count(0);
                #endif

                ((fp_invert)cmd_list[cmd_num].fp)(word_offset, &words, \
                                                  total_words);
                #ifdef LINUX
                end_time = get_time_usecs();
                print_elapsed_time(elapsed_time(start_time, end_time), \
                                   "main(): invert");
                #else
                print_elapsed_count("main(): invert");
                #endif
            }
            break;
        case 8: // wop
            num_args = sscanf(line, "%s %d %d %d", cmd, &word_offset, \
                              &num_words, &seed);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                #ifdef LINUX
                start_time = get_time_usecs();
                #else
                set_cycle_count(0);
                #endif

                ((fp_write_offset_pattern)cmd_list[cmd_num].fp)(word_offset, \
                                                                num_words,\
                                                                seed, &words, \
                                                                total_words);
                #ifdef LINUX
                end_time = get_time_usecs();
                print_elapsed_time(elapsed_time(start_time, end_time), \
                                   "main(): wop");
                #else
                print_elapsed_count("main(): wop");
                #endif
            }
            break;
        case 9: // wap
            num_args = sscanf(line, "%s %p %d %d", cmd, &addr, &num_words, \
                              &seed);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                #ifdef LINUX
                start_time = get_time_usecs();
                #else
                set_cycle_count(0);
                #endif

                ((fp_write_address_pattern)cmd_list[cmd_num].fp)(addr, \
                                                                 num_words,\
                                                                 seed, &words, \
                                                                 total_words);
                #ifdef LINUX
                end_time = get_time_usecs();
                print_elapsed_time(elapsed_time(start_time, end_time), \
                                   "main(): wap");
                #else
                print_elapsed_count("main(): wap");
                #endif
            }
            break;
        case 10: // vop
            num_args = sscanf(line, "%s %d %d %d", cmd, &word_offset, \
                              &num_words, &seed);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                #ifdef LINUX
                start_time = get_time_usecs();
                #else
                set_cycle_count(0);
                #endif

                ((fp_verify_offset_pattern)cmd_list[cmd_num].fp)(word_offset, \
                                                                 num_words,\
                                                                 seed, &words, \
                                                                 total_words);
                #ifdef LINUX
                end_time = get_time_usecs();
                print_elapsed_time(elapsed_time(start_time, end_time), \
                                   "main(): vop");
                #else
                print_elapsed_count("main(): vop");
                #endif
            }
            break;
        case 11: // vap
            num_args = sscanf(line, "%s %p %d %d", cmd, &addr, &num_words, \
                              &seed);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                #ifdef LINUX
                start_time = get_time_usecs();
                #else
                set_cycle_count(0);
                #endif

                ((fp_verify_address_pattern)cmd_list[cmd_num].fp)(addr, \
                                                                  num_words,\
                                                                  seed, \
                                                                  &words, \
                                                                  total_words);
                #ifdef LINUX
                end_time = get_time_usecs();
                print_elapsed_time(elapsed_time(start_time, end_time), \
                                   "main(): vap");
                #else
                print_elapsed_count("main(): vap");
                #endif
            }
            break;
        default:
            PRINTF(ERROR_BAD_CMD);
            break;
        }
    } while (1);
    
    return (EXIT_SUCCESS);
}
