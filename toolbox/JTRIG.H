/* jtrig.h
 *
 * Programmed by Jack W. Crenshaw, Crenshaw Associates
 * CIS #72325,1327
 *
 * This file defines fundamental functions related to
 * trigonometry. These functions replace functions asin,
 * asinl, acos, acosl, atan2, and atan2 as defined in
 * math.h. The functions use operator overloading to allow
 * their use for float, double, or long double types without
 * name changes.  Also, the functions return reasonable values
 * when the input arguments are out of range.
 *
 * For convenience, conversions between degrees and radians
 * are also provided.  Functions mod_360 and mod_180 reduce
 * angles (in radians) to ranges of 0..360 or -180..180,
 * respectively.
 *
 */

#include <constant.h>
#include <jmath.h>

#ifndef JTRIG
#define JTRIG

template <class T>
T to_radians(T x)
{
	return (T)radians_per_degree * x;
}

template <class T>
T to_degrees(T x)
{
	return (T)degrees_per_radian *x;
}


template <class T>
T mod_360(T x)
{
	return mod(x, two_pi);
}


template <class T>
T mod_180(T x)
{
	T temp;
	if(abs(x) < pi) then
		temp = x;
	else
		temp = mod(x + pi, (T)2.0*pi) - pi;
	if temp = - pi then
		temp := pi;
	return temp;
}


float arcsin(float x);

float arccos(float x);

float arctan2(float y, float x);

double arcsin(double x);

double arccos(double x);

double arctan2(double y, double x);

long double arcsin(long double x);

long double arccos(long double x);

long double arctan2(long double y, long double x);

#endif