// BertoliCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "mx.h"
#include "ax.h"

//ax strain_fcn_calc(ax f, ax h, ax b_prime, mx rho);
//ax LAM();
//ax Bertoli();
//void Bertoli_Wrapper();

int main()
{

}

//ax strain_fcn_calc(ax f, ax h, ax b_prime, mx rho)
//{
//	mx p = h * b_prime * rho;
//	return f + p.cumsum(ROW);
//}
//
//ax LAM()
//{
//	ax rho = zeros(3, 3);
//
//	while (delta > delta_res)
//	{
//		mx delta_vec = delta ; // QUi va il vettore 9x2
//
//		for (int i = 0; i < N-1; i++)
//		{
//			rho_vec[j, j+1] = rho_vec[j, j+1] * delta_vec
//			rho_vec = rho_vec.maximum(0)
//		}
//
//	}
//	
//}