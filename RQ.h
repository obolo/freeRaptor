/**
 * File containing the RQ class which duty is to manage the protocol entities
 * for the RaptorQ FEC correction scheme.
 *
 * @author Roberto Francescon
 * @brief Class RQ to manage RFC6330 (RaptorQ) protocol entities
 * @version 0.0.1
 */

class RQ
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
