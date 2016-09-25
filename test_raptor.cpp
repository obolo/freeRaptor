// Copyright 2016 Roberto Francescon
// This file is part of freeRaptor.
// freeRaptor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// freeRaptor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with freeRaptor.  If not, see <http://www.gnu.org/licenses/>.

#include "LT.h"
#include "Rcodec.h"
#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

/**
 * Function for promptly printing vectors of int
 */
void print_vector(std::vector<int> vec)
{
  for (int i = 0; i < vec.size(); i++)
    {
      std::cout << vec[i] << " ";
    }
  std::cout << std::endl;
}


int main(int argc, char* argv[])
{

  std::cout << "\nImporting LT libraries test" << std::endl;

  //-------------------- Test of the Robust Soliton distribution --------------------

  // Compute R
  double c = 0.03;
  int k = 128;
  double delta_ = 0.5;
  double R = c*log(k / delta_) * sqrt(k);

  Soliton distribution1(k, delta_, c);
  
  std::vector<double> pdf; // Probability Density Function
  std::vector<double> cdf; // Cumulative Distribution Function

  // Generate PDF with the class method and print it
  
  distribution1.initialize(); // Basivally compute PDF
  
  std::vector<double> pdf1 = distribution1.getPDF();
  std::cout << "\nRobust Soliton Distribution:" << std::endl;
  for (int i = 0; i < k; i++)
    {
      std::cout << pdf1[i] << ",";
    }
  std::cout << std::endl;

  // Generate and print class generated CDF for the RSoliton
  
  distribution1.computeCDF(); // Of course, compute CDF
  
  std::cout << "\nCumulative distribution Function of the Robust Soliton:" << std::endl;
  std::vector<double> cdf1 = distribution1.getCDF();
  for (int i = 0; i < cdf1.size(); i++)
    {
      std::cout << cdf1[i] << ",";
    }
  std::cout << std::endl;

  // Test drawing from the Robust Soliton

  const int N = 10000; // Number of random samples
  std::vector<int> collect; // Holdin' the values
  double dist[k]; // Holdin the distribution
  
  // Sample the distribution
  for (int n = 0; n < N; n++)
    {
      collect.push_back(distribution1.degree());
    }
  std::cout << std::endl;
  std::cout << "A sample: " << distribution1.degree() << std::endl;

  // Make the histogram
  for(int i = 0; i < k; i++)
    {
      dist[i] = std::count(collect.begin(), collect.end(), i);
    }

  // Print the histograms
  std::cout << "\nHistogram of sampling: " << N << " times" << std::endl;
  for (int i = 0; i <= k; i++)
    {
      std::cout << dist[i]/((double)N) << ",";
    }
  std::cout << "\n";

}
