#include "gf2matrix.h"
#include "raptor10.h"

int main(int argc, char* argv[])
{
  printf("Testing gf2matrix\n");
  
  gf2matrix mat;
  allocate_gf2matrix(&mat, 6, 6);

  set_entry(&mat, 0, 0, 1);
  set_entry(&mat, 0, 1, 1);
  set_entry(&mat, 0, 2, 1);
  set_entry(&mat, 0, 3, 1);
  set_entry(&mat, 1, 1, 1);
  set_entry(&mat, 1, 3, 1);
  set_entry(&mat, 2, 1, 1);
  set_entry(&mat, 3, 0, 1);
  set_entry(&mat, 4, 4, 1);
  set_entry(&mat, 5, 5, 1);
  set_entry(&mat, 0, 5, 1);

  gf2matrix mat_;
  allocate_gf2matrix(&mat_, 6, 6);

  set_entry(&mat_, 0, 0, 1);
  set_entry(&mat_, 0, 1, 1);
  set_entry(&mat_, 0, 2, 1);
  set_entry(&mat_, 0, 3, 1);
  set_entry(&mat_, 1, 1, 1);
  set_entry(&mat_, 1, 3, 1);
  set_entry(&mat_, 2, 1, 1);
  set_entry(&mat_, 3, 0, 1);
  set_entry(&mat_, 4, 4, 1);
  set_entry(&mat_, 5, 5, 1);
  set_entry(&mat_, 0, 5, 1);

  // Print the matrix
  print_matrix(&mat);

  // Apply Gauss-Jordan
  gaussjordan_inv(&mat);
  // Print inverted matrix
  printf("Inverted:\n");
  print_matrix(&mat);
  // print multiplication to test M * inv(M) = I
  printf("This should be identity:\n");
  gf2matrix result;
  allocate_gf2matrix(&result, 6, 6);

  mat_mul(&mat, &mat_, &result);

  

  print_matrix(&result);
  
}
