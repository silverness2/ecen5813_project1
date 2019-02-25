/*******************************************************************************
 *
 * Copyright (C) 2019 by Shilpi Gupta
 *
 ******************************************************************************/

/*
 * @file mem_manip.h
 * @brief Library declarations for interactive memory manipulaton.
 *
 * @author Shilpi Gupta
 * @date February 24, 2019
 * @version Sprint 2
*/

#ifndef MEM_MANIP_H
#define MEM_MANIP_H

#include <stdint.h> // for int32_t

#define BYTES_PER_WORD 1//4 

long int get_time_usecs();
void alloc_mem(int32_t **words, int total_words);
void free_mem(int32_t **words);
void write(const int value, int word_offset, int **words, int total_words);
void show(int word_offset, int num_words, const int32_t *words,
          int total_words);
void invert(int word_offset, int32_t **words, int total_words);

void write_a(const int value, int32_t *addr, int **words, int total_words);

#endif
