#include <time.h>
#include <stdio.h>
#include <x86intrin.h>
#include "common.h"

long long int sum(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();

	long long int sum = 0;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS; i++) {
			if(vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_unrolled(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();
	long long int sum = 0;

	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
			if(vals[i] >= 128) sum += vals[i];
			if(vals[i + 1] >= 128) sum += vals[i + 1];
			if(vals[i + 2] >= 128) sum += vals[i + 2];
			if(vals[i + 3] >= 128) sum += vals[i + 3];
		}

		//This is what we call the TAIL CASE
		//For when NUM_ELEMS isn't a multiple of 4
		//NONTRIVIAL FACT: NUM_ELEMS / 4 * 4 is the largest multiple of 4 less than NUM_ELEMS
		for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_simd(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);		// This is a vector with 127s in it... Why might you need this?
	long long int result = 0;				   // This is where you should put your final result!
	/* DO NOT DO NOT DO NOT DO NOT WRITE ANYTHING ABOVE THIS LINE. */
	
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for (unsigned int i = 0; i < NUM_ELEMS / 4; i += 1) {
			__m128i vector = _mm_loadu_si128((__m128i *) (vals + i * 4));
			__m128i mask = _mm_cmpgt_epi32(vector, _127);
			__m128i masked = _mm_and_si128(vector, mask);
			result = _mm_extract_epi32(masked, 0) + _mm_extract_epi32(masked, 1) + _mm_extract_epi32(masked, 2) + _mm_extract_epi32(masked, 3);
		}
		for (unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				result += vals[i];
			}
		}
	}

	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}

long long int sum_simd_unrolled(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);
	long long int result = 0;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for (unsigned int i = 0; i < NUM_ELEMS / 16 * 16; i += 16) {
			__m128i vector1 = _mm_loadu_si128((__m128i *) (vals + i));
			__m128i vector2 = _mm_loadu_si128((__m128i *) (vals + i + 4));
			__m128i vector3 = _mm_loadu_si128((__m128i *) (vals + i + 8));
			__m128i vector4 = _mm_loadu_si128((__m128i *) (vals + i + 12));
			__m128i mask1 = _mm_cmpgt_epi32(vector1, _127);
			__m128i mask2 = _mm_cmpgt_epi32(vector2, _127);
			__m128i mask3 = _mm_cmpgt_epi32(vector3, _127);
			__m128i mask4 = _mm_cmpgt_epi32(vector4, _127);
			__m128i masked1 = _mm_and_si128(vector1, mask1);
			__m128i masked2 = _mm_and_si128(vector2, mask2);
			__m128i masked3 = _mm_and_si128(vector3, mask3);
			__m128i masked4 = _mm_and_si128(vector4, mask4);
			result += _mm_extract_epi32(masked1, 0) + _mm_extract_epi32(masked1, 1) + _mm_extract_epi32(masked1, 2) + _mm_extract_epi32(masked1, 3);
			result += _mm_extract_epi32(masked2, 0) + _mm_extract_epi32(masked2, 1) + _mm_extract_epi32(masked2, 2) + _mm_extract_epi32(masked2, 3);
			result += _mm_extract_epi32(masked3, 0) + _mm_extract_epi32(masked3, 1) + _mm_extract_epi32(masked3, 2) + _mm_extract_epi32(masked3, 3);
			result += _mm_extract_epi32(masked4, 0) + _mm_extract_epi32(masked4, 1) + _mm_extract_epi32(masked4, 2) + _mm_extract_epi32(masked4, 3);
		}

		for (unsigned int i = NUM_ELEMS / 16 * 16; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				result += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}