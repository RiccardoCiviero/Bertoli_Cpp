#pragma once
#include "mx.h"
#include <xkeycheck.h>

// Vectors are only column vectors
// (n x 1) matrix

class ax : public mx
{
public:
	ax() : mx() {}
	ax (int r) : mx(r, 1) {} 
	ax (const ax& a) : mx(a) {}
	ax (mx& m, int i, Direction_t dir);
	
	ax(mx& m); // cast is possible if matrix is (nx1)

	void set(int i, double v);
	double get(int i) const;

	void print();

	double& operator()(int i) { return data[i]; }

	ax slice(int start, int end);

	/// <summary>
	/// Returns the row of the maximum value in the vector in the array
	/// 
	/// </summary>
	/// <returns>Row index</returns>
	int maximum_index();
	/// <summary>
	/// Returns the row of the minimum value in the vector in the array
	/// 
	/// </summary>
	/// <returns>Row index</returns>
	int minimum_index();

	static ax zeros(int r);
	static ax ones(int r);

	double last() { return data[r-1]; }



	// Matrix-Vector inverse operators
	mx operator+(const mx& m) const { return m + *this; }
	mx operator-(const mx& m) const { return m + *this; }
	mx operator*(const mx& m) const { return m * *this; }
	mx operator/(const mx& m) const { return m / *this; }

	// Array-Array operators
	ax operator+(const ax& b) const { return (ax&)(((mx&)*this) + (mx&)b); } // terrible is there a better way?
	ax operator-(const ax& b) const { return (ax&)(((mx&)*this) - (mx&)b); }
	ax operator*(const ax& b) const { return (ax&)(((mx&)*this) * (mx&)b); }
	ax operator/(const ax& b) const { return (ax&)(((mx&)*this) / (mx&)b); }
	
	// Array-Value operators
	ax operator*(double v) { return (ax&)(((mx&)*this) * v); }
	ax operator/(double v) { return (ax&)(((mx&)*this) / v); }

private:     
	
	// Hide generic matrix metods for vectors
	using mx::zeros;
	using mx::ones;

	using mx::set;
	using mx::get;
};