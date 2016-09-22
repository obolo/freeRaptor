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

Soliton::Soliton(int K)
{
  k = K;
}

Soliton::~Soliton(){}

int Soliton::degree()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> unif_dist(0, 1);
  float unif_rand = unif_dist(gen);
  int val = std::ceil(1./unif_rand);
  return (val < k) ?  val : 1;
}
