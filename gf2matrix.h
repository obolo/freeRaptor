/*
 *  Copyright 2019 Roberto Francescon
 *  This file is part of freeRaptor.
 *
 *  freeRaptor is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  freeRaptor is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with freeRaptor.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @author  Roberto Francescon
 * @brief   Definition and implementation of Galois Field GF(2) matrices
 *          and vectors
 * @version 0.1.0
 * @file    gf2matrix.h
 */

#ifndef GF2MATRIX_H
#define GF2MATRIX_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/** Typedef word: here as a uint32_t type */
typedef uint32_t word;

/** Size in bits of the word used for packed bits */
extern uint32_t wordsize;

/** Bit mask of the word */
extern uint32_t wordbitmask;

/** NUmber of positions to shift by to divide by word */
extern uint32_t wordshift;

/**
 * Struct that defines the binary GF(2) matrix type as packed words.
 * Defualt word is 32 bit long as this is the smallest unit for the raptor
 * symbol.
 */
typedef struct
{
  uint32_t n_rows;
  uint32_t n_cols;
  uint32_t n_words;

  word** rows;
  word* m_data;

} gf2matrix;

/**
 * Function that allocates the memory to accomodate for a GF(2) matrix.
 * The allocated memory is initialized to zero.
 * @param mat gf2matrix pointer to the selected matrix
 */
void allocate_gf2matrix(gf2matrix* mat, uint32_t n_cols, uint32_t n_rows);

/**
 * Function that returns the number of rows of a selected GF(2) matrix
 * @param mat gf2matrix pointer to the selected matrix
 * @return integer number of rows
 */
uint32_t get_nrows(gf2matrix* mat);

/**
 * Function that returns the number of columns of a selected GF(2) matrix
 * @param mat gf2matrix pointer to the selected matrix
 * @return integer number of columns
 */
uint32_t get_ncols(gf2matrix* mat);

/**
 * Function that returns the number of columns of a selected GF(2) matrix
 * @param mat gf2matrix pointer to the selected matrix
 * @return integer number of columns
 */
uint32_t get_nwords(gf2matrix* mat);

/**
 * Function that return the binary value at (n,m)
 * @param mat gf2matrix pointer to the selected matrix
 * @param n integer index of the selected row
 * @param m integer index of the selected column
 * @return binary value of the entry at position (n,m)
 */
int get_entry(gf2matrix* mat, int n, int m);

/**
 * Function that returns the pointer to a specific word at index l
 * @param mat
 * @param n integer index of the selected row
 * @param l integer index of the selected word
 */
word* get_word(gf2matrix* mat, int n, int l);

/**
 * Function that set a particular bit to the selected value
 * @param mat gf2matrix pointer to the selected matrix
 * @param n integer index of the selected row
 * @param m integer index of the selected column
 * @param val value to set at position (n,m)
 */
void set_entry(gf2matrix* mat, int n, int m, int val);

/**
 * Function that swaps two rows of a given matrix
 * @param matrix whose rows have to swapped
 * @param index of the first row to swap
 * @param index of the second row to swap
 */
void swap_rows(gf2matrix* mat, int n, int k);

/**
 * Function that swaps two columns of a given matrix
 * @param matrix whose columns have to swapped
 * @param index of the first column to swap
 * @param index of the second column to swap
 */
void swap_cols(gf2matrix* mat, int m, int k);

/**
 * Function that prints the matrix.
 * All the matrix, so be careful.
 * Used for debugging purposes.
 */
void print_matrix(gf2matrix* mat);

/**
 * Matrix multiplication done in the lest efficient way possible:
 * element per element
 * @param matA first matrix to multiply
 * @param matB second matrix to multiply
 * @param return parameter result matrix
 */
void mat_mul(gf2matrix* matA, gf2matrix* matB, gf2matrix* result);

/**
 * Function that inverts the given matrix, if possible, through gasussian
 * elimination. If the given matrix is found not invertible, false is returned.
 * @param mat gf2matrix to which to apply the Gaussia-Elimination inversion
 * @return integer something NOT CLEAR
 */
int gaussjordan_inv(gf2matrix* mat);

#endif
