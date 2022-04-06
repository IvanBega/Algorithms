#include <climits>
#include <iostream>
#include <vector>
using namespace std;
class RationalNumber
{
private:
    int numerator;
    int denominator;
public:
    int getNumerator() const
    {
        return numerator;
    }
    int getDenominator() const
    {
        return denominator;
    }
    void setNumerator(int num)
    {
        numerator = num;
    }
    void setDenominator(int den)
    {
        denominator = den;
    }
    static RationalNumber zero()
    {
        RationalNumber rn(0, 1);
        return rn;
    }
    static RationalNumber max()
    {
        RationalNumber rn(1000000, 1);
        return rn;
    }
    static RationalNumber fromInt(int number)
    {
        RationalNumber rn(number, 1);
        return rn;
    }
    RationalNumber()
    {
        numerator = 1;
        denominator = 1;
    }
    RationalNumber(int n, int d)
    {
        numerator = n;
        denominator = d;
    }
    friend bool operator==(const RationalNumber& lt, const RationalNumber& rt);
    friend bool operator!=(const RationalNumber& lt, const RationalNumber& rt);
    friend bool operator>(const RationalNumber& lt, const RationalNumber& rt);
    friend bool operator<(const RationalNumber& lt, const RationalNumber& rt);
    friend bool operator>=(const RationalNumber& lt, const RationalNumber& rt);
    friend bool operator<=(const RationalNumber& lt, const RationalNumber& rt);
    friend ostream& operator<<(ostream& out, const RationalNumber& obj);


};
int absInt(int x) {
    if (x >= 0) {
        return x;
    }
    else {
        return -x;
    }
}
void getFactors(int num, vector<int>& factorSet) {
    if (num != 1) {
        factorSet.push_back(num);
    }
    for (int i = 2; i <= sqrt(static_cast<double>(num)); i++) {
        if (num % i == 0) {
            factorSet.push_back(i);
            factorSet.push_back(num / i);
        }
    }
}
void simplifyFun(int& a, int& b) {
    int tempN = a;
    int tempD = b;
    int small, temp;
    vector<int> factorSet;
    if (tempN == tempD) {
        a = 1;
        b = 1;
        return;
    }
    else if (tempN == -tempD) {
        a = -1;
        b = 1;
        return;
    }
    else if (tempN == 0) {
        b = 1;
        return;
    }


    if (absInt(tempN) < absInt(tempD)) {
        small = absInt(tempN);
    }
    else {
        small = absInt(tempD);
    }

    getFactors(small, factorSet);
    for (int i = 0; i < factorSet.size(); i++) {
        temp = factorSet[i];
        while (tempN % temp == 0 && tempD % temp == 0) {
            tempN /= temp;
            tempD /= temp;
        }
    }
    a = tempN;
    b = tempD;
}
RationalNumber operator+(const RationalNumber& left, const RationalNumber& right)
{
    RationalNumber temp;
    int tempLD = left.getDenominator();
    int tempRD = right.getDenominator();
    simplifyFun(tempLD, tempRD);
    temp.setDenominator(left.getDenominator() * tempRD);
    temp.setNumerator(left.getNumerator() * tempRD + right.getNumerator() * tempLD);
    return temp;
}

bool operator==(const RationalNumber& lt, const RationalNumber& rt)
{
    return lt.denominator == rt.denominator && lt.numerator == rt.denominator;
}

bool operator!=(const RationalNumber& lt, const RationalNumber& rt)
{
    return !(lt == rt);
}

bool operator>(const RationalNumber& lt, const RationalNumber& rt)
{
    return ((double)lt.numerator / (double)lt.denominator) > ((double)rt.numerator / (double)rt.denominator);
}

bool operator<(const RationalNumber& lt, const RationalNumber& rt)
{
    return !(lt > rt);
}

bool operator>=(const RationalNumber& lt, const RationalNumber& rt)
{
    return (lt > rt) || (lt == rt);
}

bool operator<=(const RationalNumber& lt, const RationalNumber& rt)
{
    return (lt < rt) || (lt == rt);
}

ostream& operator<<(ostream& out, const RationalNumber& obj)
{
    out << obj.numerator << "/" << obj.denominator;
    return out;
}

// Додаткова функція для підрахунку суми елементів масиву з 
// freq[i] по freq[j]
int sum(int freq[], int i, int j);

RationalNumber optimalSearchTree(RationalNumber keys[], int freq[], int n, RationalNumber tree[])
{
    RationalNumber cost[3][3];

    /* cost[i][j] = Оптимальна ціна ДДП
    яка може бути сформована з keys[i] дo keys[j].
    В cost[0][n-1] буде зберігатись ціна дерева */

    // Для одного вузла, ціна дерева дорівнює частоті 
    for (int i = 0; i < n; i++)
        cost[i][i] = RationalNumber::fromInt(freq[i]);

    // Тепер працюємо з ланцюжками довжини 2, 3, ... .
    // L - довжина ланцюжка.
    for (int L = 2; L <= n; L++)
    {
        // i - рядок в cost[][]
        for (int i = 0; i <= n - L + 1; i++)
        {
            // Отримуємо стовпчик j з рядка i та
            // ланцюжка довжини L
            int j = i + L - 1;
            cost[i][j] = RationalNumber::max();

            // Підставляємо всі ключі [i..j] у якості кореня
            for (int r = i; r <= j; r++)
            {
                // c = ціна коли keys[r] стає коренем піддерева
                RationalNumber c = ((r > i) ? cost[i][r - 1] : RationalNumber::zero()) + ((r < j) ? cost[r + 1][j] : RationalNumber::zero()) + RationalNumber::fromInt(sum(freq, i, j));
                if (c < cost[i][j])
                {
                    cost[i][j] = c;
                    tree[i] = keys[r]; // зберігаємо елементи дерева у масиві
                }
            }
        }
    }
    return cost[0][n - 1];
}

// Додаткова функція для підрахунку елементів масиву з 
// freq[i] по freq[j]
int sum(int freq[], int i, int j)
{
    int s = 0;
    for (int k = i; k <= j; k++)
        s += freq[k];
    return s;
}

int main()
{
    RationalNumber keys[] = { RationalNumber::fromInt(10), RationalNumber::fromInt(12), RationalNumber::fromInt(20) };
    int freq[] = { 34, 8, 50 };
    int n = sizeof(keys) / sizeof(keys[0]);
    RationalNumber tree[3];
    cout << "Cost of Optimal BST is " << optimalSearchTree(keys, freq, n, tree);
    return 0;
}