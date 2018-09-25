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

#include "c_iir.h"
#include <string.h>
#include <stdio.h>

FLOAT_TYPE iir_calculate( const struct c_iir * iir, FLOAT_TYPE input)
{
	unsigned int i;
	unsigned int num_size = iir->num_size;
	unsigned int den_size = iir->den_size;
	FLOAT_TYPE const * num = iir->num;
	FLOAT_TYPE const * den = iir->den;
	FLOAT_TYPE * hist = iir->history;
	FLOAT_TYPE result = 0;

	memmove(hist + 1, hist, sizeof(FLOAT_TYPE) * (den_size - 1));
	hist[0] = input;
	for (i = 1; i < den_size; i++)
	{
		hist[0] -= den[i] * hist[i];
	}
	for (i = 0; i < num_size; i++)
	{
		result += num[i] * hist[i];
	}
	return result;
}

void iir_to_general_form( struct c_iir * iir )
{
	unsigned int num_size = iir->num_size;
	unsigned int den_size = iir->den_size;
	FLOAT_TYPE * num = iir->num;
	FLOAT_TYPE * den = iir->den;
	FLOAT_TYPE val = den[0];

	if (val != 1.0)
	{
		unsigned int i;
		for (i = 0; i < num_size; i++)
		{
			num[i] /= val;
		}
		for (i = 0; i < den_size; i++)
		{
			den[i] /= val;
		}
	}
}

void iir_init_zero( struct c_iir * iir )
{
	memset( iir->history, 0, sizeof(FLOAT_TYPE) * iir->den_size);				\
}

void iir_dcgain( const struct c_iir * iir )
{
	unsigned int i;
	unsigned int num_size = iir->num_size;
	unsigned int den_size = iir->den_size;
	FLOAT_TYPE const * num = iir->num;
	FLOAT_TYPE const * den = iir->den;
	FLOAT_TYPE * hist = iir->history;
	FLOAT_TYPE n = 0;
	FLOAT_TYPE d = 0;
	for (i = 0; i < den_size; i++)
	{
		d += den[i];
	}
	for (i = 0; i < num_size; i++)
	{
		n += num[i];
	}
	return n/d; // will return NaN and +/-Inf
	
}
