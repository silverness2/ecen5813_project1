#ifndef UI_H
#define UI_H

#define ERROR_MISSING_ARG "ERROR: Incorrect number of arguments.\n"
#define ERROR_BAD_CMD "ERROR: Invalid command.\n"

void exit_prog();
void show_greeting();
void show_prompt();
void show_help();
int is_valid_num_args(int num_user_args, int num_cmd_args);

#endif
