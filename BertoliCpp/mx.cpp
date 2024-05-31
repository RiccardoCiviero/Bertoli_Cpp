#include "mx.h"

#include <iostream>
#include <cassert>

mx::mx(int r, int c)
{
	this->r = r;
	this->c = c;
	data = new double[r * c];
}

mx::mx(const mx& m)
{
	r = m.r;
	c = m.c;
	data = new double[r * c];
	for (int i = 0; i < r * c; i++)
		data[i] = m.data[i];
}

mx::~mx()
{
	delete[] data;
}

void mx::set(int i, int j, double val)
{
	data[i * c + j] = val;
}

double mx::get(int i, int j)
{
	return data[i * c + j];
}

void mx::print()
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
			std::cout << data[i * c + j] << " ";
		std::cout << std::endl;
	}
}

mx mx::operator+(mx& m)
{
	// check dimensions
	if (r != m.r || c != m.c)
		throw new std::exception("Dimensions do not match");

	mx temp(r, c);
	for (int i = 0; i < r * c; i++)
		temp.data[i] = data[i] + m.data[i];
	return temp;
}

mx mx::operator-(mx& m)
{
	if (r != m.r || c != m.c)
		throw new std::exception("Dimensions do not match");
	mx temp(r, c);
	for (int i = 0; i < r * c; i++)
		temp.data[i] = data[i] - m.data[i];
	return temp;
}

mx mx::operator*(mx& m)
{
	if (r != m.r || c != m.c)
		throw new std::exception("Dimensions do not match");
	mx temp(r, c);
	for (int i = 0; i < r * c; i++)
		temp.data[i] = data[i] * m.data[i];
	return temp;
}

mx mx::operator*(double a)
{
	mx temp(r, c);
	for (int i = 0; i < r * c; i++)
		temp.data[i] = data[i] * a;
	return temp;
}

mx mx::operator/(double a)
{
	mx temp(r, c);
	for (int i = 0; i < r * c; i++)
		temp.data[i] = data[i] / a;
	return temp;
}

mx mx::operator=(mx& m)
{
	if (this == &m)
		return *this;
	delete[] data;
	r = m.r;
	c = m.c;
	data = new double[r * c];
	for (int i = 0; i < r * c; i++)
		data[i] = m.data[i];
	return *this;
}

mx mx::operator+=(mx& m)
{
	for (int i = 0; i < r * c; i++)
		data[i] += m.data[i];
	return *this;
}

mx mx::operator-=(mx& m)
{
	for (int i = 0; i < r * c; i++)
		data[i] -= m.data[i];
	return *this;
}

mx mx::operator*=(mx& m)
{
	for (int i = 0; i < r * c; i++)
		data[i] *= m.data[i];
	return *this;
}

mx mx::operator*=(double a)
{
	for (int i = 0; i < r * c; i++)
		data[i] *= a;
	return *this;
}

mx mx::operator/=(double a)
{
	for (int i = 0; i < r * c; i++)
		data[i] /= a;
	return *this;
}

bool mx::operator==(mx& m)
{
	if (r != m.r || c != m.c)
		return false;
	for (int i = 0; i < r * c; i++)
		if (data[i] != m.data[i])
			return false;
	return true;
}

bool mx::operator!=(mx& m)
{
	return !(*this == m);
}

mx mx::cumsum(Direction_t direction)
{
	mx temp(r, c);
	if (direction == Direction_t::ROW)
	{
		for (int i = 1; i < r; i++)
			for(int j = 0; j < c; j++)
				temp.data[i * c + j] = temp.data[(i - 1) * c + j] + data[i * c + j];
	}
	else {
		for(int j = 1; j < c; j++)
			for (int i = 0; i < r; i++)
				temp.data[i * c + j] = temp.data[i * c + j - 1] + data[i * c + j];
	}

	return temp;
}


std::ostream& operator<<(std::ostream& os, mx& m) {
	for (int i = 0; i < m.r; i++)
	{
		for (int j = 0; j < m.c; j++)
			os << m.data[i * m.c + j] << " ";
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, mx& m) {
	for (int i = 0; i < m.r; i++)
		for (int j = 0; j < m.c; j++)
			is >> m.data[i * m.c + j];
	return is;
}

void mx::size() {
	std::cout << "(" << r << ", " << c << ")" << std::endl;
}


