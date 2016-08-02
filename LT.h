// License: GNU GPLv3. See https://www.gnu.org/licenses/gpl.html

/**
 * Header file for the LT class which implements the Luby Tranform
 * or LT codes. All needed tools are impemeted such as the 
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
