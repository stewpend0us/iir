/*
MIT License

Copyright (c) 2018 Stewart Wadsworth

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _C_IIR_H_
#define _C_IIR_H_

#ifndef FLOAT_TYPE
#error FLOAT_TYPE must be specified
#endif

#include <assert.h>

#define IIR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define IIR_ARRAY(...) {__VA_ARGS__}
#define IIR_INIT(name, num, den)							\
FLOAT_TYPE name##_num[] = num;								\
FLOAT_TYPE name##_den[] = den;								\
FLOAT_TYPE name##_history[] = den;							\
struct c_iir name =									\
{											\
	IIR_SIZE(name##_num),								\
	IIR_SIZE(name##_den),								\
	name##_num,									\
	name##_den,									\
	name##_history									\
};											\
iir_init_zero( &name );								\
assert( name.num_size > 0 && "cannot have a zero size numerator" );			\
assert( name.den_size > 0 && "cannot have a zero size denominator" );			\
assert( name.den_size >= name.num_size && "requirement of 'standard programming'" )

/*
struct c_iir represents a general discrete time transfer function such as:

	Output(z)    b[0] + b[1]*z^-1 + b[2]*z^-2 + ... + b[m]*z^-m
	--------- = ------------------------------------------------
	Input(z)     a[0] + a[1]*z^-1 + a[2]*z^-2 + ... + a[n]*z^-n

Where:
	b is an array of length m that represents the numerator coefficients.
	a is an array of length n that represents the denominator coefficients.
*/
struct c_iir
{
	unsigned int num_size; // number of elements in num
	unsigned int den_size; // number of elements in den
	FLOAT_TYPE * num; // pointer to array of size num_size
	FLOAT_TYPE * den; // pointer to array of size den_size
	FLOAT_TYPE * history; // pointer to array of size den_size
};

/*
IIR_calculate implements the "Standard Programming" approach as described
in "Discrete-Time Control Systems" by Katsuhiko Ogata.

The "Standard Programming" approach requires:
n >= m
a[0] == 1
size(history) == n
*/
FLOAT_TYPE iir_calculate( const struct c_iir * iir, FLOAT_TYPE input );

/*
check if iir is in the general form and updates it if possible.
*/
void iir_to_general_form( struct c_iir * iir );

/**/
void iir_init_zero( struct c_iir * iir );

/**/
FLOAT_TYPE iir_dc_gain( const struct c_iir * iir );

#endif
