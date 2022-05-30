#include <iostream>
#include <cmath>



// all generated haar matrices will be based on this matrix
int haar_mat_2x2[2][2] = {
	{1, 1}, 
	{1, -1}};

// the "in" in "in_matrix" has no meaning
// free the returned pointer when done 
int *in_matrix(int size){

	if (size < 2){
		return 0;
	}

	int *data = new int[size * size];
	for (int i = 0; i < (size * size); i++){
		data[i] = 0;
	}

	// fill left top to bottom right with ones
	for (int i = 0; i < size; i++){
		data[i + i * size] = 1;
	}
	return data;
}




// remember to free tmp, 

// free the returned pointer when done
int *haar_matrix(int size){
	// error if size uneven, or size too small/negative
	if (size < 2 || size & 1){
		return 0;
	}
	
	// create output array, size^2 is used because of the 2 dimensional-ness of the haar matrix
	int *john = new int[size * size];

	
	// if the size equals 2, return an array and stop recursion
	if (size == 2){
		john[0] = haar_mat_2x2[0][0];
		john[1] = haar_mat_2x2[0][1];
		john[2] = haar_mat_2x2[1][0];
		john[3] = haar_mat_2x2[1][1];
	}

	else {
		// get matrix that is one size smaller
		int *tmp = haar_matrix(size >> 1);
		// multiply with [1, 1] and copy over into the output array
		for (int i = 0; i < ((size >> 1) * (size >> 1)); i++){
			john[2*i] = tmp[i];
			john[2*i+1] = tmp[i];
		}
		// free tmp, it's not needed anymore
		delete[] tmp;
		
		
		// get In matrix, like shown on wikipedia https://en.wikipedia.org/wiki/Haar_wavelet
		tmp = in_matrix(size >> 1);
		
		// multiply In matrix with [1, -1] 
		int offset = (size * size) >> 1;
		for (int i = 0; i < ((size >> 1) * (size >> 1)); i++){
			john[2*i + offset] = tmp[i];
			john[2*i + offset + 1] = tmp[i] * -1;
		}
		// tmp is unneeded now
		delete[] tmp;


	}

	// return the haar matrix
	return john;

}