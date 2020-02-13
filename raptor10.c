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

#include <math.h>
#include <stdint.h>
#include <raptor10.h>

void
generate_gray_seq(uint32_t* gray_seq)
{
  for (uint32_t i = 0; i <= 1000; i++)
   {
     gray_seq[i] = i ^ (uint32_t)(floor(i/2));
   }
}

int
factorial(int n)
{
  if (n == 0)
    return 1;
  else
    return n*factorial(n-1);
}

int is_prime(uint16_t n)
{
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

int
choose(int i, int j)
{
  return (factorial(i))/(factorial(j)*factorial(i-j));
}

void
Trip(uint16_t K, uint16_t X, uint16_t triple[3])
{
  uint16_t L = K + S + H;
  uint16_t L_ = L;
  while (!is_prime(L_)) {
	  L_++;
  }
  
  uint16_t Q = 65521;
  uint16_t A = (53591 + J[K]*997) % Q;
  uint16_t B = 10267 * (J[K]+1) % Q;
  uint16_t Y = (B + X*A) % Q;
  uint16_t v = Rand(Y, 0, 2^(20));
  uint16_t d = Deg(v);
  uint16_t a = 1 + Rand(Y, 1, L_-1);
  uint16_t b = Rand(Y, 2, L_);

  triple[0] = d;
  triple[1] = a;
  triple[2] = b;
}

uint16_t
Rand(uint16_t X, uint16_t i, uint16_t m)
{
	return (V0[(X + i)] % 256 ^ V1[(uint16_t)(floor(X / 256) + i) % 256]) % m;
}

uint16_t
Deg(int v)
{
  if (v < 0 || v > 1048576)
    return -1; // invalid

  if (v == 0) {
    return 0;
  } else if (v >= 0 && v < 10241) {
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

int
build_LDPC_mat(int K, int S, uint8_t C[K])
{
  int a = 0;
  int b = 0;

  for (int i = 0; i < K; i++)
    {
      a = 1 + ((int)floor(i/S) % (S-1));
      b = i % S;
      C[K+b] = C[K+b] ^ C[i];
      b = (b + a) % S;
      C[K+b] = C[K+b] ^ C[i];
      b = (b + a) % S;
      C[K+b] = C[K+b] ^ C[i];
    }
}

int
build_Half_mat(int K, int H, int S, uint8_t C[K])
{
  uint32_t* g = malloc(sizeof(uint32_t));
  generate_gray_seq(g);

  for (int h = 0; h < H; h++)
    {
      for (int j = 0; j < K+S; j++)
        {
          /* if () */
          /*   { */
          /*     enc->C[h + enc->K + enc->S] = */
          /*       enc->C[h + enc->K + enc->S]; ^ enc->C[j]; */
          /*   } */
        }
    }
}

void
LTEnc(uint16_t X, uint16_t K, uint16_t* C, uint16_t triple[3], uint16_t G)
{
  uint16_t d[] = {0};
  uint16_t a[] = {0};
  uint16_t b[] = {0};

  for (size_t i = 0; i < K; i++) {
    uint16_t triple[3] = {0};
    Trip(K, X+i, triple);
    d[i] = triple[0];
    a[i] = triple[1];
    b[i] = triple[2];
  }
}

int
build_constraints_mat(uint16_t K, uint16_t S, uint16_t L, R10* enc)
{
  /* gf2matrix G_LDPC; */
  uint8_t G_LDPC[K];
  build_LDPC_mat(K, S, G_LDPC);

  gf2matrix G_Half;
  // build_Half_mat(&G_Half);

  gf2matrix G_LT;
  // build_LT_mat(&G_LT);
  
  gf2matrix I_S;
  allocate_gf2matrix(&I_S, S, S);
  gf2matrix Z;
  allocate_gf2matrix(&Z, H, S);
  gf2matrix I_H;
  allocate_gf2matrix(&I_H, H, H);

  gf2matrix A;
  allocate_gf2matrix(&A, L, L);

  // Compose A matrix by sticking together all the previously defined matrices

  // INVERT A
  
}
