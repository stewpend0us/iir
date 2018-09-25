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
#include <stdio.h>

#define EPS 1.0E-14
#define TEXT(i) "\x1b[38;5;" #i "m"
#define BACK(i) "\x1B[48;5;" #i "m"
#define RESET "\x1b[0m"

void run_test( FLOAT_TYPE * input, int in_count, FLOAT_TYPE * expected, int expected_count, const struct c_iir * iir, const char name[] )
{
	printf("TEST %s:\n", name );
	FLOAT_TYPE output, error;
	FLOAT_TYPE * in = input;
	printf( "%10s%20s%20s%20s%10s\n", "INPUT", "EXPECTED", "CALCULATED", "ERROR", "STATUS" );
	for ( int i = 0; i<expected_count; i++ )
	{
		if (in_count == expected_count)
			in = &input[i];
		output = iir_calculate( iir, *in );
		error = output - expected[i];
		error = error < 0.0 ? -error : error;
		unsigned char good = error < EPS;
		printf( "%10g%20f%20f%20g%33s\n", *in, expected[i], output, error, good ? BACK(10) TEXT(0) " GOOD " RESET : BACK(09) TEXT(0) "  BAD " RESET );
	}
	printf("\n");
}

int main(int argc, const char * argv[])
{
	IIR_INIT(iira, IIR_ARRAY(1, 2, 3), IIR_ARRAY(1, 2, 3, 4) );
	FLOAT_TYPE inputa[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,  13,  14,  15, 16,   17,   18,   19,  20 };
	FLOAT_TYPE expecteda[] = { 1, 2, 3, 0, 5, 6, 7, -12, 25, 10, 11, -88, 173, -50, 15, -484, 1217, -942, 275, -2480 };
	run_test( inputa, IIR_SIZE(inputa), expecteda, IIR_SIZE(expecteda), &iira, "A" );

	IIR_INIT(iirb, IIR_ARRAY(0.0,  0.035,  -0.029), IIR_ARRAY(1.0,  -1.9,   0.94) );
	FLOAT_TYPE inputb[] = {1};
	FLOAT_TYPE expectedb[] =
	{
		0.0,
		0.035000000000000,
		0.072500000000000,
		0.110850000000000,
		0.148465000000000,
		0.183884500000000,
		0.215823450000000,
		0.243213125000000,
		0.265230894500000,
		0.281318362050000,
		0.291187847065000,
		0.294817649096500,
		0.292436957042250,
		0.284501628229565,
		0.271662354016458,
		0.254726942095479,
		0.234618577205940,
		0.212331971121536,
		0.188889282557334,
		0.165297584004691,
		0.142509484005019,
		0.121388290645127,
		0.102678837261023,
		0.086984797589524,
		0.074753008394735,
		0.066265006215843,
		0.061635683919051,
		0.060818693603305,
		0.063617974962371,
		0.069704580441398,
		0.078637806374028,
		0.089889526495739,
		0.102870562350318,
		0.116957913559609,
		0.131521707153958,
		0.145950804846488,
		0.159676124483607,
		0.172190879963154,
		0.183067114915403,
		0.191968091173900,
		0.198656285209932,
		0.202996936195404,
		0.204957270673932,
		0.204601694256791,
		0.202083384654406,
		0.197632838241989,
		0.191544011084637,
		0.184158753113341,
		0.175850260495788,
		0.167006267015458,
		0.158012662463329,
		0.149238167685794,
		0.141020615887480,
		0.133655292561565,
		0.127385676932743,
		0.122396811164340,
		0.118811404895468,
		0.116688666806910,
		0.116025746331388,
		0.116761571231143,
		0.118782783787666,
		0.121931412239291,
		0.126013866494247,
		0.130810818834136,
		0.136087521280266,
		0.141604120728418,
		0.147125559380544,
		0.152430689338320,
		0.157320283925097,
		0.161623691479664,
		0.165203946921770,
		0.167961229160479,
		0.169834625298446,
		0.170802232656198,
		0.170879694266236,
		0.170117320409023,
		0.168595996166881,
		0.166422111532593,
		0.163721775515058,
		0.160634588637973,
		0.157307249427994,
		0.153887260593494,
		0.150516980665325,
		0.147328238306232,
		0.144437690956436,
		0.141943068809370,
		0.139920401238754,
		0.138422277672824,
		0.137477150413937,
		0.137089644774026,
		0.137241803681548,
		0.137895160907357,
		0.138993510263323,
		0.140466218247399,
		0.142231915022534,
		0.144202393390259,
		0.146286547320311,
		0.148394190121747,
		0.150439606750227,
		0.152344714110989,
	};
	run_test( inputb, IIR_SIZE(inputb), expectedb, IIR_SIZE(expectedb), &iirb, "B" );


	IIR_INIT(iirc, IIR_ARRAY(0.0, 1.0), IIR_ARRAY(10.0,  -10.0) );
	iir_to_general_form( &iirc );
	FLOAT_TYPE inputc[] = {1};
	FLOAT_TYPE expectedc[] =
	{

		0.0,
		0.1,
		0.2,
		0.3,
		0.4,
		0.5,
		0.6,
		0.7,
		0.8,
		0.9,
		1.0,
		1.1,
		1.2,
		1.3,
		1.4,
		1.5,
		1.6,
		1.7,
		1.8,
		1.9,
		2.0,
		2.1,
		2.2,
		2.3,
		2.4,
		2.5,
		2.6,
		2.7,
		2.8,
		2.9,
		3.0,
		3.1,
		3.2,
		3.3,
		3.4,
		3.5,
		3.6,
		3.7,
		3.8,
		3.9,
		4.0,
		4.1,
		4.2,
		4.3,
		4.4,
		4.5,
		4.6,
		4.7,
		4.8,
		4.9,
		5.0,
		5.1,
		5.2,
		5.3,
		5.4,
		5.5,
		5.6,
		5.7,
		5.8,
		5.9,
		6.0,
		6.1,
		6.2,
		6.3,
		6.4,
		6.5,
		6.6,
		6.7,
		6.8,
		6.9,
		7.0,
		7.1,
		7.2,
		7.3,
		7.4,
		7.5,
		7.6,
		7.7,
		7.8,
		7.9,
		8.0,
		8.1,
		8.2,
		8.3,
		8.4,
		8.5,
		8.6,
		8.7,
		8.8,
		8.9,
		9.0,
		9.1,
		9.2,
		9.3,
		9.4,
		9.5,
		9.6,
		9.7,
		9.8,
		9.9,
	};
	run_test( inputc, IIR_SIZE(inputc), expectedc, IIR_SIZE(expectedc), &iirc, "C" );
}
