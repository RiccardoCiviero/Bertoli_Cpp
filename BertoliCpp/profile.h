#pragma once
#include "ax.h"
#include "mx.h"

class Profile
{
public:
	ax h, x, T, a, b, b_eff;
	ax f, Y, G, nu, strain;
	int N;
    double h_tot, h_graded, h_const, xi, xf, dx_m, x_T_ramp_start, Ti_K, Tf_K, resolution;

    void h_profile_fcn();
	void x_profile_fcn();
	void T_profile_fcn();
	void a_fcn();
    void moduli_fcn();
	void a_fcn_n(double T);
};

