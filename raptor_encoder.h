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
 * @author  Roberto Francescon
 * @brief   Raptor (R10) Encoder header. Definition of fields for the Content Delivery Protocol
 *          described in RFC5053.
 * @version 0.0.1
 * @file    raptor_encoder.h
 */

#ifndef RAPTOR_ENCODER_H
#define RAPTOR_ENCODER_H


#include <iostream>
#include <array>
#include <bitset>
#include <algorithm>


// Definitions:
//
// ESI  Encoding Symbol ID
// LDPC Low Density Parity Check
// LT   Luby Transform
// SBN  Source Block Number
// SBL  Source Block Length


class RaptorEncoder
{

 public:
  /**
   * Constructor for the RaptorEncoder class
   * @param F integer transfer length of the object in bytes
   * @param W target size of the sub-blocks in bytes
   * @param P maximum payload size in bytes (multiple of Al)
   * @param Al integer symbol alignment parameter (default 4)
   * @param Kmax integer maximum number of source symbols (constant 8192)
   * @param Kmin integer minimum number of source symbols (default 1024)
   * @param Gmax integer maximum number of symbols within an encoding group (default 10)
   */
  RaptorEncoder(uint64_t F, uint8_t W, uint64_t P, uint8_t Al,
		uint16_t Kmax, uint16_t Kmin, uint8_t Gmax);
  /**
   * Destructor for the RaptorEncoder class
   */
  ~RaptorEncoder();
  

 protected:

  /**
   * Method used for generating a degree during the encoding process
   */
  int deg();
  /**
   * Method used for obtaining the size S for the
   * LDPC symbols.
   */
  int getS(int K);
  /**
   * Method used for obtaining the size H for the
   * Half symbols.
   */
  int getH(int K, int S);
  /**
   * Method to obtain the S LDPC intermediate symbols
   * @param S integer nuumber of LDPC intermediate symbols to generate
   * @param C char pointer to the K first intermediate symbols
   */
  uint8_t* getLDPCSymbols(int S, char* C);  
    /**
   * Method to obtain the H Half intermediate symbols
   * @param H integer nuumber of Half intermediate symbols to generate
   * @param C char pointer to the K first intermediate symbols
   */
  uint8_t* getHalfSymbols(int H, int S, char* C);
  /**
   * Method for building the Constraint Matrix.
   * This is the main block used for the encoding process.
   */
  uint8_t* constraintMatrix();
  /**
   * Main method used for encoding. Fuck you!
   * 
   */
  void encode();


  
  const uint16_t Q = 65521; /** Largest prime number smaller than 2**16 */
  
  uint16_t T; /** Encoding Symbol Length*/

  uint16_t Z; /** number of Source Blocks*/

  uint8_t N;  /** number of sub-Blocks*/

  uint8_t K;  /** Number of source symbols in a Source Block */

  uint8_t S;  /** Number of intermediate LDPC symbols */

  uint8_t H;  /** Number of intermediate HDPC symbols */

  uint8_t L;  /** Number of intermediate symbols in the Intermediate Block */

};


class LTEnc
{
 public:
  /**
   * Constructor for the LTEnc class
   */
  LTEnc(uint8_t K, uint8_t C, std::array<int, 3> triplet);
  /**
   * Destructor for the LTEnc class
   */
  ~LTEnc();
};

#endif
