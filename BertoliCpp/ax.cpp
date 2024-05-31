#include "ax.h"

ax::ax(mx& m, int i, Direction_t dir)
{
	double *data;
	int r, c;
	if (dir == ROW) {
		data = new double[m.size(COL)];
		for (int j = 0; j < m.size(COL); j++) {
			data[j] = m.get(i, j);
		}
	}
	else {
		data = new double[m.size(ROW)];
		for (int j = 0; j < m.size(COL); j++) {
			data[j] = m.get(j, i);
		}
	}




}
