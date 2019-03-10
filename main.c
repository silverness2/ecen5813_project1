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


// TODO
// timing (long problem?)

#include <stdio.h>  // for getline
#include <stdlib.h> // for malloc, free, NULL
#include <string.h> // for strcmp
#include <stdint.h> // for int32_t
#include "ui.h"
#include "mem_manip.h"
#include "timer.h"

#define CMD_LEN 32

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
    {"show", 1, (cmd_fp)show},        // 6
    {"invert", 2, (cmd_fp)invert},    // 7
    {"wop", 4, (cmd_fp)write_offset_pattern},  // 8
    {"wap", 4, (cmd_fp)write_address_pattern}, // 9
    {"vop", 4, (cmd_fp)verify_offset_pattern}, // 10
    {"vap", 4, (cmd_fp)verify_address_pattern}  // 11
};

int main(int argc, char **argv)
{
    int num_bytes_read = 0;
    size_t num_line_bytes = 0;
    char *line = NULL;
    int total_words = 0;
    int32_t *words = NULL;
    int num_cmds = sizeof(cmd_list) / sizeof(cmd_list[0]);
 
    // Show a greeting on startup.
    show_greeting();

    do {
        // Show prompt.
        show_prompt();

        // Read user input.
        num_bytes_read = getline(&line, &num_line_bytes, stdin);

        // Check for read error.
        if (num_bytes_read < 0)
        {
            printf("Error reading input. Exiting.");
            free(line);
            line = NULL;
            return (EXIT_FAILURE);
        }

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
        long int start_time, end_time;
        int seed;

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
                start_time = get_time_usecs();
                ((fp_invert)cmd_list[cmd_num].fp)(word_offset, &words, \
                                                  total_words);
                end_time = get_time_usecs();
                print_elapsed_time(elapsed_time(start_time, end_time), \
                                   "main(): invert");
            }
            break;
        case 8: // wop
            num_args = sscanf(line, "%s %d %d %d", cmd, &word_offset, \
                              &num_words, &seed);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                start_time = get_time_usecs();
                ((fp_write_offset_pattern)cmd_list[cmd_num].fp)(word_offset, \
                                                                num_words,\
                                                                seed, &words, \
                                                                total_words);
                end_time = get_time_usecs();
                print_elapsed_time(elapsed_time(start_time, end_time), \
                                   "main(): wop");
            }
            break;
        case 9: // wap
            num_args = sscanf(line, "%s %p %d %d", cmd, &addr, &num_words, \
                              &seed);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                start_time = get_time_usecs();
                ((fp_write_address_pattern)cmd_list[cmd_num].fp)(addr, \
                                                                 num_words,\
                                                                 seed, &words, \
                                                                 total_words);
                end_time = get_time_usecs();
                print_elapsed_time(elapsed_time(start_time, end_time), \
                                   "main(): wap");
            }
            break;
        case 10: // vop
            num_args = sscanf(line, "%s %d %d %d", cmd, &word_offset, \
                              &num_words, &seed);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                start_time = get_time_usecs();
                ((fp_verify_offset_pattern)cmd_list[cmd_num].fp)(word_offset, \
                                                                 num_words,\
                                                                 seed, &words, \
                                                                 total_words);
                end_time = get_time_usecs();
                print_elapsed_time(elapsed_time(start_time, end_time), \
                                   "main(): vop");
            }
            break;
        case 11: // vap
            num_args = sscanf(line, "%s %p %d %d", cmd, &addr, &num_words, \
                              &seed);
            if (is_valid_num_args(num_args, cmd_list[cmd_num].num_args))
            {
                start_time = get_time_usecs();
                ((fp_verify_address_pattern)cmd_list[cmd_num].fp)(addr, \
                                                                  num_words,\
                                                                  seed, \
                                                                  &words, \
                                                                  total_words);
                end_time = get_time_usecs();
                print_elapsed_time(elapsed_time(start_time, end_time), \
                                   "main(): vap");
            }
            break;
        default:
            printf(ERROR_BAD_CMD);
            break;
        }

        // Free memory.
        free(line);
        line = NULL;
        num_line_bytes = 0;
    } while (1);
    
    return (EXIT_SUCCESS);
}
