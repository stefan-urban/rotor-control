/*
 * interpolation_table.h
 *
 *  Created on: 08.09.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef INTERPOLATION_TABLE_H_
#define INTERPOLATION_TABLE_H_


/**
 * Defined point in interpolation table
 */
typedef struct {
	double x;
	double y;
} interpolation_table_point_t;

/**
 * Table of points for interpolation
 */
typedef struct {
	/**
	 * Interpolation points
	 */
	interpolation_table_point_t *values;

	/**
	 * Amount of points
	 */
	int size;
} interpolation_table_t;

/**
 * Interpolate 2D table
 *
 * @param interpolation table
 * @param input x-value
 * @return interpolated y-value
 */
double interpolate_2d(interpolation_table_t table, double x);


#endif /* INTERPOLATION_TABLE_H_ */
