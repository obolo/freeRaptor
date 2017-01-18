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

GF2mat::GF2mat(int n_rows, int n_cols)
  :n_row(n_rows),n_col(n_cols)
{
  gf2mat = calloc(n_col, sizeof );
}

GF2mat::~GF2mat(){}

int GF2mat::get_nrows()
{
  return n_row;
}

int GF2mat::get_ncols()
{
  return n_col;
}

int GF2mat::get_entry(int row, int col)
{
  return cols[col]  (word >> n) & 1;
}

void GF2mat::set_entry(){}
