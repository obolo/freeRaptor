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

/**
 * Implementation file for the Rcodec header
 *
 * @author Roberto Francescon
 * @brief Implementation file of the Rcodec header
 * @license: GNU GPLv3; see https://www.gnu.org/licenses/gpl.html
 */

#include "Rcodec.h"

Rcodec::Rcodec(){}

Rcodec::~Rcodec(){}

void Rcodec::encode()
{

  distribution.initialize(); // Basically compute PDF

  for (int k = 0; k < K; k++) // loop over the input symbols
    {
      int d = distribution.degree();
      // method to uniformly choose d input symbols
      // XOR over the input symbols
    }
}

void Rcodec::decode(){}
