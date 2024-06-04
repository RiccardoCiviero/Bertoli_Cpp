 // BertoliCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "mx.h"
#include "ax.h"
#include "profile.h"

#include <fstream>

constexpr double pi = 3.14159265358979323846;
constexpr double delta_res = 0.1e-6;

constexpr double sqrt2 = 1.41421356237309504880;
constexpr double cos60 = 0.5;


mx strain_fcn_calc(ax f, ax h, ax b_prime, mx rho);
ax LAM(Profile prof_i, ax K, double delta); // No wrapper
ax Bertoli(Profile profile_t, int i); // NO wrapper

double Bertoli(Profile profile_t, int i, bool wrapper);
double LAM(Profile prof_i, ax K, double delta, bool wrapper);
void Bertoli_Wrapper();



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
	div.cumsum(COL).print();

	ax a = m(0, ROW);
	a.print();

	ax diva = a;
	diva.print();
	ax a1 = m(1, COL);
	//ax sum = a + a1;

	a1.minimum_index();
	a1.print();
	ax cs = a1.cumsum();
	cs.print();

	ax csd = 2.0 - cs;
	csd.print();
}


int main()
{
	//Example();
	Profile p;
	p.xi = 0;
	p.xf = 0.1;

	p.dx_m = 0.07 * 1e6;
	
	p.x_T_ramp_start = 0.01;
	
	p.Tf_K = 720 + 273.15;
	p.Ti_K = 520 + 273.15;
	
	p.h_const = 2 * 1e-6;
	
	p.h_graded = (p.xf - p.xi) / p.dx_m;
	p.h_tot = p.h_graded + p.h_const;
	p.resolution = 0.05e-6; // Step size for the discretization of the profiles
	p.N = p.h_tot / p.resolution;
	
	p.h_profile_fcn();
	p.x_profile_fcn();
	p.T_profile_fcn();
	p.a_fcn();
	p.moduli_fcn();

	
	std::cout << p.h_tot / p.resolution<<std::endl;
	//p.h.print();

	p.strain = ax(p.h.size(ROW));
	std::cout << Bertoli(p, p.h.size(ROW)-1, true) << std::endl; // -1??



	// Open the file
	std::ofstream file("/home/ricca/dev/Bertoli_Cpp/BertoliCpp/output.csv");

	// Check if the file is opened successfully
	//if (!file.is_open())
	//{
	//	std::cout << "Failed to open the file!" << std::endl;
	//	return 1;
	//}
	//for(int i = 0; i < strain.size(ROW); i++)
	//{
	//	file << p.h(i) << "," <<strain(i) << std::endl;
	//}
}

mx strain_fcn_calc(ax f, ax h, ax b_prime, mx rho)
{
	mx p = h * b_prime * rho;

	return p.cumsum(ROW) + f;
}

ax LAM(Profile p, ax K, double delta)
{
	int N = p.f.size(ROW);
	mx rho = mx::zeros(N, 1);
	mx rho_vec_initializer = mx::zeros(N, N);
	ax strain = p.f;

	mx mod_matrix = mx({ { 1.0, 1.0 }, { 1.0, 0.0 }, { 1.0, -1.0 }, { 0.0, 1.0 }, { 0.0, 0.0 }, { 0.0, -1.0 }, { -1.0, 1.0 }, { -1.0, 0.0 }, { -1.0, -1.0 } });

	while (delta > delta_res)
	{
		mx delta_vec = mod_matrix * delta;

		for (int i = 0; i < N-1; i++)
		{
			mx rho_vec = rho_vec * delta_vec; // bohh

			rho_vec = rho_vec.maximum(0);

			mx strain_vec = strain_fcn_calc(strain, p.h, p.b_eff, rho_vec);
			mx E_vec = strain_vec * strain_vec * p.Y * p.h + K * rho_vec * p.h;
			E_vec.sum(ROW);

			i = E_vec.minimum();

			strain = ax(strain_vec, i, ROW);
			rho = ax(rho_vec,i,ROW);
		}

		delta *= 0.9;


	}
	return strain;
	
}

