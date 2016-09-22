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
 * Header file for the LT class which implements the Luby Tranform
 * or LT codes. All needed tools are impemeted, such as the 
 * Soliton and Robust Soliton distribution
 *
 * @author  Roberto Francescon
 * @brief   Implementation of basic LT codes
 * @version 0.0.1
 * @file    LT.h
 */

#ifndef LT_H
#define LT_H

#include <iostream>
#include <cmath>
#include <random>
#include <cmath>
#include <chrono>

class LTcodes
{
 public:
  /**
   * Constructor for the LTcodes class
   */
  LTcodes();
  /**
   * Destructor for the LTcodes class
   */
  ~LTcodes();
  /**
   * Decode using message passing
   */
  void decodeMP(char* enc_block);
};

class Soliton
{
 public:
  /**
   * Constructor of the Soliton distribution class. Initilizes a Soliton
   * distribution.
   */
  Soliton(int K);
  /**
   * Destructor of the Soliton distribution class.
   */
  ~Soliton();
  /**
   * Function that selects a degree for LT code according to the Soliton
   * distribution.
   */
  int degree();

  
  int k; /**< Size of the source block: number of source symbols  */

  // protected:
  std::mt19937 _engine; /**< Seed for the uniform distribution (Mersenne TE)*/
  std::uniform_real_distribution<double> _unif_dist; /**< Uniform distribution*/
  
};

#endif
