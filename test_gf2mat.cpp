/** All hope is gone */

#include <iostream>
#include <string>
#include <gf2matrix.h>

int main(int argc, char* argv[])
{
  GF2mat A(6,7);
  std::cout << "The matrix:\n";
  A.print();
  std::cout << "Number of cols: " << A.get_ncols() << "\n";
  std::cout << "Number of rows: " << A.get_nrows() << "\n";
  A.set_entry(3,2,1);
  std::cout << "\n";
  std::cout << "This is (3,2): " << A.get_entry(3,2) << std::endl;
}
