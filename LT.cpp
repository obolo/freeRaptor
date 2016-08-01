#include "LT.h"

LTcodes::LTcodes(){}

LTcodes::~LTcodes(){}

Soliton::Soliton(int K)
{
  k = K;
}

Soliton::~Soliton(){}

int Soliton::degree()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> unif_dist(0, 1);
  float unif_rand = unif_dist(gen);
  int val = std::ceil(1./unif_rand);
  return (val < k) ?  val : 1;
}
