/**
 * File containing the R10 class which duty is to manage the protocol entities
 * for the Raptor10 FEC correction scheme.
 *
 * @author Roberto Francescon
 * @brief Class R10 to manage RFC6330/RFC5053 (Raptor10) protocol entities
 * @version 0.0.1
 */

class R10
{

 public:

 protected:
  //CDP OTI(Object Transmission Information) parts definition
  char SBN;
  char ESI[3];
  unsigned F; //Transfer length (octets)
  unsigned T; //Symbol size (octets) > Multiple of Al <
  //Scheme-Specific Raptor OTI parts definition
  unsigned Z;  //8 bit:  Number of source blocks
  unsigned N;  //16 bit: Number of sub-blocks in each sourc block
  unsigned Al; //8 bit:  Symbol alignment parameter

};
