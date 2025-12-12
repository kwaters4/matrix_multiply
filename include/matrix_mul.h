
// Smallest and largest value generated in random matrix
# define MAX 5
# define MIN -5

int* malloc_matrix_int(int n);
void free_matrix_int(int *matrix);

void generate_zero_matrix(int *matrix, int n);
void generate_identity_matrix(int *matrix1, int n);
int compare_matrices(int *matrix1, int *matrix2, int n);

void populate_matrix(int *matrix, int n);
int print_matrix(int *matrix, int n);
void multiply_matrices(int *matrix1, int *matrix2, int *result, int n);
void multiply_matrices_sum(int *matrix1, int *matrix2, int *result, int n);
void multiply_matrices_strip(int *matrix1, int *matrix2, int *result, int n);
