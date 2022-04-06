#include "ComplexNumber.h"

ComplexNumber::ComplexNumber() : _re(0), _im(0)
{
}

ComplexNumber::ComplexNumber(int re, int im) : _re(re), _im(im)
{
}

int ComplexNumber::getRe()
{
	return _re;
}

int ComplexNumber::getIm()
{
	return _im;
}
