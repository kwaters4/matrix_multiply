enum Mult_Algo {
  NAIVE,
  SUM,
  STRIP
};

void test_nxn_A(int *matrix, int n);
void test_nxn_B(int *matrix, int n);
void set_2x2_test_matrix(int *test_result);
void set_3x3_test_matrix(int *test_result);
void set_4x4_test_matrix(int *test_result);
int determined_test_mult(int *test_result, int n, enum Mult_Algo algo);
