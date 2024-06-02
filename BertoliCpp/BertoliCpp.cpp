 // BertoliCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "mx.h"
#include "ax.h"

constexpr double pi = 3.14159265358979323846;

mx strain_fcn_calc(ax f, ax h, ax b_prime, mx rho);
double LAM();
double Bertoli();
void Bertoli_Wrapper();

int main()
{
	mx m({{1, 2, 3}, {4, 5, 6}});
	std::cout << "m "; m.print(); std::cout << std::endl;

	ax a = m(0, ROW);
	ax a1 = m(1, COL);
	std::cout << "a "; a.print(); std::cout << std::endl;
	std::cout << "a1 "; a1.print(); std::cout << std::endl;

	a1.minimum_index();
}

mx strain_fcn_calc(ax f, ax h, ax b_prime, mx rho)
{
	mx p = h * b_prime * rho;

	return p.cumsum(ROW) + f;
}
//
//double LAM()
//{
//	mx rho = mx::zeros(N, 1);
//	mx rho_vec_initializer = mx::zeros(N, N);
//
//
//	while (delta > delta_res)
//	{
//		mx delta_vec = delta ; // qui va il vettore 9x2
//
//		for (int i = 0; i < N-1; i++)
//		{
//			mx rho_vec = rho_vec * delta_vec; // bohh
//
//			rho_vec = rho_vec.maximum(0);
//
//			mx strain_vec = strain_fcn_calc(f, h, b_prime, rho_vec, N);
//			mx E_vec = strain_vec * strain_vec * Y * h + K * rho_vec * h;
//			E_vec.sum(ROW);
//
//			i = mx::min(E_vec);
//
//			strain = strain_vec[:, i];
//			rho = rho_vec[:, i];
//		}
//
//		delta *= 0.9;
//
//		return strain.last() * Y.last();
//
//	}
//	
//}
//
//ax Bertoli()
//{
//	alpha = pi / 3;
//	ax h = mx::ones(N, 1);
//	ax b_prime = mx::ones(N, 1);
//	mx rho = mx::zeros(N, 1);
//
//	return LAM(f, h, b_prime, rho);
//}