// PerfectHash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <vector>
#include "ComplexNumber.h"
#include "PerfectHash.h"

int rand_int(int min, int max) {
    static std::random_device rd;
    static std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
    static std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}
int hashComplex(ComplexNumber* number, int a, int b, int m, int p) {
    int h = 0;
    h = (b + a * (number->getRe())) % p;
    h = (b + a * (h + number->getIm())) % p;
    return h % m;
}

class HashNode
{
public:
    int a;
    int b;
    int m;
    std::vector<ComplexNumber*> elements;
    std::vector<ComplexNumber*> tmp;
    HashNode()
    {
        a = b = m = 0;
        tmp = std::vector<ComplexNumber*>();
    }
    void fill(int p) 
    {
        m = (int)(tmp.size() * tmp.size());
        if (m == 1) {
            elements = tmp;
            tmp.clear();
            return;
        }

        bool flag = false;
        while (!flag) {
            elements.clear();
            elements = std::vector<ComplexNumber*>(m, nullptr);
            a = rand_int(1, p - 1);
            b = rand_int(0, p - 1);

            flag = true;
            for (auto& complex : tmp) 
            {
                int index = hashComplex(complex, a, b, m, p);
                std::cout << index << std::endl;
                if (elements[index] != nullptr) 
                {
                    flag = false;
                    break;
                }
                elements[index] = complex;
            }
        }


    }
    ComplexNumber* getComplex(ComplexNumber number, int p)
    {
        return elements[hashComplex(&number, a, b, m, p)];
    }

};

class HashTable
{
public:
    std::vector<HashNode> data = std::vector<HashNode>(80);
    int a;
    int b;
    int p;
    int m;
    HashTable(std::vector<ComplexNumber*> elements) {
        p = 2713;
        m = 80;
        //data = std::vector<HashNode>(m);

        a = rand_int(1, p - 1);
        b = rand_int(0, p - 1);

        for (auto& e : elements) {
            data[hashComplex(e, a, b, m, p)].tmp.push_back(e);
        }

        for (auto& node : data) {
            node.fill(p);
        }
    }

    ComplexNumber* getComplex(ComplexNumber& number) {
        return data[hashComplex(&number, a, b, m, p)].getComplex(number, p);
    }
};
int main()
{
    std::vector<ComplexNumber*> v;
    auto n = new ComplexNumber(1, 1);
    v.push_back(n);
    v.push_back(new ComplexNumber(2, 3));
    v.push_back(new ComplexNumber(4, 3));
    v.push_back(new ComplexNumber(5, 3));
    v.push_back(new ComplexNumber(6, 3));
    v.push_back(new ComplexNumber(7, 3));
    HashTable hash(v);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
