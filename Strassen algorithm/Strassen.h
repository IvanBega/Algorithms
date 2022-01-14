#define N 4 // maximum matrix size

#define eps 0.00000001 // precision for double comparison

void Print(double A[N][N], int n);

void ClassicMultiplication(double A[N][N], double B[N][N], double C[N][N], int n);

void Add(double A[N][N], double B[N][N], double C[N][N], int n);

void Subtract(double A[N][N], double B[N][N], double C[N][N], int n);

void Strassen(double A[N][N], double B[N][N], double C[N][N], int n);

bool Equals(double A[N][N], double B[N][N], int n);