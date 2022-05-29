#include <iostream>
#include <cmath>
#include <cstring>

// output function for debugging purposes
void output_1d(float *in, int size){
	for (int i = 0; i < size; i++){
		std::cout << in[i] << ", ";
	}
	std::cout << std::endl;
	return;
}


// definitions that are needed for the DCT functions
#define SIXTEENTH_PI 0.196349540625F
#define ONE_HALF 0.5F
#define HALF_SQRT2 0.707106781187F
#define SQRT_2 1.41421356237F

// dct, one dimensional, 16 values. returns a pointer YOU will need to free, accepts values in range [-1, 1], outputs values in range [-1, 1]
float* dct_1d_16(float *in){
	// allocate output array, set to zero
	float *out = (float*) malloc(sizeof(float) * 16);
	memset(out, 0, 16 * sizeof(float));
	
	// execute DCT algorithm, complexity O(n^2)
	for (int k = 0; k < 16; k++){
		float s = (k == 0) ? HALF_SQRT2 : 1.0;
		for (int n = 0; n < 16; n++){
			out[k] += s * in[n] * cosf32(SIXTEENTH_PI * (n + ONE_HALF) * k);
		}
		out[k] *= sqrtf32(2.0 / 256.0);
	}
	return out;
}



// inverse dct, one dimensional, 16 values. returns a pointer YOU will need to free, accepts values in range [-1, 1], outputs values in range [-1, 1]
float* idct_1d_16(float *in){
	// allocate output array, set to zero
	float *out = (float*) malloc(sizeof(float) * 16);
	memset(out, 0, 16 * sizeof(float));
	
	// execute iDCT algorithm, complexity O(n^2)
	for (int k = 0; k < 16; k++){

		for (int n = 0; n < 16; n++){
			float s = (n == 0) ? HALF_SQRT2 : 1.0;
			out[k] += s * in[n] * cosf32(SIXTEENTH_PI * (k + 0.5F) * n);
		}
		out[k] *= sqrtf32(2.0 );
	}
	return out;
}

