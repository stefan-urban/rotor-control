/*
 * interpolation_table.h
 *
 *  Created on: 08.09.2014
 *      Author: stefan
 */

#ifndef INTERPOLATION_TABLE_H_
#define INTERPOLATION_TABLE_H_


typedef struct {
	double x;
	double y;
} interpolation_table_point_t;

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
 * Returns interpolated y value
 */
double interpolate_2d(interpolation_table_t table, double x);


#endif /* INTERPOLATION_TABLE_H_ */
