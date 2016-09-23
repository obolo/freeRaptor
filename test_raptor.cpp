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

  std::cout << "Importing LT libraries test" << std::endl;

  const int K = 16; // input symbols

  const int N = 10000; // Number of random samples
  std::vector<int> collect; // Holdin' the values
  double dist[K]; // Holdin' tha histo of samples
  double exp_dist[K]; // Holdin' tha histo as thoery

  Soliton distribution(K, 0.01, 0.1);


  // ------------- Test of the Soliton distribution ----------------------
  // Sample the distribution
  for (int n = 0; n < N; n++)
    {
      collect.push_back(distribution.degree());
    }

  // Make the histogram
  for(int k = 0; k < K; k++)
    {
      dist[k] = std::count(collect.begin(), collect.end(), k);
      exp_dist[k] = (k == 1) ? 1/(double)K : 1./((double)k*((double)k-1.));
    }

  // Print the histograms
  std::cout << "Real:   ";
  for (int k = 1; k <= K; k++)
    {
      std::cout << dist[k]/((double)N) << " ";
    }
  std::cout << "\n";
  std::cout << "Expect: ";
  for (int k = 1; k <= K; k++)
    {
      std::cout << (double)exp_dist[k] << " ";
    }
  std::cout << "\n";

  //-------------------- Test of the Robust Soliton distribution --------------------

  // Compute R
  double c = 0.1;
  int k = 16;
  double delta_ = 0.01;
  double R = c*log(k / delta_) * sqrt(k);

  std::vector<double> pdf;

  std::cout << "Value of R is: " << R << std::endl;

  // Generation of the rho variable
  double rho[k];
  rho[0] = 1;
  for (int i = 2; i < k; i++)
    {
      rho[i-1] = 1/((double)i*(i-1));
    }
  // Generation of the tau variable
  double tau[k];
  for (int i = 1; i <= int(k/R) - 1; i++)
    {
      tau[i-1] = R/((double)i*k);
    }
  for (int i = int(k/R) + 1; i <= k; i++)
    {
      tau[i-1] = 0;
    }
  tau[int(k/R)-1] = R*(log(R/delta_)/k);

  // Sum everything to normalize
  double beta = 0;
  for(int i = 0; i < k; i++)
    {
      beta = beta + tau[i] + rho[i];
    }

  std::cout << "Beta is: " << beta << std::endl;
  double mi[k];
  for (int i = 0; i < k; i++)
    {
      mi[i] = (rho[i] + tau[i])/beta;
    }

  // Print the result
  std::cout << "Printing mi:" << std::endl;
  for (int i = 0; i < k; i++)
    {
      pdf.push_back(mi[i]);
      std::cout << mi[i] << "  ";
    }
  std::cout << std::endl;
  std::cout << "Second peak at: " << (int)(k/R) << std::endl;

  // Generate PDF with the class method
  distribution.initialize();
  std::vector<double> pdf1 = distribution.getPDF();

  for (int i = 0; i < k; i++)
    {
      std::cout << pdf1[i] << "  ";
    }
  std::cout << std::endl;

}
