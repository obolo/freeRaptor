/*
 *  Copyright 2018 Roberto Francescon
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
 * @version 0.0.1
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
extern int wordsize;

/** Bit mask of the word */
extern int wordbitmask;

/** NUmber of positions to shift by to divide by word */
extern int wordshift;

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
void allocate_gf2matrix(gf2matrix* mat);

/**
 * Function that returns the number of rows of a selected GF(2) matrix
 * @param mat gf2matrix pointer to the selected matrix
 * @return integer number of rows
 */
int get_nrows(gf2matrix* mat);

/**
 * Function that returns the number of columns of a selected GF(2) matrix
 * @param mat gf2matrix pointer to the selected matrix
 * @return integer number of columns
 */
int get_ncols(gf2matrix* mat);

/**
 * Function that return the binary value at (n,m)
 * @param mat gf2matrix pointer to the selected matrix
 * @param n integer index of the selected row
 * @param m integer index of the selected column
 * @return binary value of the entry at position (n,m)
 */
int get_entry(gf2matrix* mat, int n, int m);

/**
 * Function that set a particular bit to the selected value
 * @param mat gf2matrix pointer to the selected matrix
 * @param n integer index of the selected row
 * @param m integer index of the selected column
 * @param val value to set at position (n,m)
 */
void set_entry(gf2matrix* mat, int n, int m, int val);


#endif
