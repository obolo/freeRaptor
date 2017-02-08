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

  //std::cout << "Original constraint matrix:" << "\n";
  //enc.print_matrix();
  
  enc.encode(3);

  GF2mat B = enc.get_mat();

  //std::cout << "Inverted through GE:" << "\n";
  //enc.print_matrix();

  std::cout << "Copy-constructed inverted:" << "\n";
  B.print();

  int info[K] = {0,1,0,1,0,1,0,1,1,1};
  GF2mat d(23, 1);
  for (int n=0; n<K; n++)
    d.set_entry(n+K+3, 0, info[n]);

  GF2mat c = B*d;

  std::cout << "Here the input vector:" << "\n";
  d.print();
  std::cout << "Here the Intermediate symbols:\n";
  c.print();
  
  
  return 0;
  
}
