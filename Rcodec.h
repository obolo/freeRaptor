// Encoder header for the freeRaptor project

// @author Roberto Francescon
// @brief Encoder header

#ifndef RAPTOR_H
#define RAPTOR_H

#include <iostream>
#include <cmath>

using namespace std;

class Rcodec{
  /**
   * Constructor for the class Rcodec
   */
  virtual Rcodec();
  /**
   * Destructor for the class Rcodec
   */
  ~Rcodec();
  /**
   * Method for the actual encoding of the data
   */
  virtual void encode();
    /**
   * Method for the decoding of the data
   */
  virtual void decode();
  
};

#endif
