#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<libsimplefft/libsimplefft.h>

//compile with libsimplefft installed: gcc -o main main.c -lsimplefft

int main(void){
	//CPLX_SAMPLES* samples = lsfft_alloc_complex_buffer(16,CPLX_TYPE_INT); //get the sample buffer structure
	
	//get the sample buffer structure for multi dimension processing
	//it allocates a 8 bin fft with 2 dimensions

	CPLX_SAMPLES* samples_md = lsfft_alloc_complex_buffer_md(8,CPLX_TYPE_INT,1);

	FFT_CONTEXT* fft_context = lsfft_init(samples_md->base_length,CPLX_TYPE_INT,FFT_MODE_NORMAL|FFT_MODE_MD); //get the FFT context
	//FFT_CONTEXT* ifft_context = lsfft_init(16,CPLX_TYPE_INT,FFT_MODE_INVERSE); //get the FFT context

	uint32_t i,j;
	printf("loading samples\n");
	int16_t* re =(int16_t*)samples_md->re;
	int16_t* im =(int16_t*)samples_md->im;

	for(i=0;i<samples_md->length;i++){
		re[i] = 0;
		im[i] = 0;
	}

	uint32_t vector[1] = {4};//,4,4};
	uint32_t pos = get_memory_index(vector,samples_md->dimension_strides,samples_md->dimension); 
	re[pos] = 10;

	vector[0] = 5;
	//vector[1] = 5;
	//vector[1] = 5;
	pos = get_memory_index(vector,samples_md->dimension_strides,samples_md->dimension); 
	re[pos] = 10;

/*
	vector[0] = 4;
	vector[1] = 5;
	vector[1] = 5;
	pos = get_memory_index(vector,samples_md->dimension_strides,samples_md->dimension); 
	re[pos] = 10;

	vector[0] = 5;
	vector[1] = 4;
	vector[1] = 5;
	pos = get_memory_index(vector,samples_md->dimension_strides,samples_md->dimension); 
	re[pos] = 10;*/

	for(i=0;i<samples_md->length;i++){
		if(i>0 && (i % samples_md->base_length == 0)){
			printf("\n");
		}
		printf("%d+i*%d ",re[i],im[i]);
	}
	printf("\n");

	printf("performing MD FFT\n");
	perform_fft_md(fft_context,samples_md);
	
 	printf("Outputting Result\n");

	for(i=0;i<samples_md->length;i++){
		if(i>0 && (i % samples_md->base_length == 0)){
			printf("\n");
		}
		printf("%d+i*%d ",re[i],im[i]);
	}
	printf("\n");

	//printf("axis %d\n",axis);
	/*
	bit_reverse_int_md(fft_context,samples_md,memory_vector,axis);
	
	for(i=0;i<samples_md->base_length;i++){ //fill the buffer note: it takes 4GiB of memory to fill this buffer...
		memory_vector[axis] = i;
		uint32_t index = get_memory_index(memory_vector,samples_md->dimension_strides,samples_md->dimension);
		printf("%d ",((uint16_t*)samples_md->re)[index]);
	}
	printf("\n");*/

	/*
	//--FFT AND iFFT
	int i=0;
	for(;i<16;i++){ //store a square wave pulse
		((int16_t*)samples->re)[i] = i;
	}
	
	lsfft_perform(fft_context,samples); // perform FFT

	printf("FFT result:\n"); //show the result of the FFT
	
	for(i=0;i<16;i++){
		printf("%d + i * %d\n",((int16_t*)samples->re)[i],((int16_t*)samples->im)[i]);
	}
	
	lsfft_perform(ifft_context,samples); // perform FFT
	
	printf("\niFFT result:\n"); //show the result of the inverse DFT
	
	for(i=0;i<16;i++){
		printf("%d + i * %d\n",((int16_t*)samples->re)[i],((int16_t*)samples->im)[i]);
	}
	
	//--filtering using fast convolution
	CPLX_SAMPLES* kernel = lsfft_alloc_complex_buffer(16,CPLX_TYPE_INT); //get the buffer for the convolution kernel

	((int16_t*)kernel->re)[0] = -1; // perform an "edge" detection using 1D Sobel-Filter
	((int16_t*)kernel->re)[1] =  0;
	((int16_t*)kernel->re)[2] =  1;
	
	CONVOLUTION_CONTEXT* conv_context = lsfft_init_convolution(kernel);
	
	lsfft_perform_convolution(conv_context,samples); // compute the convolution
	
	printf("\nConvolution result:\n"); //show the result of the Convolution
	
	for(i=0;i<16;i++){
		printf("%d + i * %d\n",((int16_t*)samples->re)[i],((int16_t*)samples->im)[i]);
	}*/


	lsfft_free_complex_buffer(samples_md);

	printf("press any key to quit!\n");
	getchar();
}
