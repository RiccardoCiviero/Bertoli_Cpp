 // BertoliCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#include "mx.h"
#include "ax.h"
#include "profile.h"
#include "minimizer.h"



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


	ax diva = a;
	diva.print();
	ax a1 = m(1, COL);
	ax sum = a + a1;

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



	std::cout << "Resolution: " << p.h_tot / p.resolution << std::endl;
	//p.h.print();

	p.strain = ax(p.h.size(ROW));
	std::cout << "Stress: " << setup(p, p.h.size(ROW) - 1, true) << std::endl; // -1??


	// Open the file
	//std::ofstream file("/home/ricca/dev/Bertoli_Cpp/BertoliCpp/output.csv");

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
