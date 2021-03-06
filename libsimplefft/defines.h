/*
*This is a part of libsimplefft
*
* Copyright (C) 2012  Kevin Krüger (kkevin@gmx.net)
* 
* libsimplefft is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
* 
* libsimplefft is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public
* License along with libsimplefft; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef DEFINES_H
#define DEFINES_H

#include<time.h>

#define FLAG_OVERFLOW (1)
#define FLAG_CARRY    (2)
#define FLAG_ZERO     (3)
#define FLAG_MINUS    (4)

struct CPLX_SAMPLES;

/**Type holding a buffer of complex samples
*/
typedef struct CPLX_SAMPLES{

	//void* buffer;
	//clock_t exec_time;
	
	//flexible integers
	void* re;
	void* im;
	
	//precision type of the fft (8/16-Bit-Integer, Single or Double precision)
	uint8_t type;	
	size_t type_size;
	//total lenght of the allocated array
	uint32_t length;
	//Length of a base side of a fft
	uint32_t base_length;

	//required for multi dimensional FFTs
	uint32_t dimension;
	uint32_t* dimension_strides;
}CPLX_SAMPLES;

/**Marker for a normal time domain to frequency domain transform
*/
#define FFT_MODE_NORMAL  (0)

/**Marker for a inverse frequency domain to time domain transform
*/
#define FFT_MODE_INVERSE (1)

/**Marker to determine multidimensional Fourier Transforms
*/
#define FFT_MODE_MD      (2)

/**marker for single precision fft
*/
#define CPLX_TYPE_SP    (0)
/**marker for double precision fft
*/
#define CPLX_TYPE_DP    (1)
/**marker for 16-Bit integer based fft
*/
#define CPLX_TYPE_INT   (2)

/**marker for 8-Bit integer sample fft
*/
#define CPLX_TYPE_BYTE  (3)

/**marker for 32-Bit integer based fft
*/
#define CPLX_TYPE_INT32 (4)

/**Holds data required to perform a FFT.
*/
struct FFT_CONTEXT;

typedef struct FFT_CONTEXT{
	uint8_t type;
	uint8_t mode;
	uint32_t samples;
	uint32_t stages;

	CPLX_SAMPLES* twiddle_factors;
	uint32_t* bit_rev_indices;
}FFT_CONTEXT;


/**Holds the data required to perform a fast colvolution.
*/
struct CONVOLUTION_CONTEXT;
typedef struct CONVOLUTION_CONTEXT{
	uint8_t type;
	FFT_CONTEXT* fft_context;
	FFT_CONTEXT* ifft_context;
	uint32_t samples;
	CPLX_SAMPLES* kernel;
}CONVOLUTION_CONTEXT;

#endif
