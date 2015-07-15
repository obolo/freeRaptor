/* Header file for the Rcodec class which implements a Raptor object
 * which handle coding and decoding.
 * Encoder header for the freeRaptor project
 *
 * @author Roberto Francescon
 * @brief Encoder header
 */

#ifndef RAPTOR_H
#define RAPTOR_H

#include <iostream>
#include <cmath>

using namespace std;

class Rcodec{

 public:
  /**
   * Constructor for the class Rcodec
   */
  virtual Rcodec(int arch);
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
  
 protected:
  char* filename; //Filename helps to manage details
  int size_bit; //Maybe useful
  int size_byte; //Maybe useful
  int arch; //Necessary to determine the distribution to use
  
 private:

  
};

#endif
