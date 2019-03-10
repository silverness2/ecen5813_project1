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
 * @date March 11, 2019
 * @version Sprint 3 
*/

#ifndef MEM_MANIP_H
#define MEM_MANIP_H

#include <stdint.h> // for int32_t

// Typedefs
typedef void (*fp_alloc_mem)(int32_t **words, int total_words);
typedef void (*fp_free_mem)(int32_t **words, int total_words);
typedef void (*fp_write_offset)(int value, int word_offset, int **words, \
                                int total_words);
typedef void (*fp_write_address)(int value, int32_t *addr, int **words, \
                                 int total_words);
typedef void (*fp_invert)(int word_offset, int32_t **words, int total_words);
typedef void (*fp_show)(int word_offset, int num_words, int32_t *words, \
                        int total_words);
typedef void (*fp_write_offset_pattern)(int word_offset, int num_words, \
                                        int seed, int32_t **words, \
                                        int total_words);
typedef void (*fp_write_address_pattern)(int32_t *addr, int num_words, \
                                         int seed, int32_t **words, \
                                         int total_words);
typedef void (*fp_verify_offset_pattern)(int word_offset, int num_words, \
                                         int seed, int32_t **words,
                                         int total_words);
typedef void (*fp_verify_address_pattern)(int32_t *addr, int num_words,
                                          int seed, int32_t **words,
                                          int total_words);

// Functions
int is_mem_valid(int32_t **words);
int is_offset_valid(int word_offset, int total_words);
void alloc_mem(int32_t **words, int total_words);
void free_mem(int32_t **words, int total_words);
void write_offset(int value, int word_offset, int **words, \
                  int total_words);
void write_address(int value, int32_t *addr, int **words, \
                   int total_words);
void invert(int word_offset, int32_t **words, int total_words);
void write_offset_pattern(int word_offset, int num_words, int seed, \
                          int32_t **words, int total_words);
void write_address_pattern(int32_t *addr, int num_words, int seed, \
                           int32_t **words, int total_words);
void verify_offset_pattern(int word_offset, int num_words, int seed, \
                           int32_t **words, int total_words);
void verify_address_pattern(int32_t *addr, int num_words, int seed, \
                            int32_t **words, int total_words);
void show(int word_offset, int num_words, int32_t *words, \
          int total_words);
void show_all_addr(int32_t *words, int total_words);

#endif
