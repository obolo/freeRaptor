// Copyright 2016 Roberto Francescon
// This file is part of freeRaptor.
// freeRaptor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// freeRaptor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with freeRaptor.  If not, see <http://www.gnu.org/licenses/>.

#include "LT.h"

LTcodes::LTcodes(){}

LTcodes::~LTcodes(){}

void LTcodes::decodeMP(char* enc_block)
{
  //Find the one-neighbor symbols
  std::vector<int> one_neigh_list;
  for (int i = 0; i < block_size; i++)
    {

    }
}


Soliton::Soliton(int K)
: 
k(K), 
_unif_dist(0.0, 1.0),
_engine(std::chrono::system_clock::now().time_since_epoch().count())
{}

Soliton::~Soliton(){}

int Soliton::degree()
{
  float unif_rand = _unif_dist(_engine);
  int val = (int)std::ceil(1./unif_rand);
  return (val < k) ?  val : 1;
}
