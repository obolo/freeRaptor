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


#include "raptor_encoder.h"
#include <math.h>


/**
 * Method to test the primeness of numbers.
 * Be careful! NOT EFFICIENT!
 */
bool is_prime(int n)
{
  for (int i = 2; i < n; i++)
    {
      if ((bool)(n % i))
	return false;
    }

  return true;
}

/**
 * Method used to obtain the numbers used in the partitioning
 * of the object in blocks and sub-blocks
 * @return array with four elements
 */
std::array<int, 4> partition(uint8_t I, uint8_t J)
{
  uint8_t IL = ceil(I/J);
  uint8_t IS = floor(I/J);
  uint8_t JL = I - (IS * J);
  uint8_t JS = J - JL;

  std::array<int, 4> result;
  result[0] = IL; result[1] = IS; result[2] = JL; result[3] = JS;

  return result;
}


/**
 * Just implementing the choose() function, basically a binomial.
 * @return number of choices for k elements in a set of n: bin(n, k)
 */
long int choose(long int n, long int k)
{
  if(n == 0)
    return 1;
  
  long int r = n; // first factorial: from n to n-k
  for (int i = n - 1; i > k; i--)
    {
      r = r * i;
    }

  long int s = n - k; // second factorial: from n - k to 1
  for (int i = n - k - 1; i > 0; i--)
    {
      s = s * i;
    }

  return (long int)(r/s);
}

/**
 * Method used to get a Gray sequence based on integer index i
 * @return integer wich is a Gray sequence comoared to previous and next one
 */
uint32_t gray_sequence(uint32_t i)
{
  return i ^ (uint32_t)floor((double)(i/2));
}

/**
 * Method to Hamming weight a GF(2) vector.
 * It basically counts how many 1 bits it has.
 */
int hamming_weight(uint32_t number)
{
  return __builtin_popcount(number);  
}

/**
 * Method for collecting N Gray sequences that weight exaclty k.
 * This clearly is a waste of memory but I did not find anything
 * smarter up to now. To Be Improved!
 * @return pointer to array of 32 bit uintegers
 */
uint32_t* collect_m(int k, int N)
{
  
  uint32_t* m = new uint32_t[N]();
  int n = 0;
  int i = 0;
  while(n < N)
    {
      if (hamming_weight(gray_sequence(i)) == k)
	{
	  m[n] = gray_sequence(i);
	  n++;
	}
      i++;
    }
  return m;
}

/**
 * Method used to generate the (d,a,b)-triple used in the encoding process
 * @return array with three elements
 */
std::array<int, 3> trip(uint8_t K, uint8_t i)
{
  std::array<int, 3> dab_triple;  
}

RaptorEncoder::RaptorEncoder(uint64_t F, uint8_t W, uint64_t P, uint8_t Al=4,
			     uint16_t Kmax=8192, uint16_t Kmin=1024, uint8_t Gmax=10)
{

  // Pointers to data

  uint8_t* C_ = new uint8_t[K](); // The K source symbols
  uint8_t*  C = new uint8_t[L](); // The L intermediate symbols
  uint8_t** A; // encoding matrix

  // Derive parameters

  uint64_t G = std::min(ceil(P*Kmin/F), std::min(P/Al, Gmax));

  T = floor(P/(Al*G))*Al; 

  uint64_t Kt = ceil(F/T);

  Z = ceil(Kt/Kmax);

  N = std::min( ceil(ceil(Kt/Z)*T/W), T/Al );

  // Partitioning and sub-partitioning  the blocks and the symbols

  std::array<int, 4> sub_block  = partition(Kt, Z);
  std::array<int, 4> sub_symbol = partition((T/Al), N);

  // Partiotioning of object

  uint8_t KL = sub_block[0];
  uint8_t KS = sub_block[1];
  uint8_t ZL = sub_block[2];
  uint8_t ZS = sub_block[3];

  // Sub-partitioning of blocks

  uint8_t TL = sub_symbol[0];
  uint8_t TS = sub_symbol[1];
  uint8_t NL = sub_symbol[2];
  uint8_t NS = sub_symbol[3];

  // Get the S LDPC symbols
  //uint8_t* LDPC_symbols = getLDPCSymbols(S, C);

  // Get the H Half symbols
  //uint8_t* half_symbols = getHalfSymbols(H, C);

  // Get the Repair symbols
  //uint8_t* repair_symbols = getRepairSymbols();

  // Compose packet
  //SBN + ESI + SourceSymbols + RepairSymbols
}

