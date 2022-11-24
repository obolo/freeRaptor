/*
 *  Copyright 2020 Roberto Francescon
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

#include <gf2matrix.h>
#include <math.h>

uint32_t wordsize = 8 * sizeof(word);
uint32_t wordbitmask = 8 * sizeof(word);
uint32_t wordshift = 5;

void allocate_gf2matrix(gf2matrix *mat, uint32_t n_rows, uint32_t n_cols) {
  mat->n_rows = n_rows;
  mat->n_cols = n_cols;
  mat->n_words = (mat->n_cols + wordsize - 1) >> wordshift;
  mat->rows = (word **)malloc(mat->n_rows * sizeof(word *));

  for (int i = 0; i <= mat->n_rows; i++) {
    mat->rows[i] = (word *)malloc(mat->n_words);
    memset(mat->rows[i], 0, mat->n_words);
  }

  mat->m_data = (word *)mat->rows[0];
}

void dealloc_gf2matrix(gf2matrix *mat) {
  for (int i = 0; i <= mat->n_rows; i++) {
    free(mat->rows[i]);
  }
  free(mat->rows);
}

uint32_t get_nrows(gf2matrix *mat) { return mat->n_rows; }

uint32_t get_ncols(gf2matrix *mat) { return mat->n_cols; }

uint32_t get_nwords(gf2matrix *mat) { return mat->n_words; }

int get_entry(gf2matrix *mat, int n, int m) {
  return (mat->rows[n][(m / wordbitmask)] >> m) & 1;
}

word *get_word(gf2matrix *mat, int n, int l) {
  return mat->rows[n] + l * sizeof(word);
}

void set_entry(gf2matrix *mat, int n, int m, int val) {
  mat->rows[n][(m / wordbitmask)] ^=
      (-val ^ mat->rows[n][(m / wordbitmask)]) & (1 << m);
}

void swap_rows(gf2matrix *mat, int n, int k) {
  word *tmp = mat->rows[n];
  mat->rows[n] = mat->rows[k];
  mat->rows[k] = tmp;
}

void print_matrix(gf2matrix *mat) {
  for (int i = 0; i < get_nrows(mat); i++) {
    for (int j = 0; j < get_ncols(mat); j++) {
      printf("%d", get_entry(mat, i, j));
      printf(" ");
    }

    printf("\n");
  }
}

void swap_cols(gf2matrix *mat, int m, int k) {
  word *tmp;

  for (int i = 0; i < get_nrows(mat); i++) {
    int tmp_val = get_entry(mat, i, m);
    set_entry(mat, i, m, get_entry(mat, i, k));
    set_entry(mat, i, k, tmp_val);
  }
}

void mat_mul(gf2matrix *matA, gf2matrix *matB, gf2matrix *result) {
  int i = 0;
  int j = 0;
  int part = 0;
  for (i = 0; i < get_ncols(matA); i++) {
    for (j = 0; j < get_nrows(matB); j++) {
      part = get_entry(matA, i, 0) * get_entry(matB, 0, j);

      for (int z = 1; z < get_ncols(matA); z++) {
        part = part ^ (get_entry(matA, i, z) * get_entry(matB, z, j));
      }

      set_entry(result, i, j, part);
    }
  }
}

int gaussjordan_inv(gf2matrix *mat) {
  gf2matrix identity;
  allocate_gf2matrix(&identity, get_nrows(mat), get_ncols(mat));
  for (int i = 0; i < get_nrows(&identity); i++) {
    for (int j = 0; j < get_ncols(&identity); j++) {
      if (i == j)
        set_entry(&identity, i, j, 1);
    }
  }

  int n_rows = get_nrows(mat);
  int n_cols = get_ncols(mat);

  int j = 0;
  int i = 0;
  for (i = 0; i < get_nrows(mat); i++) {
    j = i;

    while (j < get_ncols(mat) && get_entry(mat, j, i) == 0)
      j = j + 1;

    if (i != j)
      swap_rows(mat, i, j);
    swap_rows(&identity, i, j);

    for (int k = 0; k < get_nrows(mat); k++) {
      if (k != i) {
        if (get_entry(mat, k, i) == 1) {
          for (int l = 0; l < get_nwords(mat); l++) {
            mat->rows[k][l] = mat->rows[k][l] ^ mat->rows[i][l];
            (&identity)->rows[k][l] =
                (&identity)->rows[k][l] ^ (&identity)->rows[i][l];
          }
        }
      }
    }
  }

  *mat = identity;
  return 0;
}
