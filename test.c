#include <gf2matrix.h>

int main(void)
{
  printf("Testing gf2matrix\n");
  
  gf2matrix mat;
  mat.n_rows = 32;
  mat.n_cols = 32;

  allocate_gf2matrix(&mat);

  set_entry(&mat, 4, 4, 1);

  int i = get_entry(&mat, 4, 4);

  printf("The value is: %d\n", i);

  
}
