#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <libR10.h>
#include <math.h>
#include <cinttypes>
#include <bitset>
//#include <gsl/gsl_sf_bessel.h>

void print_matrix(uint8_t** mat, int k, int n)
{
  for (int i = 0; i < k; i++)
    {
      for(int j = 0; j < n; j++)
	{
	  std::cout << (unsigned)mat[i][j] << " ";
	}
      std::cout << std::endl;
    }
}

int main(int argc, char* argv[])
{
  std::cout << "This is a fucking library importation test." << std::endl;
  uint8_t  K = 10;
  uint64_t F = 2048; 
  uint8_t  W = 64;
  uint64_t P = 512;
  R10Encoder enc(K, F, W, P);
  std::cout <<"Here is K: " << (unsigned)enc.K << std::endl;
  enc.setS();
  std::cout <<"Here is S: " << (unsigned)enc.S << std::endl;
  enc.setH();
  std::cout <<"Here is H: " << (unsigned)enc.H << std::endl;
  std::cout << "Here is the encoding matrix:" << std::endl;
  print_matrix(enc.A, enc.L + K, enc.L + K);
  uint16_t d = 4;
  uint16_t a = 6;
  uint16_t b = 7;
  uint16_t t[3] = {d, a, b};

}
