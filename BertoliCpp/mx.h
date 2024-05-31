#pragma once
#include <iostream>
#include <tuple>

#define ALL -1

class ax;

typedef enum
{
	ROW,
	COL
} Direction_t;

class mx
{

private:
	double* data;
	int r, c;

protected:
	mx(double* data, int r, int c);

public:
	mx(int r, int c);
	mx(const mx& m);
	~mx();
	void set(int i, int j, double val);
	double get(int i, int j);
	void print();
	mx operator+(mx& m);
	mx operator-(mx& m);
	mx operator*(mx& m);
	mx operator*(double a);
	mx operator/(double a);
	mx operator=(mx& m);
	mx operator+=(mx& m);
	mx operator-=(mx& m);
	mx operator*=(mx& m);
	mx operator*=(double a);
	mx operator/=(double a);
	bool operator==(mx& m);
	bool operator!=(mx& m);
	ax operator()(int i, int j);


	mx cumsum(Direction_t direction);
	mx sum(Direction_t direction);
	double sum();

	void print_size();
	int size(Direction_t dir);
	

	friend std::ostream& operator<<(std::ostream& os, mx& m);
	friend std::istream& operator>>(std::istream& is, mx& m);
};

