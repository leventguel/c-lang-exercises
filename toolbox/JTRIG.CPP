/* jtrig.cpp
 *
 * Programmed by Jack W. Crenshaw, Crenshaw Associates
 * CIS #72325,1327
 *
 * This file, with jtrig.h, defines fundamental functions related to
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

float arcsin(float x)
{
	if(x>1.0)
		return pi_over_2;
	if(x<-1.0)
		return -pi_over_2;
	return asin(x);
}

float arccos(float x)
{
	if(x>1.0)
		return 0.0;
	if(x<-1.0)
		return pi;
	return acos(x);
}

float arctan2(float y, float x)
{
	if(y == 0.0)
		return(x>0.0)? 0.0: -pi;
	if(x == 0.0)
		return signum((float)pi_over_2, y);
	return atan2(y, x);
}

double arcsin(double x)
{
	if(x>1.0)
		return pi_over_2;
	if(x<-1.0)
		return -pi_over_2;
	return asin(x);
}

double arccos(double x)
{
	if(x>1.0)
		return 0.0;
	if(x<-1.0)
		return pi;
	return acos(x);
}

double arctan2(double y, double x)
{
	if(y == 0.0)
		return(x>0.0)? 0.0: -pi;
	if(x == 0.0)
		return signum((double)pi_over_2, y);
	return atan2(y, x);
}

long double arcsin(long double x)
{
	if(x>1.0L)
		return pi_over_2;
	if(x<-1.0L)
		return -pi_over_2;
	return asinl(x);
}

long double arccos(long double x)
{
	if(x>1.0L)
		return 0.0L;
	if(x<-1.0L)
		return pi;
	return acosl(x);
}

long double arctan2(long double y, long double x)
{
	if(y == 0.0L)
		return(x>0.0L)? 0.0L: -pi;
	if(x == 0.0L)
		return signum((long double)pi_over_2, y);
	return atan2l(y, x);
}


