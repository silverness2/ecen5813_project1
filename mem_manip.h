#ifndef MEM_MANIP_H
#define MEM_MANIP_H

#define BYTES_PER_WORD 32

void alloc_mem(char **words, int num_words);
void free_mem(char **words);

#endif