int RaptorEncoder::getS(int K)
{
  int X = (int)(sqrt(2*K));
  bool run = true;
  while(X*(X-1) < 2*K)
    {
      X = X + 1;	  
    }
  
  int S = ceil(ceil(0.01*K) + X);
  while(!is_prime(S))
    {
      S++;
    }
  
  return S;
  
}

int RaptorEncoder::getH(int K, int S)
{
  bool run = true;
  int h = floor((K+S)/4);
  while (choose(h, ceil(h/2)) < K+S)
    {
      h++;
    }
  return h;
}

uint8_t* RaptorEncoder::getLDPCSymbols(int S, uint8_t* C)
{
  // uint8_t* symbols = new uint8_t[S]();
  // uint8_t a;
  // uint8_t b;
  
  // for (int i = 0; i < K; i++)
  //   {
  //     a = 1 + ( floor((i/S) % (S - 1)) );
  //     b = i % S;
  //     C[K + b] = C[K + b] ^ C[i];
  //     b = (b + a) % S;
  //     C[K + b] = C[K + b] ^ C[i];
  //     b = (b + a) % S;
  //     C[K + b] = C[K + b] ^ C[i];
  //   }
  
}

uint8_t* RaptorEncoder::getHalfSymbols(int H, int S, uint8_t* C)
{

  // // Find H prime which I called H_
  // int H_ = ceil((double)H/2);
  // // Build the table cotaining the Gray words of weight H_
  // uint32_t* m = collect_m(H_, K+S);
  
  // // main loop for building the Half Symbols
  // int i = 0;
  // for (int h = 0; h < H;  h++)
  //   {
  //     for (int j = 0; j < K + S; j++)
  // 	{ 
  // 	  word = std::bitset<32>(m[j]);
  // 	  if ((bool)(word >> h) & 1))
  // 	    C[h+K+S] = C[h+K+S] ^ C[j];
  // 	}
  //   }
}


uint8_t* constraintMatrix(int K, int S, int H)
{
  uint8_t* A[K+S+H][K+S+H];

  // // Build the first part: LDPC part
  // // S rows / K + S + H columns
  // // Elaborate on the first ceil(K/S) circulant submatrices
  // for (int i = 0; i < ceil(K/S); i++)
  //   {
  //     for(int c = 0; c < S; c++)
  // 	{
  // 	  A[          0 + c][S+c] = 1;
  // 	  A[(  i+1) % S + c][S+c] = 1;
  // 	  A[(2*i+1) % S + c][S+c] = 1;
  // 	}
  //   }

  // // SxS identity matrix
  // uint8_t* I_S[S][S];
  // for (int i = 0; i < S; i++)
  //   {
  //     I_S[i][i] = 1;
  //   }

  // // HxH identity matrix
  // uint8_t* I_H = new uint8_t[H][H]();
  // for (int i = 0; i < S; i++)
  //   {
  //     I_H[i][i] = 1;
  //   }
  
}

void RaptorEncoder::encode(int K)
{
  int S = getS(K);
  
  int H = getH(K, S);
  
  uint8_t* C = new uint8_t[K+S+H]();
  
  // Apply getLDPCSymbols();
  uint8_t* C = getLDPCSymbols(S, C);
  
  // Apply getHalfSymbols();
  uint8_t* C = getHalfSymbols(H, S, C);

  // Encode
  
}
