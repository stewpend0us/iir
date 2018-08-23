#include "IIR.h"
#include <string.h>

FLOAT_TYPE IIR_calculate(IIR * const iir, FLOAT_TYPE const input)
{
	size_t i;
	size_t const num_size = iir->num_size;
	size_t const den_size = iir->den_size;
	FLOAT_TYPE const * const num = iir->num;
	FLOAT_TYPE const * const den = iir->den;
	FLOAT_TYPE * const hist = iir->history;
	FLOAT_TYPE result = 0;

	for (i = 0; i < num_size; i++)
	{
		result += num[i] * hist[i];
	}
	memmove(hist + 1, hist, sizeof(FLOAT_TYPE) * (den_size - 1));
	hist[0] = input;
	for (i = 1; i < den_size; i++)
	{
		hist[0] -= den[i] * hist[i];
	}
	return result;
}

void IIR_to_general_form(IIR * const iir)
{
	size_t const num_size = iir->num_size;
	size_t const den_size = iir->den_size;
	FLOAT_TYPE * const num = iir->num;
	FLOAT_TYPE * const den = iir->den;
	FLOAT_TYPE const val = den[0];

	if (val != (FLOAT_TYPE)1.0)
	{
		size_t i;
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
