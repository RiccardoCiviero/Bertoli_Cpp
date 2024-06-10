#include "minimizer.h"

mx strain_fcn_calc(const ax& f, const ax& h, const ax& b_prime, const mx& rho)
{
	mx p = h * b_prime * rho;

	return p.cumsum(ROW) + f;
}

double setup(const Profile& profile_t, int i, bool wrapper)
{
	auto alpha = pi / 3;
	Profile prof_i;

	prof_i.h = profile_t.h.slice(0, i); // Serve una versione di slice const -> altrimenti mi sovrascrivi profile_t: è corretto passare per const reference profile e assegnare a prof_i solo una "view" di profile_t
	prof_i.x = profile_t.x.slice(0, i);
	prof_i.T = profile_t.T(i) * ax::ones(prof_i.h.size(ROW));
	prof_i.N = prof_i.h.size(ROW);

	prof_i.a_fcn();

	prof_i.a.print();
	prof_i.b = prof_i.a / sqrt2;

	prof_i.b_eff = prof_i.b / 4.0; // This is b_prime

	prof_i.moduli_fcn();

	prof_i.h.print();
	prof_i.b.print();
	ax x = ((prof_i.h.sum() - prof_i.h.cumsum()) / prof_i.b);
	x.print();
	ax y = log(x);
	ax K = prof_i.G * prof_i.b * prof_i.b * (1.0 - (cos60 * cos60) * prof_i.nu) / (2.0 * pi * (1.0 - prof_i.nu) * (y - 1.0));
	K.set(K.size(ROW) - 1, K(K.size(ROW) - 2));

	prof_i.f = (prof_i.a(0) - prof_i.a) / prof_i.a;

	const double delta = abs(prof_i.f.sum() / (prof_i.N * prof_i.b_eff(0) * prof_i.h(1)));

	return LAM(prof_i, K, delta, wrapper);
}

double LAM(const Profile& p, const ax& K, double delta, bool wrapper)
{
	const int N = p.f.size(ROW);
	ax rho = ax::zeros(N);
	mx rho_vec_initializer = mx::zeros(N, 9);
	ax strain = p.f;

	mx mod_matrix = mx({ { 1.0, 1.0 }, { 1.0, 0.0 }, { 1.0, -1.0 }, { 0.0, 1.0 }, { 0.0, 0.0 }, { 0.0, -1.0 }, { -1.0, 1.0 }, { -1.0, 0.0 }, { -1.0, -1.0 } });

	while (delta > delta_res)
	{
		mx delta_vec = mod_matrix * delta;

		for (int i = 0; i < N - 1; ++i)
		{
			mx rho_vec = rho * rho_vec_initializer;

			for (int j = 0; j < mod_matrix.size(COL); ++j) {
				rho_vec(i, j) = rho_vec(i, j) * delta_vec(0, j);
				rho_vec(i + 1, j) = rho_vec(i, j) * delta_vec(1, j);
			}

			rho_vec = rho_vec.maximum(0);

			mx strain_vec = strain_fcn_calc(strain, p.h, p.b_eff, rho_vec);
			mx E_vec = strain_vec * strain_vec * p.Y * p.h + K * rho_vec * p.h;
			auto E_conf = E_vec.sum(ROW);

			auto k = ax(E_conf).minimum_index();

			strain = ax(strain_vec, k, ROW);
			rho = ax(rho_vec, k, ROW);
		}

		delta *= 0.9;

	}
	return strain.last() / p.Y.last();

}