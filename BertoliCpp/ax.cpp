#include "ax.h"

ax::ax(mx& m, int i, Direction_t dir)
{
	double *data;
	int r, c;
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
		for (int j = 0; j < m.size(ROW); j++) {
			data[j] = m.get(j, i);
		}
	}

	c = 1;

	this->data = data;
	this->r = r;
	this->c = c;
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

ax mx::operator()(int i, Direction_t dir)
{
	return ax(*this, i, dir);
}


mx mx::operator+(ax& a)
{
	mx temp(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			data[i * c + j] += a.get(i, 0);
	return mx();
}

mx mx::operator-(ax& a)
{
	mx temp(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			data[i * c + j] -= a.get(i, 0);
	return mx();
}

mx mx::operator*(ax& a)
{
	mx temp(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			data[i * c + j] *= a.get(i, 0);
	return mx();
}

mx mx::operator/(ax& a)
{
	mx temp(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			data[i * c + j] /= a.get(i, 0);
	return mx();
}



