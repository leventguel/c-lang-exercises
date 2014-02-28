/* jmath.h
 *
 * Programmed by Jack W. Crenshaw, Crenshaw Associates
 * CIS #72325,1327
 *
 * This file defines certain fundamental math functions.
 * These functions replace functions max, min, abs, and
 * sqrt as defined in math.h.
 *
 * They are more general, and are defined via templates
 * so can be used without name changes for any numeric
 * type.
 *
 */


#include <iostream.h>
#include <math.h>

 #ifndef JMATH
 #define JMATH

// Return the maximum of two numbers

 template <class T>
 T max(T x, T y)
 {
	return (x > y)? x: y;
 };


// Return the minimum of two numbers

 template <class T>
 T min(T x, T y)
 {
	return (x < y)? x: y;
 };


// Return the absolute value of a number

 template <class T>
 T abs(T x)
 {
	return (x > 0)? x: -x;
 };


// Return a number with the magnitude of the first
// argument, and the sign of the second

 template <class T>
 T signum(T x, T y)
 {
	return (y > 0)? abs(x): -abs(x);
 };


// Return a number modulo the second argument

template <class T>
T mod(T x, T y){
	if(y == 0) return x;
	int i = (int)(x/y);
	if(x*y < 0)--i;
	x = x-((T) i)*y;
	if(x==y)x -= y;
	return x;
}

// return the square root of a number

 double square_root(double x);

 long double square_root(long double x);

#endif
