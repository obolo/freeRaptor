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
 * Header file for the Rcodec class which implements a RaptorQ object
 * which handle coding and decoding.
 * Encoder header for the freeRaptor project.
 *
 * @author  Roberto Francescon
 * @brief   Encoder header
 * @version 0.0.1
 * @file    Rcodec.h
 */

#ifndef RAPTOR_H
#define RAPTOR_H

#include <iostream>
#include <cmath>
#include <vector>

class Rcodec
{

 public:
  /**
   * Constructor for the Rcodec class
   */
  Rcodec();
  /**
   * Destructor for the Rcodec class
   */
  ~Rcodec();
  /**
   * Method for the actual encoding of the data
   */
  void encode();
  /**
   * Method for the decoding of the data
   */
  void decode();

 protected:

  char* filename; /**< Filename helps to manage details */
  int size_bit;   /**< Maybe useful */
  int size_byte;  /**< Maybe useful */
  int arch;       /**< Necessary to determine the distribution to use */
  
};

class EncSymbol
{

 public:
  std::vector<int> neighbors;
  int value;
  
};

class DecSymbol
{

 public:
  std::vector<int> neighbors;
  int value;
  
};

#endif
