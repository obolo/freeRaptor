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
 * @file    libR10.h
 */

#ifndef LIBR10_H
#define LIBR10_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <gf2matrix.h>

// Definitions:
//
// ESI  Encoding Symbol ID
// LDPC Low Density Parity Check
// LT   Luby Transform
// SBN  Source Block Number
// SBL  Source Block Length


class R10Codec
{
  
 public:
  /**
   * Constructor for the R10Codec class
   * @param K integer number of input source symbols
   * @param N integer number of output encoding symbols  
   */
  R10Codec(int K, int N);
  /**
   * Destructor for the R10Codec class
   */
  ~R10Codec();
  /**
   * Method to print the generator matrix: used while
   * developing to check consistency. Possibly TBE!
   */
  void print_matrix();
  /**
   * Obtain the constraint matrix for debugging purposes: TBE!
   */
  GF2mat get_mat();

 protected:

  /**
   * Method used for obtaining the size S for the
   * LDPC symbols.
   */
  void setS();
  /**
   * Method used for obtaining the size H for the
   * Half symbols.
   */
  void setH();
  /**
   * Method used for generating a degree during the encoding process
   */
  uint32_t deg(uint16_t v);
  /**
   * Method to obtain the S LDPC intermediate symbols
   */
  void setLDPCSymbols();  
  /**
   * Method to obtain the H Half intermediate symbols.
   * Basically circulant matrices.
   */
  void setHalfSymbols();
  /**
   * Method for building the Constraint Matrix.
   * This is the upper part of matrix A and is built
   * once and hen saved for each value of K.
   */
  void constraintMatrix();
  /**
   * Method for setting the LT symbols in the precode matrix.
   * This is needed to make the code systematic.
   */
  void setLTSymbols();
  /**
   * Method for generating the triple that is used
   * to generate an encoding symbol
   */
  void trip(uint8_t X, uint32_t* triple);
  /**
   * Method for obtaining random values to be used in
   * the degree function and trip() function
   */
  uint32_t rand(uint16_t X, uint16_t i, uint16_t m);
  /**
   * Method used for the LT encoding process.
   */
  uint16_t LTEnc(uint16_t K, GF2mat C, uint16_t* triple);

  
  uint32_t V0[256] = {251291136, 3952231631, 3370958628, 4070167936, 123631495, 3351110283,
		      3218676425, 2011642291, 774603218, 2402805061, 1004366930,
		      1843948209, 428891132, 3746331984, 1591258008, 3067016507,
		      1433388735, 504005498, 2032657933, 3419319784, 2805686246,
		      3102436986, 3808671154, 2501582075, 3978944421, 246043949,
		      4016898363, 649743608, 1974987508, 2651273766, 2357956801, 689605112,
		      715807172, 2722736134, 191939188, 3535520147, 3277019569, 1470435941,
		      3763101702, 3232409631, 122701163, 3920852693, 782246947, 372121310,
		      2995604341, 2045698575, 2332962102, 4005368743, 218596347,
		      3415381967, 4207612806, 861117671, 3676575285, 2581671944,
		      3312220480, 681232419, 307306866, 4112503940, 1158111502, 709227802,
		      2724140433, 4201101115, 4215970289, 4048876515, 3031661061,
		      1909085522, 510985033, 1361682810, 129243379, 3142379587, 2569842483,
		      3033268270, 1658118006, 932109358, 1982290045, 2983082771,
		      3007670818, 3448104768, 683749698, 778296777, 1399125101, 1939403708,
		      1692176003, 3868299200, 1422476658, 593093658, 1878973865,
		      2526292949, 1591602827, 3986158854, 3964389521, 2695031039,
		      1942050155, 424618399, 1347204291, 2669179716, 2434425874,
		      2540801947, 1384069776, 4123580443, 1523670218, 2708475297,
		      1046771089, 2229796016, 1255426612, 4213663089, 1521339547,
		      3041843489, 420130494, 10677091, 515623176, 3457502702, 
		      2115821274,2720124766, 3242576090, 854310108, 425973987, 325832382, 1796851292,
		      2462744411, 1976681690, 1408671665, 1228817808, 3917210003,
		      263976645, 2593736473, 2471651269, 4291353919, 650792940, 1191583883,
		      3046561335, 2466530435, 2545983082, 969168436, 2019348792,
		      2268075521, 1169345068, 3250240009, 3963499681, 2560755113,
		      911182396, 760842409, 3569308693, 2687243553, 381854665, 2613828404,
		      2761078866, 1456668111, 883760091, 3294951678, 1604598575,
		      1985308198, 1014570543, 2724959607, 3062518035, 3115293053,
		      138853680, 4160398285, 3322241130, 2068983570, 2247491078,
		      3669524410, 1575146607, 828029864, 3732001371, 3422026452,
		      3370954177, 4006626915, 543812220, 1243116171, 3928372514,
		      2791443445, 4081325272, 2280435605, 885616073, 616452097, 3188863436,
		      2780382310, 2340014831, 1208439576, 258356309, 3837963200,
		      2075009450, 3214181212, 3303882142, 880813252, 1355575717, 207231484,
		      2420803184, 358923368, 1617557768, 3272161958, 1771154147,
		      2842106362, 1751209208, 1421030790, 658316681, 194065839, 3241510581,
		      38625260, 301875395, 4176141739, 297312930, 2137802113, 1502984205,
		      3669376622, 3728477036, 234652930, 2213589897, 2734638932,
		      1129721478, 3187422815, 2859178611, 3284308411, 3819792700,
		      3557526733, 451874476, 1740576081, 3592838701, 1709429513,
		      3702918379, 3533351328, 1641660745, 179350258, 2380520112,
		      3936163904, 3685256204, 3156252216, 1854258901, 2861641019,
		      3176611298, 834787554, 331353807, 517858103, 3010168884, 4012642001,
		      2217188075, 3756943137, 3077882590, 2054995199, 3081443129,
		      3895398812, 1141097543, 2376261053, 2626898255, 2554703076,
		      401233789, 1460049922, 678083952, 1064990737, 940909784, 1673396780,
		      528881783, 1712547446, 3629685652, 1358307511}; /**< V0 */

