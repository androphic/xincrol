//============================================================================
// Name        : Xincrol.cpp
// Author      : Tofig Kareemov
// Version     :
// Copyright   : Your copyright notice
// Description : Xincrol! algorithm in C++, Ansi-style
// Unique Random Number Generator. For generation of a stream of random numbers
// where each number appears only once. Useful for Secure IDs, encryption, visual
// effects, Random Forest building, Data fogging and Steganography, Games,
// Songs shuffling for media player, Time limited statistical analysis for
// Big Data sets etc.
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define INT_BITS (32)

unsigned int currentTimeMillis() {
	struct timeval oTime;
	gettimeofday(&oTime, 0);
	long long iMilliseconds = oTime.tv_sec * 1000LL + oTime.tv_usec / 1000;
	return (unsigned int) iMilliseconds;
}

void printHex(int iInput) {
	printf("0x%08x\n", iInput);
}

void printInt(int iInput) {
	printf("%d\n", iInput);
}

inline unsigned int _reverse_(unsigned int iInput) {
	unsigned int iResult = 0;
	for (int i = 0; i < INT_BITS; ++i) {
		iResult = (iResult << 1) | (iInput & 1);
		iInput = iInput >> 1;
	}
	return iResult;
}

inline unsigned int _rol_(unsigned int iInput, unsigned int iDist) {
	iDist = iDist % INT_BITS;
	return ((iInput << iDist) | (iInput >> (INT_BITS - iDist)));
}

inline unsigned int _rol1_(unsigned int iInput) {
	return ((iInput << 1) | (iInput >> (INT_BITS - 1)));
}

inline unsigned int _rol1_(unsigned int iInput, unsigned int iBits) {
	unsigned int iMask;
	if (iBits == 32) {
		iMask = 0xFFFFFFFF;
	} else {
		iMask = (0x00000001 << iBits) - 1;
	}
	unsigned int iRolBackBits = iBits - 1;
	return ((iInput << 1) | ((iInput >> iRolBackBits) & 1)) & iMask;
}

unsigned int xincrol(unsigned int iIndex1, unsigned iIndex2,
		unsigned int iBits) {
	unsigned int iResult = 0x5aa55aa5 ^ iIndex1;
	unsigned int iKey = 0xaa55aa55 ^ _reverse_(iIndex2);
	for (int i = 0; i < INT_BITS * INT_BITS; ++i) {
		iResult = _rol1_((iResult + i) ^ iKey, iBits);
		iKey = _rol_(++iKey, i);
	}
	return iResult;
}

int main(void) {
	printf("Xincrol demonstration\n");
	int iBits = 4;
	int iExperiments = 123456;
	unsigned int iSeed = currentTimeMillis();
	int iTS = currentTimeMillis();
	for (unsigned int i = 0; i < iExperiments; ++i) {
		unsigned int iResult = xincrol(i, iSeed, iBits);
		printHex(iResult);
	}
	printf("Time (millis): %d\n", currentTimeMillis() - iTS);
	return 0;
}
