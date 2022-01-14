#include <iostream>
#include <chrono>
#include "Strassen.h"

using namespace std;

int main()
{
    double A[4][4] = {
            {3,4,5,1},
            {3,7,3,5},
            {2,-4,1,5},
            {7,2,3.5,8.2}
    };
    double B[4][4] = {
        {-1.2,3.3,4,1},
        {4,6,8,9},
        {3,6,7,-0.8},
        {1,4,3,6}
    };
    double C[4][4];
    double D[4][4];
    auto start = std::chrono::high_resolution_clock::now();
    Strassen(A, B, C, 4);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    ClassicMultiplication(A, B, D, 4);
    Print(C, 4);
    Print(D, 4);
    std::cout << Equals(C, D, 4) << endl;
    std::cout << "\nTook " << duration.count() << " microseconds";
    return 0;
}
// matrix output to console
void Print(double A[N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }
}

// classic matrix multiplication
void ClassicMultiplication(double A[N][N], double B[N][N], double C[N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

// matrix addition
void Add(double A[N][N], double B[N][N], double C[N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// matrix subtraction
void Subtract(double A[N][N], double B[N][N], double C[N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// matrix multiplication using Strassen algorithm
void Strassen(double A[N][N], double B[N][N], double C[N][N], int n)
{
    double A11[N][N], A12[N][N], A21[N][N], A22[N][N],
        B11[N][N], B12[N][N], B21[N][N], B22[N][N],
        C11[N][N], C12[N][N], C21[N][N], C22[N][N],
        P1[N][N], P2[N][N], P3[N][N], P4[N][N], P5[N][N], P6[N][N], P7[N][N];

    if (n <= 2)
    {
        ClassicMultiplication(A, B, C, n);
        return;
    }
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n / 2];
            A21[i][j] = A[i + n / 2][j];
            A22[i][j] = A[i + n / 2][j + n / 2];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + n / 2];
            B21[i][j] = B[i + n / 2][j];
            B22[i][j] = B[i + n / 2][j + n / 2];
        }
    }

    double temp1[N][N], temp2[N][N];
    /*P1 = (A11 + A22)(B11 + B22)
    P2 = (A21 + A22)B11
    P3 = A11(B12 - B22)
    P4 = A22(B21 - B11)
    P5 = (A11 + A12)B22
    P6 = (A21 - A11)(B11 + B12)
    P7 = (A12 - A22)(B21 + B22)*/

    // P1 = (A11 + A22)(B11 + B22)
    Add(A11, A22, temp1, n / 2);
    Add(B11, B22, temp2, n / 2);
    Strassen(temp1, temp2, P1, n / 2);

    // P2 = (A21 + A22)B11
    Add(A21, A22, temp1, n / 2);
    Strassen(temp1, B11, P2, n / 2);

    // P3 = A11(B12 - B22)
    Subtract(B12, B22, temp2, n / 2);
    Strassen(A11, temp2, P3, n / 2);

    // P4 = A22(B21 - B11)
    Subtract(B21, B11, temp2, n / 2);
    Strassen(A22, temp2, P4, n / 2);

    // P5 = (A11 + A12)B22
    Add(A11, A12, temp1, n / 2);
    Strassen(temp1, B22, P5, n / 2);

    // P6 = (A21 - A11)(B11 + B12)
    Subtract(A21, A11, temp1, n / 2);
    Add(B11, B12, temp2, n / 2);
    Strassen(temp1, temp2, P6, n / 2);

    // P7 = (A12 - A22)(B21 + B22)
    Subtract(A12, A22, temp1, n / 2);
    Add(B21, B22, temp2, n / 2);
    Strassen(temp1, temp2, P7, n / 2);

    /*
    C11  = P1 + P4 - P5 + P7
    C12 = P3 + P5
    C21 = P2 + P4
    C22 = P1 - P2 + P3 +P6*/

    // C11  = P1 + P4 - P5 + P7
    Add(P1, P4, temp1, n / 2);
    Subtract(P7, P5, temp2, n / 2);
    Add(temp1, temp2, C11, n / 2);

    // C12 = P3 + P5
    Add(P3, P5, C12, n / 2);

    // C21 = P2 + P4
    Add(P2, P4, C21, n / 2);

    // C22 = P1 - P2 + P3 +P6
    Subtract(P1, P2, temp1, n / 2);
    Add(P3, P6, temp2, n / 2);
    Add(temp1, temp2, C22, n / 2);

    for (int i = 0; i < n / 2; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + n / 2] = C12[i][j];
            C[i + n / 2][j] = C21[i][j];
            C[i + n / 2][j + n / 2] = C22[i][j];
        }
    }
}

// checks whether matrices are equals
bool Equals(double A[N][N], double B[N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] - B[i][j] > 0.00000001)
                return false;
        }
    }
    return true;
}