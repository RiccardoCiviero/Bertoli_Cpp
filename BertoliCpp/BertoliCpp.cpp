 // BertoliCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "mx.h"
#include "ax.h"
#include "profile.h"

constexpr double pi = 3.14159265358979323846;
constexpr double delta_res = 0.1e-6;

constexpr double sqrt2 = 1.41421356237309504880;
constexpr double cos60 = 0.5;

//
//mx strain_fcn_calc(ax f, ax h, ax b_prime, mx rho);
//double LAM(profile prof_i, ax K, double delta);
//double Bertoli(profile profile_t, int i);
//void Bertoli_Wrapper();



void Example() {
	mx m({ {1, 2, 3}, {4, 5, 6} });
	m.print();

	std::cout << m(1, 2) << std::endl;
	m(1, 2) = 10;

	m.print();

	double& v = m(1, 2);
	v = 20;
	m.print();

	mx div = m * m;
	div.print();

	ax a = m(0, ROW);
	a.print();

	ax diva = a;
	diva.print();
	ax a1 = m(1, COL);
	//ax sum = a + a1;

	a1.minimum_index();

}


int main()
{
	Example();
}
//
//mx strain_fcn_calc(ax f, ax h, ax b_prime, mx rho)
//{
//	mx p = h * b_prime * rho;
//
//	return p.cumsum(ROW) + f;
//}
//
//double LAM(profile p, ax K, double delta)
//{
//	int N = p.f.size(ROW);
//	mx rho = mx::zeros(N, 1);
//	mx rho_vec_initializer = mx::zeros(N, N);
//	ax strain = p.f;
//
//	mx mod_matrix = mx({ { 1.0, 1.0 }, { 1.0, 0.0 }, { 1.0, -1.0 }, { 0.0, 1.0 }, { 0.0, 0.0 }, { 0.0, -1.0 }, { -1.0, 1.0 }, { -1.0, 0.0 }, { -1.0, -1.0 } });
//
//	while (delta > delta_res)
//	{
//		mx delta_vec = mod_matrix * delta;
//
//		for (int i = 0; i < N-1; i++)
//		{
//			mx rho_vec = rho_vec * delta_vec; // bohh
//
//			rho_vec = rho_vec.maximum(0);
//
//			mx strain_vec = strain_fcn_calc(strain, p.h, p.b_eff, rho_vec);
//			mx E_vec = strain_vec * strain_vec * p.Y * p.h + K * rho_vec * p.h;
//			E_vec.sum(ROW);
//
//			i = E_vec.minimum();
//
//			strain = ax(strain_vec, i, ROW);
//			rho = ax(rho_vec,i,ROW);
//		}
//
//		delta *= 0.9;
//
//		return strain.last() * p.Y.last();
//
//	}
//	
//}
//
//double Bertoli(profile profile_t, int i)
//{
//	double alpha = pi / 3;
//	profile prof_i;
//
//	prof_i.h = profile_t.h(i);
//	prof_i.x = profile_t.x(i);
//
//	a_fcn_n(prof_i.x, profile_t.T.get(i,1));
//
//	prof_i.b  = prof_i.a / sqrt2;
//	prof_i.b_eff = prof_i.b / 4.0; // This is b_prime
//
//	prof_i.moduli_fcn();
//	
//	ax K = prof_i.G * prof_i.b * prof_i.b * (1 - (cos60* cos60) * prof_i.nu) / (2 * pi * (1 - prof_i.nu) * (std::log((prof_i.h.sum() - prof_i.h.cumsum(ROW))/prof_i.b) - 1));
//	K.set(K.size(ROW), K(K.size(ROW) - 2));
//
//	prof_i.f = (prof_i.a(0) - prof_i.a) / prof_i.a;
//
//	double delta = abs(prof_i.f.sum() / (prof_i.N * prof_i.b_eff(0) * prof_i.h(1)));
//
//	return LAM(prof_i, K, delta); 
//}
//
