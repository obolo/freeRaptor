/**
 * Header file for the Rcodec class which implements a RaptorQ object
 * which handle coding and decoding.
 * Encoder header for the freeRaptor project.
 *
 * @author Roberto Francescon
 * @brief Encoder header
 * @version 0.0.1
 */

#ifndef RAPTOR_H
#define RAPTOR_H

#include <iostream>
#include <cmath>

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

#endif
