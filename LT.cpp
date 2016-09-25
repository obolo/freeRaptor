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

#include "LT.h"

LTcodes::LTcodes(){}

LTcodes::~LTcodes(){}

Soliton::Soliton(int K, double delta_, double c_)
: 
k(K), 
_unif_dist(0.0, 1.0),
delta_(delta_),
c(c_),
_engine(std::chrono::system_clock::now().time_since_epoch().count())
{}

Soliton::~Soliton(){}

int Soliton::degree()
{
  //float unif_rand = _unif_dist(_engine);
  //int val = (int)std::ceil(1./unif_rand);
  //return (val < k) ?  val : 1;
  std::default_random_engine generator;
  std::discrete_distribution<int> distribution(pdf.begin(), pdf.end());

  return distribution(_engine);
  
}

void Soliton::initialize()
{
  // Compute R
  computeR(c);
  // Generation of the rho variable
  double rho[k];
  rho[0] = 1;
  for (int i = 2; i < k; i++)
    {
      rho[i-1] = 1/((double)i*(i-1));
    }
  // Generation of the tau variable
  double tau[k];
  for (int i = 1; i <= int(k/R) - 1; i++)
    {
      tau[i-1] = R/((double)i*k);
    }
  for (int i = int(k/R) + 1; i <= k; i++)
    {
      tau[i-1] = 0;
    }
  tau[int(k/R)-1] = R*(log(R/delta_)/k);

  // Sum everything to normalize
  double beta = 0;
  for(int i = 0; i < k; i++)
    {
      beta = beta + tau[i] + rho[i];
    }
  double mi[k];
  for (int i = 0; i < k; i++)
    {
      mi[i] = (rho[i] + tau[i])/beta;
      pdf.push_back((rho[i] + tau[i])/beta);
    }
}

void Soliton::computeR(double c)
{
  R = c*log(k / delta_) * sqrt(k);
}

void Soliton::computeCDF()
{
  cdf.push_back(pdf[0]);
  for (int i = 1; i < k; i++)
    {
      cdf.push_back(cdf[i-1] + pdf[i]);
    }
}

const std::vector<double> Soliton::getPDF() const
{
  return pdf;
}

const std::vector<double> Soliton::getCDF() const
{
  return cdf;
}
