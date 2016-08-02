#include "LT.h"

LTcodes::LTcodes(){}

LTcodes::~LTcodes(){}

void LTcodes::decodeMP(char* enc_block)
{
  //Find the one-neighbor symbols
  std::vector<int> one_neigh_list;
  for (int i = 0; i < block_size; i++)
    {

    }
}


Soliton::Soliton(int K)
: 
k(K), 
_unif_dist(0.0, 1.0),
_engine(std::chrono::system_clock::now().time_since_epoch().count())
{}

Soliton::~Soliton(){}

int Soliton::degree()
{
  float unif_rand = _unif_dist(_engine);
  int val = (int)std::ceil(1./unif_rand);
  return (val < k) ?  val : 1;
}
