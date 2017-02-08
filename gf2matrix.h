// Copyright 2016 Roberto Francescon
// This file is part of freeRaptor.
//
// freeRaptor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// freeRaptor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with freeRaptor.  If not, see <http://www.gnu.org/licenses/>.

/**
 * @author  Roberto Francescon
 * @brief   Definition and implementation of Galois Field GF(2) matrices and vectors
 * @version 0.0.1
 * @file    gf2matrix.h
 */

#ifndef GF2MATRIX_H
#define GF2MATRIX_H

#include <iostream>
#include <string>
#include <assert.h>
#include <fstream>
#include <cstring>

/**
 * Class representing a GF(2) matrix.
 * Representation based on the 32 bit packed words.
 */

class GF2mat
{
 public:
  /**
   * Constructor for generating a GF(2) matrix represented as 32 bit packed words
   */
  GF2mat(int n_rows, int n_cols);
  /**
   * Destructor of the GF(2) matrix
   */
  ~GF2mat();
    /**
   * Copy-Constructor of the GF(2) matrix
   */
   GF2mat(const GF2mat &A);
  /**
   * Method for obtaining the number of rows
   */
  int get_nrows();
  /**
   * Method for obtaining the number of columns
   */
  int get_ncols();
    /**
   * Method for obtaining the number of words
   */
  int get_nwords();
  /**
   * Method for obtaining an entry of a GF2mat matrix
   */
  int get_entry(int row, int col);
  /**
   * Method for setting an entry of a GF2mat matrix
   */
  void set_entry(int row, int col, int val);
  /**
   * Method for exchanging 2 rows
   */
  void row_exchange(int a, int b);
   /**
   * Method for exchanging 2 columns
   */
  void col_exchange(int a, int b);
  /**
   * Operator overloading for multiplying two GF2mat matrices.
   * @param v GF2mat sencond operand
   */
  GF2mat operator*(GF2mat &v);
  /**
   * Method for setting to zero all the selected entries
   * of the G_LT partof the GF2mat matrix.
   * Specfically built for the R10Codec objects.
   * @param K int number of source symbols
   * @param S number of LDPC symbols
   * @param H number of Half symbols
   */
  void clear_LT(int K, int S, int H);
    /**
   * Method for inverting through Gaussian Elimination method.
   * Other methods, such as Belief Propagation or Inactivation Decoding
   * may be implemented in the future.
   */
  void invert_GE();
  /**
   * Method for printing a GF(2) matrix to the stdout
   */
  void print();

 protected:
  int n_col; /**< Number of columns of the GF(2) matrix */
  int n_row; /**< Number of rows of the GF(2) matrix */
  int n_word; /**< Number of 32-bit words used to represent a single rows*/
  const int wordsize = 32; /**< Number of bits that are group together. If needed */
  const int wordmasksize = 5; /**< Number of 1 bits in the word mask */
  const int wordmask = 0x1f; /**< Bitmask used to perfom modulo operation bitwisely */

  uint32_t** cols; /**< Main ref to the matrix data. Pointer to array of pointers to columns */
  uint32_t** rows; /**< Main ref to the matrix data. Pointer to array of pointers to rows */
  uint32_t* gf2mat; /**< Block of memory used to manage bits */

};


#endif
