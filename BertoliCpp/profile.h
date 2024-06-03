#pragma once
#include "ax.h"
#include "mx.h"

typedef struct name
{
	ax h, x, T, a, b, b_eff;
	ax f, Y, G, nu;
	int N;
    double h_tot, h_graded, h_const, xi, xf, dx_m, x_T_ramp_start, Ti_K, Tf_K, resolution;

    void h_profile_fcn();
	void x_profile_fcn();
	void T_profile_fcn();
	void a_fcn();
    void moduli_fcn();
}profile;


ax a_fcn_n(profile p, double T);