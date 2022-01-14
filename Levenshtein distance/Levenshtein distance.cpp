#include <iostream>
int min(int x, int y, int z)
{
    return std::min(std::min(x, y), z);
}

int editDistance(char* s1, char* s2, int length1, int length2)
{
    int matrix[10];
    int last, old; // діагоналі
    for (int i = 1; i <= length1; i++)
    {
        matrix[i] = i;
    }
    for (int i = 1; i <= length2; i++)
    {
        matrix[0] = i;
        for (int j = 1, last = j - 1; j <= length1; j++)
        {
            old = matrix[j];
            matrix[j] = min(matrix[j] + 1, matrix[j - 1] + 1, last + (s1[j - 1] == s2[i - 1] ? 0 : 1));
            last = old;
        }
    }
    return matrix[length1];
}
int main()
{
    char s1[] = "app";
    char s2[] = "apple";
    std::cout << editDistance(s1, s2, 3, 5);
}
