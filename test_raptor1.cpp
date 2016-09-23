// Copyright 2016 Roberto Francescon
//
// This file is part of freeRaptor.
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
 * Function to promptly print the element of a vector container
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

  char a = 0xa;
  char b = 0xf;
  std::cout << "Result of xoring chars: " << 0xa << " and " << 0xb <<" is " <<  0xa^0xb << std::endl;
  
  std::cout << "Test algorithm Fountain Code LT" << std::endl;

  int K = 6;
  int N = 7;

  std::vector<EncSymbol> enc_symbols;
  std::vector<DecSymbol> dec_symbols;

  // Form an encoded packet
  for (int n = 0; n < N; n++)
    {
      EncSymbol enc_sym;
      enc_symbols.push_back(enc_sym);
    }
  enc_symbols[0].value = 1;
  enc_symbols[1].value = 1;
  enc_symbols[2].value = 0;
  enc_symbols[3].value = 1;
  enc_symbols[4].value = 0;
  enc_symbols[5].value = 0;
  enc_symbols[6].value = 1;
 
  // Form a wannabe decoded packet
  for (int n = 0; n < N; n++)
    {
      DecSymbol dec_sym;
      dec_sym.value = -1;
      dec_symbols.push_back(dec_sym);
    }
  
  // filling up the example
  int settings[N][K];
  settings[0][0] = 2; settings[0][1] = 4;  settings[0][2] = 5;  settings[0][3] = -1; settings[0][4] = -1; settings[0][5] = -1;
  settings[1][0] = 0; settings[1][1] = 1;  settings[1][2] = 2;  settings[1][3] = -1; settings[1][4] = -1; settings[1][5] = -1;
  settings[2][0] = 0; settings[2][1] = 3;  settings[2][2] = -1; settings[2][3] = -1; settings[2][4] = -1; settings[2][5] = -1;
  settings[3][0] = 2; settings[3][1] = -1; settings[3][2] = -1; settings[3][3] = -1; settings[3][4] = -1; settings[3][5] = -1;
  settings[4][0] = 0; settings[4][1] = 5;  settings[4][2] = -1; settings[4][3] = -1; settings[4][4] = -1; settings[4][5] = -1;
  settings[5][0] = 2; settings[5][1] = 5;  settings[5][2] = -1; settings[5][3] = -1; settings[5][4] = -1; settings[5][5] = -1;
  settings[6][0] = 1; settings[6][1] = 3;  settings[6][2] = 4;  settings[6][3] = 5;  settings[6][4] = -1; settings[6][5] = -1;


  // Generate encoded symbols/packets containers
  for (int i = 0; i < N; i++)
    {
 
      for (int j = 0; j < K; j++)
	
  	{
  	  if (settings[i][j] != -1)
  	    {
  	      enc_symbols[i].neighbors.push_back(settings[i][j]);
  	    }
  	}      
    }

  
  // Receiving packets: form the digraph that will be use in the belief propagation process
  for (int n = 0; n < N; n++)
    {
      int n_neigh = enc_symbols[n].neighbors.size();
  
      for (int i = 0; i < n_neigh; i++)
      	{
      	  int n_dec_pck = enc_symbols[n].neighbors[i];
      	  dec_symbols[n_dec_pck].neighbors.push_back(n);
      	}
    }

  // Belief propagation algorithm
  
  int count = 0;        // check if algo needs to be run again
  bool run_flag = true; // check if algo need to be run again
  int counter = 0;      // just count how many times we run the algo
 
  //Main loop that implements the belief propagation algorithm (LT codes)
    while (run_flag)
    {
      // step 1: find encoded symbol of degree 1
      // This cleraly depends of how a symbol is recognized to have 1 neighbor
      bool flag = false;
      int index;
      for (int i = 0; i < N; i++)
	{
	  if (enc_symbols[i].neighbors.size() == 1 && enc_symbols[i].value != -1)
	    {
	      flag = true;
	      index = i;
	    }
	}
      if (flag == false)	
	{
	  std::cout << "Stopped: no one-neighbor node found and undecoded symbols left" << std::endl;
	  return 1;
	}      
      else //true	
	{

	  // Step 2: decode the unique neighbor of this symbol with the value of the encoded symbol itself
	  dec_symbols[enc_symbols[index].neighbors[0]].value = enc_symbols[index].value;
	  std::cout << "Assigned value: " << dec_symbols[enc_symbols[index].neighbors[0]].value;
	  std::cout << " to node " << enc_symbols[index].neighbors[0] << std::endl;

	  enc_symbols[index].value = -1;
	  
	  // handmade search by value (beacuse C++11 apparently is evil)
	  int ind = std::find(dec_symbols[enc_symbols[index].neighbors[0]].neighbors.begin(),
			      dec_symbols[enc_symbols[index].neighbors[0]].neighbors.end(), index)
	    - dec_symbols[enc_symbols[index].neighbors[0]].neighbors.begin();
	  // int ind = 0;
	  // for (int i = 0; i < dec_symbols[enc_symbols[index].neighbors[0]].neighbors.size(); i++)
	  //   {
	  //     if (dec_symbols[enc_symbols[index].neighbors[0]].neighbors[i] == index)
	  // 	ind = i;
	  //   }
	  // erase link in the dec_symbol neighbors list
	  dec_symbols[enc_symbols[index].neighbors[0]].neighbors.erase(dec_symbols[enc_symbols[index].neighbors[0]].neighbors.begin() + ind);
      
	  // Step 3: this just decoded symbol have, of course, other neighbors: do a XOR of the
	  //         newly assigned value with them and erase neighs correspondigly
	  std::vector<int> neighs = dec_symbols[enc_symbols[index].neighbors[0]].neighbors;
	  int n_n = neighs.size();
	  for (int i = 0; i < n_n; i++)
	    {
	      enc_symbols[neighs[i]].value = (int)( (bool)enc_symbols[neighs[i]].value ^ (bool)enc_symbols[index].value ); //XOR
              // erase links from decoded packet (both at enc_symbols and dec_symbols)
	      int p_ind = std::find(enc_symbols[neighs[i]].neighbors.begin(), enc_symbols[neighs[i]].neighbors.end(), enc_symbols[index].neighbors[0]) - enc_symbols[neighs[i]].neighbors.begin();
	      std:: cout << "Looking in enc symbol: " << neighs[i] << " :: ";
	      print_vector(enc_symbols[neighs[i]].neighbors);
	      std::cout << "Indexxx: " << p_ind << " Node searching for: "<< enc_symbols[index].neighbors[0] << std::endl;
	      enc_symbols[neighs[i]].neighbors.erase(enc_symbols[neighs[i]].neighbors.begin() + p_ind);
	    }

	  // erase link in the enc_symbol neighbors list
	  // std::cout << "Erasing node " << index << std::endl;
	  // enc_symbols[index].neighbors.erase(enc_symbols[index].neighbors.begin() + 1);

	  
	  // Step 4: if there are unrecovered symbols, stop: you won! Else, got to Step 1.
	  count = 0;
	  for (int n = 0; n < N; n++)
	    {
	      if (dec_symbols[n].value != -1)
	       {
		 count++;
	       }
	    }
	  if (count == K)
	    run_flag = false;

	  counter++;
	  std::cout << "Counts: " << count;
	  std::cout << " Counter: " << counter << std::endl;
	}
    }

  // print decoded values
  std::cout << "Decoded symbols: ";
  for (int k = 0; k < K; k++)
    {
      std::cout << dec_symbols[k].value;
    }
  std::cout << std::endl;

  // print received encoded symbols to check if they were properly processed
  std::cout << "Received encoded symbols: ";
  for (int n = 0; n < N; n++)
    {
      std::cout << enc_symbols[n].value;
    }
  std::cout << std::endl;
  
}
