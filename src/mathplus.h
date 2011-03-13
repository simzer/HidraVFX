/*
 * mathplus.h
 *
 *  Created on: 5 Mar 2011
 *      Author: yals
 */

#ifndef MATHPLUS_H_
#define MATHPLUS_H_

#define PI 3.14159265358979323846

static inline double sign(double a) { return (a > 0 ? 1 : a<0 ? -1 : 0); }
static inline double sqr(double a) { return (a * a); }
static inline double min(double a, double b) { return (a < b ? a : b ); }
static inline double max(double a, double b) { return (a > b ? a : b ); }
static inline double limit(double min, double var, double max)
  { return (min > var ? min : (var > max ? max : var) ); }

#endif /* MATHPLUS_H_ */
