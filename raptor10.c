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

#include <math.h>
#include <raptor10.h>
#include <stdint.h>

uint popcount(uint v) {
  uint c; // c accumulates the total bits set in v

  for (c = 0; v; c++) {
    v &= v - 1; // clear the least significant bit set
  }

  return c;
}

void generate_gray_seq(uint32_t *gray_seq) {
  for (uint32_t i = 0; i < 4000; i++) {
    gray_seq[i] = i ^ (uint32_t)(floor(i / 2));
  }
}

int factorial(int n) {
  if (n == 0)
    return 1;
  else
    return n * factorial(n - 1);
}

int is_prime(uint32_t n) {
  int flag = 0;
  for (uint i = 2; i <= n / 2; ++i) {
    // condition for non-prime
    if (n % i == 0) {
      flag = 1;
      break;
    }
  }
  if (flag == 0)
    return 1;
  else
    return 0;
}

int choose(int i, int j) {
  return (factorial(i)) / (factorial(j) * factorial(i - j));
}

void r10_Trip(uint32_t K, uint32_t X, uint32_t triple[3], Raptor10 *obj) {
  uint32_t L = obj->K + obj->S + obj->H;
  uint32_t L_ = obj->L;
  while (!is_prime(L_)) {
    L_++;
  }

  uint32_t Q = 65521;
  uint32_t A = (53591 + J[K - 4] * 997) % Q;
  uint32_t B = 10267 * (J[K - 4] + 1) % Q;
  uint32_t Y = (B + X * A) % Q;
  uint32_t v = r10_Rand(Y, 0, (uint32_t)pow(2.0, 20.0));
  uint32_t d = r10_Deg(v);
  uint32_t a = 1 + r10_Rand(Y, 1, L_ - 1);
  uint32_t b = r10_Rand(Y, 2, L_);

  triple[0] = d;
  triple[1] = a;
  triple[2] = b;
}

uint32_t r10_Rand(uint32_t X, uint32_t i, uint32_t m) {
  return (V0[(X + i) % 256] ^ V1[((uint32_t)floor(X / 256) + i) % 256]) % m;
}

uint32_t r10_Deg(uint32_t v) {
  if (v < 0 || v > 1048576)
    return -1; // invalid

  if (v >= 0 && v < 10241) {
    return 1;
  } else if (v >= 10241 && v < 491582) {
    return 2;
  } else if (v >= 491582 && v < 712794) {
    return 3;
  } else if (v >= 712794 && v < 831695) {
    return 4;
  } else if (v >= 831695 && v < 948446) {
    return 10;
  } else if (v >= 948446 && v < 1032189) {
    return 11;
  } else if (v >= 1032189 && v < 1048576) {
    return 40;
  }
}

int r10_build_LDPC_submat(int K, int S, gf2matrix *A) {
  int a = 0;
  int b = 0;

  for (int i = 0; i < K; i++) {
    a = 1 + ((int)floor(i / S) % (S - 1));
    b = i % S;
    set_entry(A, b, i, 1);
    /* C[K+b] = C[K+b] ^ C[i]; */
    b = (b + a) % S;
    set_entry(A, b, i, 1);
    /* C[K+b] = C[K+b] ^ C[i]; */
    b = (b + a) % S;
    set_entry(A, b, i, 1);
    /* C[K+b] = C[K+b] ^ C[i]; */
  }
}

int r10_build_Half_submat(unsigned int K, unsigned int S, unsigned int H,
                          gf2matrix *A) {
  uint32_t g[4000];
  generate_gray_seq(&g[0]);
  uint H_ = ceil((float)H / 2.0);
  int n_bits = (int)sizeof(*g) * 8;
  size_t n_words = 4000;
  uint32_t m[n_words];

  uint j = 0;
  for (size_t i = 0; i < n_words; i++) {
    if (popcount(g[i]) == H_) {
      m[j] = g[i];
      j++;
    }
  }

  // Build the G_HALF submatrix
  for (uint h = 0; h < H; h++) {
    for (uint j = 0; j < K + S; j++) {
      if (m[j] & (1UL << h)) {
        set_entry(A, h + S, j, 1);
      }
    }
  }
}

int r10_build_LT_submat(uint32_t K, uint32_t S, uint32_t H, Raptor10 *obj,
                        gf2matrix *A) {
  uint32_t L = K + S + H;
  uint32_t L_ = L;
  while (!is_prime(L_)) {
    L_++;
  }

  for (uint32_t i = 0; i < K; i++) {
    uint32_t triple[3] = {0};
    r10_Trip(K, i, triple, obj);
    uint32_t d = triple[0];
    uint32_t a = triple[1];
    uint32_t b = triple[2];
    uint32_t j_max = fmin((d - 1), (L - 1));

    while (b >= L)
      b = (b + a) % L_;

    set_entry(A, i + S + H, b, 1);

    for (uint j = 1; j <= j_max; j++) {
      b = (b + a) % L_;

      while (b >= L)
        b = (b + a) % L_;

      set_entry(A, i + S + H, b, 1);
    }
  }
}

