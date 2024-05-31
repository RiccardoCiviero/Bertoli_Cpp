#pragma once
#include "mx.h"

class ax : mx
{
public:
	ax (int r) : mx(r, 1) {}
	ax (const ax& a) : mx(a) {}
	ax(mx& m, int i, Direction_t dir);
private:

};

