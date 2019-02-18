#include <stdio.h> // for getline
#include <stdlib.h> // for free
#include <string.h> // for strcmp

void show_greeting()
{
    printf("\nWelcome to Interactive Memory Manipulation!\n\n");
}

void show_prompt()
{
    printf("Please enter a memory command, or type \"help\" for more info.\n");
    printf(">> ");
}

void show_help()
{
    printf("\n-----------------------------------------\n");
    printf("Help Menu\n\n");

    printf("help\n\tShow all commands.\n\n");

    printf("allocate num_bytes\n\tAllocate num_bytes bytes of memory to be "
           "used by application.\n\n");

    printf("free\n\tFree previously allocated block of memory.\n\n");

    printf("display address num_words\n\tDisplay contents of memory in 32-"
           "bit words in hexadecimal format by\n\tspecifying num_words words "
           "to display and an address.\n\n");

    printf("write address value\n\tWrite value at address.\n\n");

    printf("invert address\n\tInvert all memory bits at address using XOR "
            "and display time to perform\n\toperation.\n\n");

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
    int num_read = 0;
    size_t num_bytes = 0;
    char *line;

    show_greeting();

    do {
        // Show prompt and read user input.
        show_prompt();
        num_read = getline(&line, &num_bytes, stdin);

        // Check for error.
        if (num_read < 0)
        {
            printf("Error reading input. Exiting.");
            free(line);
            return (EXIT_FAILURE);
        }

        // Process commands.
        if (strcmp(line, "exit\n") == 0)
        {
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(line, "help\n") == 0)
        {
            show_help();
        }
        else
        {
            printf("Invalid commnd - try again.\n");
        }
    } while (1);
    
    // Free memory.
    free(line);

    return (EXIT_SUCCESS);
}
