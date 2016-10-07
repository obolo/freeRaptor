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

#include <libR10.h>

// utility methods
/**
 * Verify if int number is prime.
 */
bool is_prime(int n)
{
  for (int i = 2; i < n; i++)
    {
      if (!(n % i))
	return false;
    }

  return true;
}

/**
 * Binomial coefficient.
 */
int choose(int n, int k)
{
  if(n == 0)
    return 1;
  
  int r = n;
  for (int i = n-1; i > k; i--)
    {
      r = r * i;
    }

  int s = n - k;
  for (int i = n-k - 1; i > 0; i--)
    {
      s = s * i;
    }

  return (int)(r/s);
}

/**
 * Method to Hamming weight a GF(2) vector.
 * It basically counts how many 1 bits it has.
 */
int hamming_weight(uint32_t number)
{
  return __builtin_popcount(number);  
}

/**
 * Method used to get a Gray sequence based on integer index i
 * @return integer wich is a Gray sequence comoared to previous and next one
 */
uint32_t gray_sequence(uint32_t i)
{
  return i ^ (uint32_t)floor((double)(i/2));
}

/**
 * Method for collecting N specular Gray sequences that weight exaclty k.
 * This clearly is a waste of memory but I did not find anything
 * smarter up to now. To Be Improved!
 * @return pointer to array of 32 bit uintegers
 */
uint32_t* collect_m(int k, int N)
{
  
  uint32_t* m = new uint32_t[N]();
  int n = 0;
  int i = 0;
  while(n < N)
    {
      if (hamming_weight(gray_sequence(i)) == k)
	{
	  m[n] = gray_sequence(i);
	  n++;
	}
      i++;
    }
  return m;
}



R10Encoder::R10Encoder(uint8_t K_, uint64_t F_, uint8_t W_, uint64_t P_, uint8_t Al,
		       uint16_t Kmax, uint16_t Kmin, uint8_t Gmax)
  :
  K(K_),
  F(F_),
  W(W_),
  P(P_),
  S(0),
  H(0),
  T(8)
{
  setS();
  setH();

  // initialize the encoding matrix
  A = new uint8_t*[L+K];
  for(int i = 0; i < L+K; ++i)
    A[i] = new uint8_t[L+K]();

  // obtain the constraint matrix
  constraintMatrix();

  // read Systematic index
  uint16_t count = 0;
  J = new uint16_t[8189];
  std::ifstream read_systematic("systematic.dat");
  std::string line;
  while(getline(read_systematic, line))
    {
      std::istringstream iss(line);
      uint16_t val;
      while (iss >> val)
	{
	  J[count] = val;
	  count++;
	}
    }
}

R10Encoder::~R10Encoder(){}


void R10Encoder::setS()
{
  int X = (int)(sqrt(2*K));
  while(X*(X-1) < 2*K)
    {
      X = X + 1;	  
    }
  
  S = (uint8_t)ceil(ceil(0.01*K) + X);
  while(!is_prime(S))
    {
      S++;
    }
}


void R10Encoder::setH()
{
  int h = 1;
  while (choose(h, ceil(h/2)) < K+S)
    {
      h++;
    }
  H = h;
  L = S + H; // given that we have S and also H initilize also L
}

void R10Encoder::setLDPCSymbols()
{
  assert(S != 0);

  // Do the first floor(K/S) circulant submatrices
  for (int i = 0; i < floor(K/S); i++)
    {
      int i1 = 0;
      int i2 = (i   + 1) % S;
      int i3 = (2*(i + 1)) % S;
      for (int c = 0; c < S; c++)
	{
	  A[(i1+c)%S][c+S*i] = 1;
	  A[(i2+c)%S][c+S*i] = 1;
	  A[(i3+c)%S][c+S*i] = 1;
	}
    }
  // Do the last circulant matrix
  {
    int i = floor(K/S);
    int i1 = 0;
    int i2 = (i   + 1) % S;
    int i3 = (2*(i + 1)) % S;
    for (int c = 0; c < K%S; c++)
      {
	A[(i1+c)%S][c+S*i] = 1;
	A[(i2+c)%S][c+S*i] = 1;
	A[(i3+c)%S][c+S*i] = 1;
      }
  }
  // Now fill the SxS identity matrix
  for (int i = 0; i < S; i++)
    {
      A[i][K+i] = 1;
    }
}

void R10Encoder::setHalfSymbols()
{
  // Obtain what is called H prime in the RFC
  uint8_t H_ = ceil((double)H/2);
  // Collect the first K+S specular gray sequences of weight H_
  uint32_t* m = collect_m(H_, K+S);
  for(int c = 0; c < K+S; c++)
    {
      uint8_t number = m[c];
      for(int b = 0; b < H; b++)
	{
           A[b+S][c] = ((number >> b) & 1);
	}
    }

  // Now fill the SxS identity matrix
  for (int i = 0; i < H; i++)
    {
      A[i+S][i+K+S] = 1;
    }  
}

void R10Encoder::constraintMatrix()
{
  setLDPCSymbols();
  setHalfSymbols();
}

uint32_t R10Encoder::deg(uint16_t v)
{
  int ind = 0;
  for (int i = 0; i < 8; i++)
    {
      if (v < f[i])
	ind = i;
    }
  return d[ind];
}

uint32_t R10Encoder::rand(uint16_t X, uint16_t i, uint16_t m)
{
  return ( (uint32_t)V0[ (X+i) % 256 ] ^ (uint32_t)V1[ (uint32_t)(floor(X/256)+1) % 256 ] ) % m;
}

void R10Encoder::trip(uint8_t X, uint16_t* triple)
{
  uint8_t L_ = L;
  while(!is_prime(L_))
    L_ = L_++;
  uint8_t J_ = J[K];

  uint16_t A_ = (53591 + J_*997) % Q;
  uint16_t B_ = 10267*(J_+1) % Q;
  uint16_t Y_ = (B_ + X*A_) % Q;
  uint16_t v = rand(Y_, 0, 2^20);

  triple[0] = deg(v);                // d
  triple[1] = 1 + rand(Y_, 1, L_-1); // a
  triple[2] = rand(Y_, 2, L_);       // b
}

uint16_t R10Encoder::LTEnc(uint16_t K, uint8_t* C, uint16_t* triple)
{
  uint8_t L_ = L;
  while(!is_prime(L_))
    L_ = L_++;
  uint16_t d = triple[0];
  uint16_t a = triple[1];
  uint16_t b = triple[2];

  while (b >= L)
    b = (b + a) % L_;

  uint16_t result = C[b];

  uint16_t cond = std::min(d-1, L-1);
  for (int j = 1; j < cond; j++)
    {
      b = (b + a) % L_;
      while (b >= L)
	{
	  b = (b + a) % L_;
	}
      result = (uint16_t)result ^ (uint16_t)C[b];
    }
  return result;
}

void R10Encoder::reordering()
{
  int i = 0;
  int u = 0;
  uint8_t* V;

  
}
