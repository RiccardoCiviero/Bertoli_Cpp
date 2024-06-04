#include "profile.h"

void profile::h_profile_fcn() {
    int j = 0;
    for (double i = 0; i < h_tot; i += resolution) {
        h.set(j, i);
        j++;
    }
}

void profile::x_profile_fcn() {
    for (double i = 0; i < h_tot; i += resolution) {
        if (i < h_graded) {
            x.set(i, xi + (xf - xi) * i / h_graded);
        }
        else {
            x.set(i, xf);
        }
    }
}

void profile::T_profile_fcn() {
    double h_T_ramp_start = x_T_ramp_start / dx_m;
    for (double i = 0; i < h_tot; i += resolution) {
        if (i < h_T_ramp_start) {
            T.set(i, Ti_K);
        }
        else if (i < h_graded) {
            T.set(i, Ti_K + resolution * (Tf_K - Ti_K) / (h_graded - h_T_ramp_start));
        }
        else {
            T.set(i,Tf_K);
        }
    }
}

void profile::a_fcn() {
    for(int i = 0; i < h.size(ROW); i ++) {
        a.set(i, (0.54310 + 0.02 * x(i) + 0.0027 * x(i) * x(i)) * 1e-9 * (1 + (2.6 + 2.55 * x(i)) * T(i) * 1e-6));
	}
    
}

ax a_fcn_n(profile p, double T) {
    ax temp;
    for (int i = 0; i < p.h.size(ROW); i++) {
        p.a.set(i, (0.54310 + 0.02 * p.x(i) + 0.0027 * p.x(i) * p.x(i)) * 1e-9 * (1 + (2.6 + 2.55 * p.x(i)) * T * 1e-6));
    }
    return temp;
}

void profile::moduli_fcn() {

    double c11si_Pa, c12si_Pa, c44si_Pa, c11ge_Pa, c12ge_Pa, c44ge_Pa, C12_Pa, C44_Pa, C11_Pa;
    for (int i = 0; i < T.size(ROW); i++) {
        c11si_Pa = -36714285.714 * T(i) + 180385714285.6;
        c12si_Pa = -19857142.857 * T(i) + 71842857142.8;
        c44si_Pa = -571428.571 * T(i) + 79828571428.4;

        c11ge_Pa = -13142857.143 * T(i) + 134457142857.2;
        c12ge_Pa = -2714285.714 * T(i) + 48985714285.6;
        c44ge_Pa = -7142857.143 * T(i) + 69857142857.2;

        C12_Pa = c12si_Pa * (1 - x(i)) + c12ge_Pa * x(i);
        C44_Pa = c44si_Pa * (1 - x(i)) + c44ge_Pa * x(i);
        C11_Pa = c11si_Pa * (1 - x(i)) + c11ge_Pa * x(i);

        nu.set(i, C12_Pa / (C11_Pa + C12_Pa)); // Poisson

        // G_Pa = 3 / (1 / C44_Pa + 4 / (C11_Pa - C12_Pa)) # Shear
        G.set(i, C44_Pa);
        Y.set(i, C11_Pa + C12_Pa - 2 * C12_Pa * C12_Pa / C11_Pa); // Biaxial = E / (1 - nu);
    }
}