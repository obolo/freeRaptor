#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <math.h>

#include <gf2matrix.h>
#include <libR10.h>

int main(int argc, char* argv[])
{
  std::cout << "Test for the libR10 library." << "\n" << "\n";
  int K = 10;
  int N = 15;
  
  R10Encoder enc(K, N); // R10Encoder object example

  std::cout << "Original constraint matrix:" << "\n";
  enc.print_matrix();

  enc.decode();

  std::cout << "Inverted through GE:" << "\n";
  enc.print_matrix();
  
  return 0;
  
}