void r10_build_LT_mat(uint32_t N, Raptor10 *obj, gf2matrix *G_LT,
                      uint32_t *ESIs) {
  uint32_t L = obj->K + obj->S + obj->H;
  uint32_t L_ = obj->L;
  while (!is_prime(L_)) {
    L_++;
  }

  for (uint32_t i = 0; i < obj->N; i++) {

    uint32_t triple[3] = {0};
    uint32_t X = ESIs[i];
    r10_Trip(obj->K, X, triple, obj);
    uint32_t d = triple[0];
    uint32_t a = triple[1];
    uint32_t b = triple[2];
    uint32_t j_max = fmin((d - 1), (obj->L - 1));

    while (b >= obj->L)
      b = (b + a) % L_;

    set_entry(G_LT, i, b, 1);

    for (uint j = 1; j <= j_max; j++) {
      b = (b + a) % L_;

      while (b >= obj->L)
        b = (b + a) % L_;

      set_entry(G_LT, i, b, 1);
    }
  }
}

void r10_LTEnc(uint32_t X, uint32_t K, uint32_t *C, uint32_t triple[3],
               uint32_t G, Raptor10 obj) {
  uint32_t d[] = {0};
  uint32_t a[] = {0};
  uint32_t b[] = {0};

  for (size_t i = 0; i < K; i++) {
    uint32_t triple[3] = {0};
    r10_Trip(K, X + i, triple, &obj);
    d[i] = triple[0];
    a[i] = triple[1];
    b[i] = triple[2];
  }
}

int r10_build_constraints_mat(Raptor10 *obj, gf2matrix *A) {

  // build G_LDPC and G_Half submatrices
  r10_build_LDPC_submat(obj->K, obj->S, A);
  r10_build_Half_submat(obj->K, obj->S, obj->H, A);

  // build identity matrices
  for (int i = 0; i < obj->S; i++) {
    set_entry(A, i, obj->K + i, 1);
  }
  for (int i = 0; i < obj->H; i++) {
    set_entry(A, obj->S + i, obj->K + obj->S + i, 1);
  }

  // build the LT submatrix
  r10_build_LT_submat(obj->K, obj->S, obj->H, obj, A);

  // invert A
  gaussjordan_inv(A);

  return 0;
}

void r10_compute_params(Raptor10 *obj) {
  if (obj->Al == 0 && obj->K == 0 && obj->Kmax == 0 && obj->Kmin == 0 &&
      obj->Gmax == 0)
    return;

  uint32_t X = 2;
  while (X * (X - 1) < 2 * obj->K)
    X++;

  // S number of LDPC symbols
  obj->S = 1;
  while (obj->S < ceil(0.01 * obj->K) + X)
    obj->S++;

  obj->S++;

  // H number of Half symbols
  obj->H = 1;
  while (choose(obj->H, ceil(obj->H / 2)) < obj->K + obj->S)
    obj->H++;

  // L number of intermediate symbols
  obj->L = obj->K + obj->S + obj->H;
}

void r10_multiplication(Raptor10 *obj, gf2matrix *A, uint8_t *block,
                        uint8_t *res_block) {
  int beg = 0;
  for (uint j = 0; j < get_ncols(A); j++) {
    for (uint i = 0; i < get_nrows(A); i++) {
      if (get_entry(A, i, j)) {
        if (!beg)
          for (uint t = 0; t < obj->T; t++)
            res_block[i + t] = block[j + t];
        else
          for (uint t = 0; t < obj->T; t++)
            res_block[i + t] = res_block[i + t] ^ block[j + t];
      }
    }
  }
}

void r10_encode(uint8_t *src_s, uint8_t *enc_s, Raptor10 *obj, gf2matrix *A) {
  // Multiply constraints matrix with input block to obtain intermediate symbols
  uint8_t int_symbols[obj->L];
  r10_multiplication(obj, A, src_s, int_symbols);

  // Calculate the LT matrix and encoded symbols
  gf2matrix G_LT;
  allocate_gf2matrix(&G_LT, obj->L, obj->N);

  // Create vector of ESIs
  uint32_t ESIs[obj->N];
  for (uint32_t i = 0; i < obj->N; i++)
    ESIs[i] = i;

  // Build the LT matrix and encode
  r10_build_LT_mat(obj->N, obj, &G_LT, ESIs);
  r10_multiplication(obj, A, int_symbols, enc_s);
}

void r10_decode(uint8_t *enc_s, uint8_t *dec_s, Raptor10 *obj, gf2matrix *A,
                uint32_t N_, uint32_t *ESIs) {
  // Calculate intermediate symbols
  // Build constraint matrix

  // To check if r10_build_constraints_mat relies on a already defined N !!!!
  uint8_t int_symbols[obj->L];
  r10_multiplication(obj, A, enc_s, int_symbols);

  // Calculate the LT matrix and encoded symbols
  gf2matrix G_LT;
  allocate_gf2matrix(&G_LT, obj->L, obj->K);

  // Build the LT matrix and decode
  r10_build_LT_mat(obj->K, obj, &G_LT, ESIs);
  r10_multiplication(obj, A, int_symbols, enc_s);
}
