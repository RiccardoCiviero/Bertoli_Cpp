#pragma once
#include "mx.h"

// Vectors are only column vectors
// (n x 1) matrix

class ax : public mx
{
public:
	ax (int r) : mx(r, 1) {} 
	ax (const ax& a) : mx(a) {}
	ax(mx& m, int i, Direction_t dir);

	mx operator+(mx& m){ return m+(*this); }
	mx operator-(mx& m){ return m-(*this); }
	mx operator*(mx& m){ return m*(*this); }
	mx operator/(mx& m){ return m/(*this); }


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

private:                                        
};