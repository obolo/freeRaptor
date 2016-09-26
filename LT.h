// Copyright 2016 Roberto Francescon
// This file is part of freeRaptor.
//
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

#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <random>
#include <cmath>
#include <chrono>
#include <math.h>
#include <vector>


class EncSymbol
{

public:
  std::vector<int> neighbors;
  char data;
  
};

class Soliton
{
 public:
  /**
   * Constructor of the Soliton distribution class. Initilizes a Soliton
   * distribution.
   */
  Soliton(int K, double delta_, double c);
  /**
   * Destructor of the Soliton distribution class.
   */
  ~Soliton();
  /**
   * Function that selects a degree for LT code according to the Soliton
   * distribution.
   */
  int degree();
  /**
   * Function that initialize the Soliton distribution values
   */
  void initialize();
  /**
   * Function that computer the parameter R from c
   */
  void computeR(double c);
  /**
   * Function that computes the Cumulative Distribution Function from the 
   * Probability Density Function
   */
  void computeCDF();
  /**
   * Function to print out the PDF of the Robust Soliton
   */
  const std::vector<double> getPDF() const;
    /**
   * Function to print out the CDF of the Robust Soliton
   */
  const std::vector<double> getCDF() const;
  /**
   * Function that computes the vector of symbols to be
   * selected for encoding the current output symbol
   */
  std::vector<int> select_symbols(int deg);
  
 protected:
  int k;         /**< Size of the source block: number of source symbols  */
  double R;      /** Parameter of the Robust Soliton*/
  double delta_; /** Failure probability*/
  double c;      /** Second spike position parameter */
  std::vector<double> pdf;   /** Probability Density Function */
  std::vector<double> cdf;   /** Cumulative Distribution Function */

protected:
  std::mt19937 _engine; /**< Seed for the uniform distribution (Mersenne TE)*/
  std::uniform_real_distribution<double> _unif_dist; /**< Uniform distribution*/
  
};

class LTcodes
{
 public:
  /**
   * Constructor for the LTcodes class
   */
  LTcodes(int K, double delta_, double c_);
  /**
   * Destructor for the LTcodes class
   */
  ~LTcodes();
    /**
   * Encode using the Robust Soliton Distribution
   */
  EncSymbol encode_symbol();
  /**
   * Decode using Belief Propagation
   */
  void decode_symbol();
  /**
   * Method that assigns the filename for encoding
   */
  void set_filename(std::string fname);
  /**
   * Method to buffer a file to be encoded
   */
  char* buffer_data();

 protected:

  Soliton distribution; /** Robust Soliton Distribution object */
  std::string filename; /** Filename of the file under encoding process */

};

#endif
