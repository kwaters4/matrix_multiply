
// Smallest and largest value generated in random matrix
# define MAX 5
# define MIN -5

#define BLOCK_SIZE 256

int* malloc_matrix_int(const int n);
void free_matrix_int(int *matrix);

void generate_zero_matrix(int *matrix, const int n);
void generate_identity_matrix(int *matrix1, const int n);
int compare_matrices(const int *matrix1, const int *matrix2, const int n);

void populate_matrix(int *matrix, const int n);
int print_matrix(const int *matrix, const int n);
void multiply_matrices(const int *matrix1, const int *matrix2, int *result, const int n);
void multiply_matrices_sum(const int *matrix1, const int *matrix2, int *result, const int n);
void multiply_matrices_strip(const int *matrix1, const int *matrix2, int *result, const int n);
void multiply_matrices_strip_unrolled(const int *matrix1, const int *matrix2, int *result, const int n);
void multiply_matrices_blocked(const int *matrix1, const int *matrix2, int *result, const int n);
