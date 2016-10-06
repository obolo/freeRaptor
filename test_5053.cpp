#include <iostream>
#include <cstdio>
#include <stdio.h>
#include "raptor_encoder.h"
#include <math.h>
#include <cinttypes>
#include <bitset>
//#include <gsl/gsl_sf_bessel.h>

int choose(int n, int k)
{
  if(n == 0)
    return 1;
  
  int r = n;
  for (int i = n - 1; i > k; i--)
    {
      r = r * i;
    }

  int s = n - k;
  for (int i = n - k - 1; i > 0; i--)
    {
      s = s * i;
    }

  return (int)(r/s);
}


bool is_prime(int n)
{
  for (int i = 2; i < n; i++)
    {
      if (!(n % i))
	return false;
    }

  return true;
}

int getS(int K)
{
  int X = (int)(sqrt(2*K));
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

int getH(int K, int S)
{
  int h = 1;
  while (choose(h, ceil(h/2)) < K+S)
    {
      h++;
    }
  return h;
}

void print_matrix(uint8_t* mat, int k, int n)
{
  for (int i = 0; i < k; i++)
    {
      for(int j = 0; j < n; j++)
	{
	  std::cout << mat+i+j << " ";
	}
      std::cout << std::endl;
    }
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

int main(int argc, char* argv[])
{
  int S = 10;
  std::cout << "This is a fucking library importation test." << std::endl;
  // uint8_t* symbols = new uint8_t[S]();
  // symbols[0] = 6;
  // symbols[9] = 6;
  // for (int i = 0; i < S; i++)
  //   {
  //     std::cout << std::hex << symbols[i] << ",";
  //   }
  // std::cout << std::endl;
  int K = 256;
  //double c_ = sqrt(2*K);
  //uint8_t c  = (uint8_t)(sqrt(2*K));
  //std::printf("Here you have the number: %f \n", c_);
  //std::printf("Here you have the number: %+" PRIu8 "\n", c);
  // int X = (int)(sqrt(2*K));
  // bool run = true;
  // while(run)
  //   {
  //     if (X * (X - 1) >= 2*K)
  // 	run = false;
  //     else
  // 	X = X + 1;	  
  //   }
  // int S_ = (int)(ceil(0.01*K) + X);
  // std::cout << std::dec << "X is equal to " << X << " and S is " << S_ << std::endl;
  // int n = 6;
  // int k = ceil(n/2); 
  // std::cout << std::dec << "Binomial of ( "<<n<<" "<<k<< " ) is " << choose(n,k) << std::endl;
  int a = 4;
  int b = 6;
  int c = a ^ b;
  std::cout << "The result of XORing " << std::bitset<8>(a) << " and " << std::bitset<8>(b) << " is " << std::bitset<8>(c) << std::endl; 

  // Piece of code to test the Gray sequences picking with constant Hamming weight
  std::cout << "Testing Half symbols generation" << std::endl;
  uint32_t* m = collect_m(4, 6);
  for (int n = 0; n < 6; n++)
    {
      std::cout << m[n] << " " << std::bitset<32>(m[n]) << std::endl;
    }
  int K_ = 10;
  int S_ = getS(K_);
  std::cout << std::dec << "For K="<< K_ << "S is " << S_ << std::endl;
  int H = getH(K_, S_);
  std::cout << std::dec << "For K="<< K_ << " H is " << H << std::endl;

  //  uint8_t** A = new uint8_t[S_][10];
  uint8_t A[S_][10];

  // Build the first part: LDPC part
  // S rows / K + S + H columns
  // Elaborate on the first ceil(K/S) circulant submatrices
  // for (int i = 0; i < ceil(K/S); i++)
  //   {
  //     for(int c = 0; c < S; c++)
  // 	{
  // 	  A[          0 + c][S+c] = 1;
  // 	  A[(  i+1) % S + c][S+c] = 1;
  // 	  A[(2*i+1) % S + c][S+c] = 1;
  // 	}
  //   }
  //Test RaptorEncoder object generator
  RaptorEncoder enc(1024, 8, 1024);   
}
