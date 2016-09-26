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
//#include "Rcodec.h"
#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
#include <bitset>

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
  for(int i = 1; i < k; i++)
    {
      dist[i-1] = std::count(collect.begin(), collect.end(), i);
    }

  // Print the histograms
  std::cout << "\nHistogram of sampling: " << N << " times" << std::endl;
  for (int i = 0; i <= k; i++)
    {
      std::cout << dist[i]/((double)N) << ",";
    }
  std::cout << "\n";

  // Test the input symbols chooser
  int degg = distribution1.degree();
  std::vector<int> in_symbols;
  in_symbols = distribution1.select_symbols(degg);
  std::cout << "Here slected " << degg << " symbols: ";
  print_vector(in_symbols);

  // Test reading a file bit by bit
  std::string filename("text.txt");
  std::ifstream filestream(filename, std::ifstream::binary);
  //std::cout << "Bit representation: " << std::hex << filestream << std::endl;
  filestream.seekg(0, filestream.end);
  int length = filestream.tellg();
  char* buffer = new char[length];
  std::cout << "Length of file is: " << length << std::endl;
  filestream.seekg(0, filestream.beg);
  filestream.read(buffer, length);
  std::cout << std::bitset<32>(buffer[8]);
  std::cout << std::endl;

  // Test the XORing of chars
  char char1 = buffer[3];
  char char2 = buffer[8];
  std::cout << "First char:  " << std::bitset<8>(char1) << std::endl;
  std::cout << "Second char: " << std::bitset<8>(char2) << std::endl;
  char out_symbol;
  out_symbol = char1 ^ char2;
  std::cout << "Result char: " << std::bitset<8>(out_symbol) << std::endl;

}