  uint32_t V1[256] = {807385413, 2043073223, 3336749796, 1302105833, 2278607931, 541015020,
		      1684564270, 372709334, 3508252125, 1768346005, 1270451292,
		      2603029534, 2049387273, 3891424859, 2152948345, 4114760273,
		      915180310, 3754787998, 700503826, 2131559305, 1308908630, 224437350,
		      4065424007, 3638665944, 1679385496, 3431345226, 1779595665,
		      3068494238, 1424062773, 1033448464, 4050396853, 3302235057,
		      420600373, 2868446243, 311689386, 259047959, 4057180909, 1575367248,
		      4151214153, 110249784, 3006865921, 4293710613, 3501256572, 998007483,
		      499288295, 1205710710, 2997199489, 640417429, 3044194711, 486690751,
		      2686640734, 2394526209, 2521660077, 49993987, 3843885867, 4201106668,
		      415906198, 19296841, 2402488407, 2137119134, 1744097284, 579965637,
		      2037662632, 852173610, 2681403713, 1047144830, 2982173936, 910285038,
		      4187576520, 2589870048, 989448887, 3292758024, 506322719, 176010738,
		      1865471968, 2619324712, 564829442, 1996870325, 339697593, 4071072948,
		      3618966336, 2111320126, 1093955153, 957978696, 892010560, 1854601078,
		      1873407527, 2498544695, 2694156259, 1927339682, 1650555729,
		      183933047, 3061444337, 2067387204, 228962564, 3904109414, 1595995433,
		      1780701372, 2463145963, 307281463, 3237929991, 3852995239,
		      2398693510, 3754138664, 522074127, 146352474, 4104915256, 3029415884,
		      3545667983, 332038910, 976628269, 3123492423, 3041418372, 2258059298,
		      2139377204, 3243642973, 3226247917, 3674004636, 2698992189,
		      3453843574, 1963216666, 3509855005, 2358481858, 747331248,
		      1957348676, 1097574450, 2435697214, 3870972145, 1888833893,
		      2914085525, 4161315584, 1273113343, 3269644828, 3681293816,
		      412536684, 1156034077, 3823026442, 1066971017, 3598330293,
		      1979273937, 2079029895, 1195045909, 1071986421, 2712821515,
		      3377754595, 2184151095, 750918864, 2585729879, 4249895712,
		      1832579367, 1192240192, 946734366, 31230688, 3174399083, 3549375728,
		      1642430184, 1904857554, 861877404, 3277825584, 4267074718,
		      3122860549, 666423581, 644189126, 226475395, 307789415, 1196105631,
		      3191691839, 782852669, 1608507813, 1847685900, 4069766876,
		      3931548641, 2526471011, 766865139, 2115084288, 4259411376,
		      3323683436, 568512177, 3736601419, 1800276898, 4012458395, 1823982,
		      27980198, 2023839966, 869505096, 431161506, 1024804023, 1853869307,
		      3393537983, 1500703614, 3019471560, 1351086955, 3096933631,
		      3034634988, 2544598006, 1230942551, 3362230798, 159984793, 491590373,
		      3993872886, 3681855622, 903593547, 3535062472, 1799803217, 772984149,
		      895863112, 1899036275, 4187322100, 101856048, 234650315, 3183125617,
		      3190039692, 525584357, 1286834489, 455810374, 1869181575, 922673938,
		      3877430102, 3422391938, 1414347295, 1971054608, 3061798054,
		      830555096, 2822905141, 167033190, 1079139428, 4210126723, 3593797804,
		      429192890, 372093950, 1779187770, 3312189287, 204349348, 452421568,
		      2800540462, 3733109044, 1235082423, 1765319556, 3174729780,
		      3762994475, 3171962488, 442160826, 198349622, 45942637, 1324086311,
		      2901868599, 678860040, 3812229107, 19936821, 1119590141, 3640121682,
		      3545931032, 2102949142, 2828208598, 3603378023, 4135048896}; /**< V1 */
  
