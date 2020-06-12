# ![image](free_raptor60.png) freeRaptor

## A free and open (GPLv3) implementation of Raptor codes

The effort was made towards building a free and open piece of software that implements the Raptor codes:
because the project originated from a telecommunication setting, complying to a standard looked
like a good idea, thus the RFC 5053 was chosen as reference. The software is built as a
library to include in your source code.

The first version of this software implements the RFC 5053 also called Raptor10, or R10, with the following features:
- binary representation is made trough packed words of 32 bits each;
- because of the previous, matrix inversion is done through GE instead of Inactivation Decoding;
- about the remaining points, an effort was made to stick to the RFC.

### Raptor 10

The standard defines the packet fields along with the ranges of the parameters to be supported.
The following definitions are used throughout the code:
- K: integer number of source symbols in a single source block (8-8192)
- T: integer number of bytes that makes up a symbol (4-1024)
- N: integer number of encoding symbols coming out from the encoder;
     being the code systematic, we have N-K repair symbols

The basic structure of the encoder includes:
1. the calculation of L intermediate symbols from the K source symbols, where:
   - L = S + H
   - S is the number of LDPC constraints
   - H is the number of HDPC constraints (or Half symbols constraints)

2. the calculation of the N-K repair symbols from the L intermediate symbols via the LTEnc() function.
   LTEnc is described in [1].

While the decoder includes:
1. calculation of the L intermediate symbol from the received set of encoding symbols
2. calculation of the missing source symbols by means of the intermediate symbols

## License

This software is licensed under the GPLv3 license, making it free for everyone tu use, examine, improve and modify: see <http://www.gnu.org/licenses/>.

### References

[1] RFC5053, M. Luby, A. Shokrollahi, M. Watson, T. Stockhammer, IETF Standards Track, Oct. 2007

[2] Raptor Codes, A. Shokrollahi and M. Luby, Book in Foundations and Trends in Communications and Information Theory, January 2011
