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

  enc.print_matrix();
  

}
