/* jmath.cpp
 *
 * Programmed by Jack W. Crenshaw, Crenshaw Associates
 * CIS #72325,1327
 *
 * This file, with jmath.h, defines certain fundamental
 * math functions. These functions replace functions max,
 * fmax, min, fmin, abs, fabs, and sqrt as defined in math.h.
 *
 * They are more general, and are defined via templates
 * so can be used without name changes for any numeric
 * type.
 *
 */
#include <math.h>

// Return the square root of a number


float square_root(float x){
	if(x < 0.0) return 0.0;
	else return sqrt(x);
}


double square_root(double x){
	if(x < 0.0) return 0.0;
	else return sqrt(x);
}


long double square_root(long double x){
	if(x < 0.0L) return 0.0L;
	else return sqrtl(x);
}
