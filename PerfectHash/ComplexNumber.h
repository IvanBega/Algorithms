#pragma once
class ComplexNumber
{
private:
	int _re;
	int _im;
public:
	ComplexNumber();
	ComplexNumber(int re, int im);
	int getRe();
	int getIm();
};

