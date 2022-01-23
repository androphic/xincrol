//============================================================================
// Name        : Xincrol.cpp
// Author      : Tofig Kareemov
// Version     :
// Copyright   : Your copyright notice
// Description : Xincrol! algorithm implementaion. C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define INT_BITS sizeof(int)

int current_timestamp() {
	struct timeval te;
	gettimeofday(&te, NULL); // get current time // @suppress("Symbol is not resolved") // @suppress("Invalid arguments")
	long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds // @suppress("Field cannot be resolved")
	printf("milliseconds: %lld\n", milliseconds);
	return (int) milliseconds;
}

void printHex(int iInput) {
	printf("0x%X\n", iInput);
}

void printInt(int iInput) {
	printf("%d\n", iInput);
}

inline unsigned int _reverse_(unsigned int iInput) {
	unsigned int iResult = 0;
	for (int i = 0; i < INT_BITS; ++i) {
		if ((iInput & 1) != 0) {
			iResult = iResult | 1;
		}
		iResult = iResult << 1;
		iInput = iInput >> 1;
	}
	return iResult;
}

inline unsigned int _rol_(unsigned int iInput) {
	return ((iInput << 1) | (iInput >> (INT_BITS - 1)));
}

unsigned int xincrol(unsigned int iIndex, unsigned int iBits,
		unsigned int iSeed) {
	unsigned int iMask = (1 << iBits) - 1;
	unsigned int iInnerSeed = 0x5a5aa5a5 ^ _reverse_(iSeed);
	unsigned int iResult = (iIndex ^ _reverse_(iInnerSeed)) & iMask;
	for (int i = 0; i < 256 * iBits; ++i) {
		iInnerSeed = iInnerSeed ^ iSeed;
		unsigned int iOperation = iInnerSeed & 3;
		if (iOperation == 0) {
			// Xor
			iResult = (iResult ^ iInnerSeed) & iMask;
		} else if (iOperation == 1) {
			// Inc
			iResult = (iResult + 1) & iMask;
		} else if (iOperation == 2) {
			// ROL Bits
			iResult = ((iResult << 1) | ((iResult >> (iBits - 1)) & 1)) & iMask;
		} else if (iOperation == 3) {
			// Not
			iResult = (iResult ^ 0xFFFFFFFF) & iMask;
		}
		iInnerSeed = iInnerSeed ^ iSeed;
		++iSeed;
		iInnerSeed = _rol_(iInnerSeed);
	}
	return iResult;
}

int main(void) {
	puts("Xincrol demonstration"); /* prints !!!Hello World!!! */ // @suppress("Invalid arguments")
	int iBits = 8;
	unsigned int iSeed = current_timestamp();
	for (unsigned int i = 0; i < 1 << iBits; ++i) {
		printInt(xincrol(i, iBits, iSeed)); // @suppress("Invalid arguments")
	}
	return EXIT_SUCCESS; // @suppress("Symbol is not resolved")
}
