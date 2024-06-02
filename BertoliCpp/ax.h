#pragma once
#include "mx.h"
#include <xkeycheck.h>

// Vectors are only column vectors
// (n x 1) matrix

class ax : public mx
{
public:
	ax (int r) : mx(r, 1) {} 
	ax (const ax& a) : mx(a) {}
	ax(mx& m, int i, Direction_t dir);
	
	ax(mx& m); // cast is possible if matrix is (nx1)

	void set(int i, double v);

	// Broadcast operators commutative version 
	mx operator+(mx& m){ return m+(*this); }
	mx operator-(mx& m){ return m-(*this); }
	mx operator*(mx& m){ return m*(*this); }
	mx operator/(mx& m){ return m/(*this); }


	ax operator+(ax& a) { return (ax&) (((mx&)*this) + (mx&)a); } // terrible is there a better way?
	ax operator-(ax& a) { return (ax&) (((mx&)*this) - (mx&)a); }
	ax operator*(ax& a) { return (ax&)(((mx&)*this) * (mx&)a); }
	//ax operator/(ax& a) { return (ax&)(((mx&)*this) / (mx&)a); }

	ax operator*(double a) { return (ax&)(((mx&)*this) * a); }
	ax operator/(double a) { return (ax&)(((mx&)*this) / a); }

	void print();


	double operator()(int i) { return data[i]; }

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

private:     
	
	// Hide generic matrix metods for vectors
	using mx::zeros;
	using mx::ones;

	using mx::set;
};