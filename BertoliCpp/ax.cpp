#include "ax.h"

#include <exception>

ax::ax(mx& m, int i, Direction_t dir)
{
	if (dir == ROW) {
		r = m.size(COL);
		data = new double[m.size(COL)];
		for (int j = 0; j < m.size(COL); j++) {
			data[j] = m.get(i, j);
		}

	}
	else {
		r = m.size(ROW);
		data = new double[m.size(ROW)];
		for (int j = 0; j < m.size(ROW); ++j) {
			data[j] = m.get(j, i);
		}
	}

	c = 1;
}

ax::ax(mx& m) {
	if (m.size(COL) != 1 && m.size(ROW) !=1) throw new std::exception("Cast to matrix to vector is allowed only for (nx1) matrixes (Column vectors) or (1xn) matrixes casting them to column vector");

	if (m.size(COL) == 1) {
		r = m.size(ROW);
		c = 1;
		data = new double[r];
		for (int i = 0; i < r; i++)
			data[i] = m.get(i, 0);
	}
	else {
		r = m.size(COL);
		c = 1;
		data = new double[r];
		for (int i = 0; i < r; i++)
			data[i] = m.get(0, i);
	}
}


int ax::maximum_index()
{
	int max = 0;
	for (int i = 1; i < r; i++)
		if (data[i] > data[max])
			max = i;
	return max;
}


int ax::minimum_index()
{
	int min = 0;
	for (int i = 1; i < r; i++)
		if (data[i] < data[min])
			min = i;
	return min;
}

ax ax::zeros(int r)
{
	ax temp(r);
	for (int i = 0; i < r; i++)
		temp.data[i] = 0;
	return temp;
}

ax ax::ones(int r)
{
	ax temp(r);
	for (int i = 0; i < r; i++)
		temp.data[i] = 1;
	return temp;
}

ax mx::operator()(int i, Direction_t dir)
{
	if (i >= r || i < 0) throw new std::exception("Index fail");
	return ax(*this, i, dir);
}


// Operators 


mx mx::operator+(const ax& a) const
{
	mx temp(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			temp.data[i * c + j] = data[i * c + j] + a.get(i);
	return temp;
}

mx mx::operator-(const ax& a) const
{
	mx temp(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			temp.data[i * c + j] = data[i * c + j] + a.get(i);
	return temp;
}

mx mx::operator*(const ax& a) const
{
	mx temp(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			temp.data[i * c + j] = data[i * c + j] + a.get(i);
	return temp;
}

mx mx::operator/(const ax& a) const
{
	mx temp(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			temp.data[i * c + j] = data[i * c + j] + a.get(i);
	return temp;
}

ax operator+(double a, const ax& m)
{
	return (ax&)(a + (mx&)m);
}
ax operator-(double a, const ax& m)
{
	return (ax&)(a - (mx&)m);
}
ax operator*(double a, const ax& m)
{
	return (ax&)(a * (mx&)m);
}
ax operator/(double a, const ax& m)
{
	return (ax&)(a / (mx&)m);
}


ax ax::slice(int start, int end) {
	if(end <= start || start < 0 || end < 0) throw new std::exception("Index fail");
	if(end >= r) throw new std::exception("Slice dimension error");
	
	ax temp(end - start + 1);

	for(int i = start; i <= end; i++) {
		temp.set(i - start, data[i]);
	}

	return temp;
}

void ax::set(int i, double v) {
	if(i >= r || i < 0) throw new std::exception("Index fail");
	data[i] = v;
}

double ax::get(int i) const {
	if (i >= r || i < 0) throw new std::exception("Index fail");
	return data[i];
}

void ax::print() {
	std::cout << "ax (" << r << ", " << c << ")" << std::endl;
	std::cout << "[ ";
	for (int i = 0; i < r; i++)
	{
		std::cout << data[i] << std::endl;
	}
	std::cout << "]" << std::endl;
}

double& ax::operator()(int i)
{
	if (i >= r || i < 0) throw new std::exception("Index fail");
	return data[i];
}

ax log(const ax& m) {
	return (ax&)log((mx&)m);
}