  uint32_t f[8] = {0,10241,491582,712794,831695,948446,1032189,1048576}; /**< Degree distribution f
									    function */
  uint8_t  d[7] = {1,2,3,4,10,11,40}; /**< Degree distribution d function  */

  uint16_t* J; /**< Systematic Index */

  const uint16_t Q = 65521; /**< Largest prime number smaller than 2**16 */

  GF2mat* A; /**< Constraint matrix */
  GF2mat* G_LDPC; /**< LDPC part of the constraint matrix */
  GF2mat* G_Half; /**< Half part of the constraint matrix */
  
  int K; /**< Number of input source symbols*/
  int N; /**< Number of output encoding symbols for the first round*/
  
  int S;  /**< Number of intermediate LDPC symbols */
  int H;  /**< Number of intermediate HDPC symbols (Half Symbols) */
  int L;  /**< Number of intermediate symbols in the Intermediate Block */

  uint16_t T; /**< Encoding Symbol Length (bytes)*/
  uint16_t Z; /**< Number of Source Blocks*/
  uint64_t F; /**< Transfer length of the object (bytes)*/
  uint64_t P; /**< Payload size of each packet (bytes)*/
  uint8_t W;  /**< Target on the sub block size (bytes)*/
};


class R10Encoder : public R10Codec
{
  
 public:
  /**
   * Constructor for the R10Encoder class
   * @param K integer number of input source symbols
   * @param N integer number of output encoding symbols
   */
  R10Encoder(int K, int N);
  /**
   * Destructor for the R10Encoder class
   */
  ~R10Encoder();
  /**
   * Method for startin the decoder. It will stop when the stop command
   * is issued.
   */
  void start();
  /**
   * Method fr producing the intermediate symbols
   */
  void int_symbols();
  /**
   * Main method used for encoding.
   */
  void encode(int X);
  /**
   * Main method used for decoding.
   */
  void decode();

 protected:
  // Data used for keeping track of the stream
  uint16_t FECID; /**< Value for the FEC ID (1 as per IANA definition)*/
  uint16_t SBN; /**< Counter for the Source Block Number */
  uint16_t ESI; /**< Counter for the Encoding Symbol ID */
  uint16_t RESERVED; /**< Reserved field */

};


class R10Decoder : public R10Codec
{

 public:
  /**
   * Constructor for the R10Decoder class
   */
  R10Decoder(int K, int N);
  /**
   * Destructor for the R10Decoder class
   */
  ~R10Decoder();
  /**
   * Method for startin the decoder. It will stop when the stop command
   * is issued.
   */
  void start();
  /**
   * Main method used for encoding.
   */
  void encode();
  /**
   * Main method used for decoding.
   */
  void decode();

 protected:
  // Data used for keeping track of the stream
  uint16_t FECID; /**< Value for the FEC ID (1 as per IANA definition)*/
  uint16_t SBN; /**< Counter for the Source Block Number */
  uint16_t ESI; /**< Counter for the Encoding Symbol ID */
  uint16_t RESERVED; /**< Reserved field */

};

#endif
