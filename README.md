# freeRaptor

## A free and open (GPLv3) implementation of Raptor codes written in C++.

The effort was made towards building a free and open piece of software implementing Rator codes: because the project originated from a telecommunication setting, complying to a standard looked like a good idea and so the RFC 5053 was chose as reference. the software is built as a static library to include in your source code to use its objects.

The first version of this software implement the RFC 5053 also called Raptor10 or R10, with the following features:
- binary representation is made trough packed words of 32 bits each;
- because of the previous, matrix inversion is done through GE instead of Inactivation Decoding;
- about the remaining points, an effort was made to stick to the RFC.

There exists the will to implement also the RFC 6330, also referred to by RaptorQ or RQ, but this is left to future work.

The software is under GPLv3 license, making it free for everyone tu use, improve and modify: see <http://www.gnu.org/licenses/>.
