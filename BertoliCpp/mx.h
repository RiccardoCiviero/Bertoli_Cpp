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

protected:
	double* data;
	int r, c;
	mx(double* data, int r, int c) noexcept;

public:
	mx() noexcept;
	mx(int r, int c);
	mx(const mx& m);
	mx(int r, int c, std::initializer_list<double> list);
	mx(std::initializer_list<std::initializer_list<double>> list);

	~mx();
	void set(int i, int j, double val);
	double get(int i, int j) const;
	void print();
	std::stringstream to_string();
	
	/// <summary>
	/// Copy-assignment operator 
	/// Safe on self-assignment, and to return the lhs by reference
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	mx& operator=(const mx& m);

	/// <summary>
	/// Move-assignment operator
	/// Safe on self-assignment, and to return the lhs by reference
	/// The move result uses the same data pointer of the moved object
	/// Be careful if using the moved object after the move operation!
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	mx& operator=(mx&& m) noexcept;

	
	double& operator()(int i, int j);


	ax operator()(int i, Direction_t dir);

	mx transpose() const;

	/// <summary>
	/// Returns the maximum value in the matrix
	/// </summary>
	/// <returns>The maximum element value</returns>
	double maximum() const noexcept;
	/// <summary>
	/// Returns the minimum value in the matrix
	/// </summary>
	/// <returns>The minimum element value</returns>
	double minimum() const noexcept;


	/// <summary>
	/// Returns a matrix with elements equals 
	///    max(element, n)
	/// </summary>
	/// <param name="n">Saturator value</param>
	/// <returns>A new matrix, result of operation</returns>
	mx maximum(double n) const noexcept;
	/// <summary>
	/// Returns a matrix with elements equals 
	///    min(element, n)
	/// </summary>
	/// <param name="n">Saturator value</param>
	/// <returns>A new matrix, result of operation</returns>
	mx minimum(double n) const noexcept;


	mx cumsum(Direction_t direction) const;
	mx sum(Direction_t direction) const;
	
	static mx zeros(int r, int c);
	static mx ones(int r, int c);

	double sum() const noexcept;

	void print_size() const;
	int size(Direction_t dir) const;
	

	friend std::ostream& operator<<(std::ostream& os, mx& m);
	friend std::istream& operator>>(std::istream& is, mx& m);

	// Matrix-Matrix operators
	// Both inputs are consts as they are not modified
	mx operator+(const mx& b) const;
	mx operator-(const mx& b) const;
	mx operator*(const mx& b) const;
	mx operator/(const mx& b) const;

	// Matrix-Value operators
	mx operator+(double a) const;
	mx operator-(double a) const;
	mx operator*(double a) const;
	mx operator/(double a) const;


	// Value compare operators
	bool operator==(const mx& b) const;
	bool operator!=(const mx& b) const;

	// Matrix-Array broadcast operators
	mx operator+(const ax& a) const;
	mx operator-(const ax& a) const;
	mx operator*(const ax& a) const;
	mx operator/(const ax& a) const;

	
};

// Inverse Value-Matrix operators
mx operator+(double a, const mx& m);
mx operator-(double a, const mx& m);
mx operator*(double a, const mx& m);
mx operator/(double a, const mx& m);

mx log(const mx& m);