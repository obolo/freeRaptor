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

#include <math.h>

#include <gf2matrix.h>

int wordsize = 8*sizeof(word);

int wordbitmask = 8*sizeof(word);

int wordshift = 5; 


void allocate_gf2matrix(gf2matrix* mat)
{

  mat->n_words = (mat->n_rows + wordsize-1) >> wordshift;

  mat->rows = (word**) malloc(mat->n_rows);
  
  for (int i = 0; i < mat->n_rows; i++)
    {
      mat->rows[i] = (word*) malloc(mat->n_words);
    }

  mat->m_data = (word*)mat->rows[0];
}


int get_nrows(gf2matrix* mat)
{
  return mat->n_rows;
}


int get_cols(gf2matrix* mat)
{
  return mat->n_cols;
}


int get_entry(gf2matrix* mat, int n, int m)
{
  return (mat->rows[n][(m/wordbitmask)] >> m ) & 1;
}

void set_entry(gf2matrix* mat, int n, int m, int val)
{
  mat->rows[n][(m/wordbitmask)] ^=
    (-val ^ mat->rows[n][(m/wordbitmask)]) & (1 << m);
}
