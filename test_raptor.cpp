#include "LT.h"
#include "Rcodec.h"
#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
  std::cout << "Test importazione librerie Raptor" << std::endl;
  Soliton soliton_dist (10);
  Rcodec codec();
  std::cout << "Number of source pcks (K): " << soliton_dist.k << std::endl;
  std::cout << "Output of sampling Soliton: " << soliton_dist.degree() << std::endl;


  int N_test = 100000;
  std::vector<int> collect;
  for (int i = 0; i < N_test; i++)
    {
      collect.push_back(soliton_dist.degree());
    }
  
  double dist[soliton_dist.k];
  double exp_dist[soliton_dist.k];
  for (int k = 1; k <= soliton_dist.k; k++)
    {
      dist[k] = std::count(collect.begin(), collect.end(), k);
      exp_dist[k] = (k == 1) ? 1/(double)soliton_dist.k : 1./((double)k*((double)k-1.));
    }
  for (int k = 1; k <= soliton_dist.k; k++)
    {
      std::cout << dist[k]/((double)N_test) << " ";
    }
  std::cout << "\n";
    for (int k = 1; k <= soliton_dist.k; k++)
    {
      std::cout << (double)exp_dist[k] << " ";
    }
  std::cout << "\n";
  
}
