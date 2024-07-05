#include "profile.h"

void Profile::h_profile_fcn() {
    h = ax(h_tot / resolution);
    double h_i = 0;
    for (int i = 0; i < h.size(ROW); i++) {
        h.set(i, h_i);
        h_i = h_i + resolution;
    }
}

void Profile::x_profile_fcn() {
    x = ax(h.size(ROW));
    for (int i = 0; i < h.size(ROW); i++) {
        if (h(i) < h_graded) {
            x.set(i, xi + (xf - xi) * h(i) / h_graded);
        }
        else {
            x.set(i, xf);
        }
    }
}

void Profile::T_profile_fcn() {
    T = ax(h.size(ROW));
    const auto h_T_ramp_start = x_T_ramp_start / dx_m;
    for (int i = 0; i < h.size(ROW); i++) {
        if (h(i) < h_T_ramp_start) {
            T.set(i, Ti_K);
        }
        else if (h(i) < h_graded) {
            T.set(i, Ti_K + resolution * (Tf_K - Ti_K) / (h_graded - h_T_ramp_start));
        }
        else {
            T.set(i,Tf_K);
        }
    }
}

void Profile::a_fcn() {
    a = ax(h.size(ROW));
    for(int i = 0; i < h.size(ROW); i ++) {
        //a.set(i, (0.54310 + 0.02 * x(i) + 0.0027 * x(i) * x(i)) * 1e-9 * (1 + (2.6 + 2.55 * x(i)) * T(i) * 1e-6));
        a.set(i, 0.543108e-9 * (1 - x(i)) + 0.56576e-9 * x(i));
    }
    
}

void Profile::a_fcn_n(double T) {
    a = ax(h.size(ROW));
    for (int i = 0; i < h.size(ROW); i++) {
        // a.set(i, (0.54310 + 0.02 * x(i) + 0.0027 * x(i) * x(i)) * 1e-9 * (1 + (2.6 + 2.55 * x(i)) * T * 1e-6));
        a.set(i, 0.543108e-9 * (1 - x(i)) + 0.56576e-9 * x(i));
    }
}

void Profile::moduli_fcn() {
    nu = ax(h.size(ROW));
    G = ax(h.size(ROW));
    Y = ax(h.size(ROW));
    double c11si_Pa, c12si_Pa, c44si_Pa, c11ge_Pa, c12ge_Pa, c44ge_Pa, C12_Pa, C44_Pa, C11_Pa;
    for (int i = 0; i < T.size(ROW); i++) {
        //c11si_Pa = -36714285.714 * T(i) + 180385714285.6;
        //c12si_Pa = -19857142.857 * T(i) + 71842857142.8;
        //c44si_Pa = -571428.571 * T(i) + 79828571428.4;
        //
        //c11ge_Pa = -13142857.143 * T(i) + 134457142857.2;
        //c12ge_Pa = -2714285.714 * T(i) + 48985714285.6;
        //c44ge_Pa = -7142857.143 * T(i) + 69857142857.2;

        c11si_Pa = 160.1e9;
        c11ge_Pa = 124e9;
        c12si_Pa = 57.8e9;
        c12ge_Pa = 41.3e9;
        c44si_Pa = 79.6e9;
        c44ge_Pa = 67e9;


        C12_Pa = c12si_Pa * (1 - x(i)) + c12ge_Pa * x(i);
        C44_Pa = c44si_Pa * (1 - x(i)) + c44ge_Pa * x(i);
        C11_Pa = c11si_Pa * (1 - x(i)) + c11ge_Pa * x(i);

        nu.set(i, C12_Pa / (C11_Pa + C12_Pa)); // Poisson

        // G_Pa = 3 / (1 / C44_Pa + 4 / (C11_Pa - C12_Pa)) # Shear
        G.set(i, C44_Pa);
        Y.set(i, C11_Pa + C12_Pa - 2 * C12_Pa * C12_Pa / C11_Pa); // Biaxial = E / (1 - nu);
    }
}