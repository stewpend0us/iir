#ifndef _IIR_H_
#define _IIR_H_

#ifndef FLOAT_TYPE
#error FLOAT_TYPE must be specified. ex FLOAT_TYPE double
#endif

#include <stddef.h>
#include <assert.h>

#define MACROARRAY(...) __VA_ARGS__
#define IIR_INIT(name, num, den)								\
FLOAT_TYPE name##_num[] = num;									\
FLOAT_TYPE name##_den[] = den;									\
FLOAT_TYPE name##_history[] = den;								\
IIR name =														\
{																\
	sizeof(name##_num) / sizeof(name##_num[0]),					\
	sizeof(name##_den) / sizeof(name##_den[0]),					\
	name##_num,													\
	name##_den,													\
	name##_history												\
};																\
memset(name.history, 0, sizeof(FLOAT_TYPE) * name.den_size);	\
assert(name.num_size > 0);										\
assert(name.den_size > 0);										\
assert(name.den_size >= name.num_size)

/*
The IIR struct represents the all the data required to solve the general
form of a discrete time transfer function such as:

	Output(z)    b[0] + b[1]*z^-1 + b[2]*z^-2 + ... + b[m]*z^-m
	--------- = ------------------------------------------------
	Input(z)     a[0] + a[1]*z^-1 + a[2]*z^-2 + ... + a[n]*z^-n

Where:
	b is an array of length m that represents the numerator coefficients.
	a is an array of length n that represents the denominator coefficients.
*/
typedef struct _IIR
{
	size_t const num_size; // number of elements in num
	size_t const den_size; // number of elements in den
	FLOAT_TYPE * const num; // pointer to array of size num_size
	FLOAT_TYPE * const den; // pointer to array of size den_size
	FLOAT_TYPE * const history; // pointer to array of size den_size
} IIR;

/*
IIR_calculate implements the "Standard Programming" approach as described
in "Discrete-Time Control Systems" by Katsuhiko Ogata.

The "Standard Programming" approach requires:
n >= m
a[0] == 1
sizeof(history) == n
*/
FLOAT_TYPE IIR_calculate(IIR * const iir, FLOAT_TYPE const input);


//check if iir is in the general form and updates it if possible.
void IIR_to_general_form(IIR * const iir);

#endif
