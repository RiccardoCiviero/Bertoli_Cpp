#include "mx.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

mx::mx(double* data, int r, int c)
{
	this->data = data;
	this->r = r;
	this->c = c;
}

mx::mx()
{
	r = -1;
	c = -1;
	data = nullptr;
}


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

mx::mx(int r, int c, std::initializer_list<double> list)
{
	if (r * c != list.size()) throw new std::exception("Initializer list dimensions do not match");
	
	this->r = r;
	this->c = c;
	data = new double[r * c];
	int i = 0;
	for (auto it = list.begin(); it != list.end() && i < (r*c); it++)
		data[i++] = *it;

}

mx::mx(std::initializer_list<std::initializer_list<double>> list)
{
	r = list.size();
	c = list.begin()->size();
	data = new double[r * c];
	int i = 0;
	for (auto it = list.begin(); it != list.end() && i < (r * c); it++)
	{
		if (it->size() != c) throw new std::exception("Initializer list dimensions do not match");
		for (auto it2 = it->begin(); it2 != it->end() && i < (r * c); it2++)
			data[i++] = *it2;
	}

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

mx& mx::operator=(const mx& m)
{
	// Guard self assignment
	if (this == &m)
		return *this;

	// If same dimensions (of internal array, not nxm), do not reallocate memory
	if(data != nullptr && r*c == m.r*m.c)
	{
		r = m.r;
		c = m.c;
		for (int i = 0; i < r * c; i++)
			data[i] = m.data[i];
		return *this;
	}

	// Reallocate memory
	delete[] data;
	r = m.r;
	c = m.c;
	data = new double[r * c];
	for (int i = 0; i < r * c; i++)
		data[i] = m.data[i];
	return *this;
}

mx& mx::operator=(mx&& m) noexcept
{
	// Guard self assignment
	if (this == &m)
		return *this;

	// Move data
	delete[] data;
	r = m.r;
	c = m.c;
	data = m.data;
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


//ax mx::operator()(int i, int j)
//{
//	if (i == ALL) {
//		return ax()
//	} else
//	//return data[i * c + j];
//}

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

void mx::print_size() {
	std::cout << "(" << r << ", " << c << ")" << std::endl;
}

int mx::size(Direction_t dir)
{
	return dir == ROW ? r : c;
}

// ROW returns a column vector and vice versa
mx mx::sum(Direction_t direction)
{
	if (direction == Direction_t::ROW)
	{
		mx temp(1, c);
		for (int j = 0; j < c; j++)
			for (int i = 0; i < r; i++)
				temp.data[j] += data[i * c + j];
		return temp;
	}
	else {
		mx temp(r, 1);
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				temp.data[i] += data[i * c + j];
		return temp;
	}

}

mx mx::zeros(int r, int c)
{
	double* data = new double [r * c];
	for (int i = 0; i < r * c; i++)
		data[i] = 0;
	return mx(data, r, c);
}


mx mx::ones(int r, int c)
{
	double* data = new double[r * c];
	for (int i = 0; i < r * c; i++)
		data[i] = 1;
	return mx(data, r, c);
}

double mx::sum()
{
	double sum = 0;
	for(int i = 0; i < r * c; i++)
		sum += data[i];
	return sum;
}

double mx::maximum()
{
	double max = data[0];
	for (int i = 1; i < r * c; i++)
		if (data[i] > max)
			max = data[i];
	return max;
}

double mx::minimum()
{
	double min = data[0];
	for (int i = 1; i < r * c; i++)
		if (data[i] < min)
			min = data[i];
	return min;
}

mx mx::maximum(double n)
{
	mx temp(r, c);
	for (int i = 0; i < r * c; i++)
		temp.data[i] = std::max(data[i], n);
	return temp;
}


mx mx::minimum(double n)
{
	mx temp(r, c);
	for (int i = 0; i < r * c; i++)
		temp.data[i] = std::min(data[i], n);
	return temp;
}