ax Bertoli(Profile profile_t, int i)
{
	double alpha = pi / 3;
	Profile prof_i;

	prof_i.h = profile_t.h(i);
	prof_i.x = profile_t.x(i);

	prof_i.a_fcn_n(profile_t.T(i));

	prof_i.b  = prof_i.a / sqrt2;
	prof_i.b_eff = prof_i.b / 4.0; // This is b_prime

	prof_i.moduli_fcn();
	
	ax K = prof_i.G * prof_i.b * prof_i.b * (1.0 - (cos60* cos60) * prof_i.nu) / (2 * pi * (1 - prof_i.nu) * (log((prof_i.h.sum() - prof_i.h.cumsum())/prof_i.b) - 1));
	K.set(K.size(ROW), K(K.size(ROW) - 2));

	prof_i.f = (prof_i.a(0) - prof_i.a) / prof_i.a;

	double delta = abs(prof_i.f.sum() / (prof_i.N * prof_i.b_eff(0) * prof_i.h(1)));

	return LAM(prof_i, K, delta); 
}

double Bertoli(Profile profile_t, int i, bool wrapper)
{
	double alpha = pi / 3;
	Profile prof_i;

	prof_i.h = profile_t.h.slice(0,i);
	prof_i.x = profile_t.x.slice(0,i);
	prof_i.T = profile_t.T(i) * ax::ones(prof_i.h.size(ROW));

	prof_i.a_fcn();

	prof_i.a.print();
	prof_i.b = prof_i.a / sqrt2;
	
	prof_i.b_eff = prof_i.b / 4.0; // This is b_prime

	prof_i.moduli_fcn();

	prof_i.h.print();
	prof_i.b.print();
	ax x = ((prof_i.h.sum() - prof_i.h.cumsum()) / prof_i.b);
	ax y = log(x);
	ax K = prof_i.G * prof_i.b * prof_i.b * (1.0 - (cos60 * cos60) * prof_i.nu) / (2.0 * pi * (1.0 - prof_i.nu) * (y - 1.0));
	K.set(K.size(ROW)-1, K(K.size(ROW) - 2));

	prof_i.f = (prof_i.a(0) - prof_i.a) / prof_i.a;

	double delta = abs(prof_i.f.sum() / (prof_i.N * prof_i.b_eff(0) * prof_i.h(1)));

	return LAM(prof_i, K, delta, wrapper);
}

double LAM(Profile p, ax K, double delta, bool wrapper)
{
	int N = p.f.size(ROW);
	mx rho = mx::zeros(N, 1);
	mx rho_vec_initializer = mx::zeros(N, N);
	ax strain = p.f;

	mx mod_matrix = mx({ { 1.0, 1.0 }, { 1.0, 0.0 }, { 1.0, -1.0 }, { 0.0, 1.0 }, { 0.0, 0.0 }, { 0.0, -1.0 }, { -1.0, 1.0 }, { -1.0, 0.0 }, { -1.0, -1.0 } });

	while (delta > delta_res)
	{
		mx delta_vec = mod_matrix * delta;

		for (int i = 0; i < N - 1; i++)
		{
			mx rho_vec = rho_vec_initializer * delta_vec; // bohh

			rho_vec = rho_vec.maximum(0);

			mx strain_vec = strain_fcn_calc(strain, p.h, p.b_eff, rho_vec);
			mx E_vec = strain_vec * strain_vec * p.Y * p.h + K * rho_vec * p.h;
			E_vec.sum(ROW);

			i = E_vec.minimum();

			strain = ax(strain_vec, i, ROW);
			rho = ax(rho_vec, i, ROW);
		}

		delta *= 0.9;


	}
	return strain.last() / p.Y.last();

}