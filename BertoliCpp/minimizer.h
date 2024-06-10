#pragma once
#include "ax.h"
#include "mx.h"
#include "profile.h"

constexpr double pi = 3.14159265358979323846;
constexpr double delta_res = 50e4;

constexpr double sqrt2 = 1.41421356237309504880;
constexpr double cos60 = 0.5;


mx strain_fcn_calc(const ax& f, const ax& h, const ax& b_prime, const mx& rho);

ax LAM(const Profile& p, const ax& K, double delta); // No wrapper
double LAM_wrapped(const Profile& p, const ax& K, double delta);


ax setup(const Profile& profile_t, int i); // NO wrapper
double setup_wrapped(const Profile& profile_t, int i);

//void wrapper() {};