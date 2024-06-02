#pragma once
#include "ax.h"

class sample
{
private:
	ax* h, *T, *x;
	ax* Y, *Gn, nu;

public:
	sample(ax* h, ax T, ax x, ax* Y, ax Gn, ax nu);
	~sample();
};


