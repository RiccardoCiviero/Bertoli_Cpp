#pragma once
#include "ax.h"
#include "mx.h"
#include "profile.h"

constexpr double pi = 3.14159265358979323846;
constexpr double delta_res = 0.1e-6;

constexpr double sqrt2 = 1.41421356237309504880;
constexpr double cos60 = 0.5;


mx strain_fcn_calc(const ax& f, const ax& h, const ax& b_prime, const mx& rho);

// ax LAM(Profile prof_i, ax K, double delta); // No wrapper
double LAM(const Profile& p, const ax& K, double delta, bool wrapper);


// ax setup(Profile profile_t, int i); // NO wrapper
double setup(const Profile& profile_t, int i, bool wrapper);

//void wrapper() {};