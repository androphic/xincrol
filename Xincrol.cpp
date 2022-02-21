//============================================================================
// Name        : Xincrol.cpp
// Author      : Tofig Kareemov
// Version     :
// Copyright   : Your copyright notice
// Description : Xincrol! algorithm in C++, Ansi-style
// Unique Random Number Generator. For generation random numbers stream where
// each number appears only once. Useful for IDs, encryption, visual 
// effects, Random Forest building etc.
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
	printf("0x%X\n", iInput);
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

inline unsigned int _rol_(unsigned int iInput) {
	return ((iInput << 1) | (iInput >> (INT_BITS - 1)));
}

inline unsigned int _rol_(unsigned int iInput, unsigned int iBits) {
	unsigned int iMask = (1 << iBits) - 1;
	unsigned int iRolBackBits = iBits - 1;
	return ((iInput << 1) | ((iInput >> iRolBackBits) & 1)) & iMask;
}

unsigned int xincrol(unsigned int iIndex1, unsigned iIndex2,
		unsigned int iBits) {
	unsigned int iResult = 0x5aa55aa5 ^ iIndex1;
	unsigned int iKey = 0xaa55aa55 ^ _reverse_(iIndex2);
	for (int i = 0; i < INT_BITS * INT_BITS; ++i) {
		iResult = _rol_((iResult + i) ^ iKey, iBits);
		iKey = _rol_(++iKey);
	}
	return iResult;
}

int main(void) {
	printf("Xincrol demonstration\n");
	int iBits = 20;
	unsigned int iSeed = currentTimeMillis();
	int iTS = currentTimeMillis();
	for (unsigned int i = 0; i < 1 << iBits; ++i) {
		unsigned int iResult = xincrol(i, iSeed, iBits);
		printHex(iResult);
	}
	printf("Time spent(millis): %d\n", currentTimeMillis() - iTS);
	return 0;
}
