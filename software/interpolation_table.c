/*
 * interpolation_table.c
 *
 *  Created on: 08.09.2014
 *      Author: stefan
 */

#include <stdio.h>

#include "interpolation_table.h"



double interpolate_2d(interpolation_table_t table, double x)
{
	int i;

	// Go through list an search for matching x and x+1
	for (i = 0; i < (table.size - 1); i++)
	{
		// x-Vales are ascending through array
		if (table.values[i].x <= x && table.values[i + 1].x >= x )
		{
			double diff_x = x - table.values[i].x;
			double diff_n = table.values[i + 1].x - table.values[i].x;

			double diff_y = table.values[i + 1].y - table.values[i].y;

			return table.values[i].y + diff_y * diff_x / diff_n;
		}
	}

	// Out of range
	return -1;
}
