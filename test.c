#include <gf2matrix.h>
#include <raptor10.h>

int main(int argc, char* argv[])
{
  printf("Testing gf2matrix\n");

  // Create a Raptor10 object and fill it w/ all known needed params
  Raptor10 coder;
  unsigned int K = 22;
  /* unsigned int S = 7; */
  /* unsigned int H = 6; */
  /* unsigned int L = K + S + H; */

  coder.K = K;
  coder.Kmin = 1024;
  coder.Kmax =8192;
  coder.Gmax = 10;
  coder.Al = 4;
  compute_params(&coder);
  printf("K=%u, S=%u, H=%u, L=%u\n", coder.K, coder.S, coder.H, coder.L);

  gf2matrix A;
  allocate_gf2matrix(&A, coder.L, coder.L);
  
  // Compute the intermediate symbols
  build_LDPC_mat(K, coder.S, &A);
  build_Half_mat(K, coder.S, coder.H, &A);
  for (int i = 0; i < coder.S; i++) {
  	set_entry(&A, i, K+i, 1);
  }
  for (int i = 0; i < coder.H; i++) {
  	set_entry(&A, coder.S+i, K+coder.S+i, 1);
  }
  build_LT_mat(K, coder.S, coder.H, coder, &A);
  print_matrix(&A);

  gf2matrix B;
  gf2matrix id;
  allocate_gf2matrix(&B, coder.L, coder.L);
  allocate_gf2matrix(&id, coder.L, coder.L);
  for (int n = 0; n < coder.L; n++) {
	for (int m = 0; m < coder.L; m++) {
	  set_entry(&B, n, m, get_entry(&A, n, m));
	}
  }
  printf("Hopefully A again\n");
  print_matrix(&B);
  // Compute the encoding matrix: invert the intermediate matrix
  gaussjordan_inv(&A);
  mat_mul(&A, &B, &id);
  printf("Hopefully identity\n");
  print_matrix(&id);

  // From now on it should be possible to call the encode and decode functions
  
}
