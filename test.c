#include <gf2matrix.h>
#include <raptor10.h>

int main() {
  printf("Testing gf2matrix\n");

  // Create a Raptor10 object and fill it w/ all known needed params
  Raptor10 coder;
  unsigned int K = 22;

  coder.K = K;
  coder.Kmin = 1024;
  coder.Kmax = 8192;
  coder.Gmax = 10;
  coder.Al = 4;
  coder.N = 24;
  coder.T = 4;
  r10_compute_params(&coder);
  printf("K=%u, S=%u, H=%u, L=%u\n", coder.K, coder.S, coder.H, coder.L);

  // Allocate and calculate the constraints matrix
  gf2matrix A;
  allocate_gf2matrix(&A, coder.L, coder.L);
  r10_build_constraints_mat(&coder, &A);

  // LT encode
  uint8_t enc_s[coder.L * coder.T];
  uint8_t src_s[coder.K * coder.T];
  r10_encode(src_s, enc_s, &coder, &A);

  // Now, enc_s should contain the encoded symbols
  // Still, doesn't allow to decide the size of the symbols

  printf("Constraints matrix:\n");
  print_matrix(&A);
}
