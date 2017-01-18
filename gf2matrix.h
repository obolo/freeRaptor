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

#ifndef LIBR10_H
#define LIBR10_H

#include <iostream>
#include <string>
#include <assert.h>
#include <fstream>

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
 * Method for obtaining the number of rows
 */
int get_nrows();
/**
 * Method for obtaining the number of columns
 */
int get_ncols();
/**
 * Method for obtaining an entry of a GF2mat matrix
 */
int get_entry(int row, int col);
/**
 * Method for setting an entry of a GF2mat matrix
 */
void set_entry(int row, int col, int val);

private:
int n_col; /** Number of columns of the GF(2) matrix */
int n_row; /** Number of rows of the GF(2) matrix */
int n_words; /** Number of 32-bit words used to represent a single column*/
const int wordsize = 32; /** Number of bits that are group together. If needed. */

uint32_t** gf2mat;

}


#endif
