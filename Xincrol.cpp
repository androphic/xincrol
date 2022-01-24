//============================================================================
// Name        : Xincrol.cpp
// Author      : Tofig Kareemov
// Version     :
// Copyright   : Your copyright notice
// Description : Xincrol! algorithm in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define INT_BITS (sizeof(int)*8)

unsigned int currentTimeMillis() {
	struct timeval te;
	gettimeofday(&te, 0);
	long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (unsigned int) milliseconds;
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
		iResult = iResult << 1;
		iResult = iResult | (iInput & 1);
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
	unsigned int iRolBackBits = iBits - 1;
	unsigned int iInnerSeed = 0x5a5aa5a5 ^ _reverse_(iSeed);
	unsigned int iResult = (iIndex ^ _reverse_(iInnerSeed)) & iMask;
	for (int i = 0; i < 256 * iBits; ++i) {
		unsigned int iLocalInnerSeed = iInnerSeed ^ iSeed ^ _reverse_(iSeed);
		switch (iLocalInnerSeed >> (INT_BITS - 2)) {
		case 0:
			// Xor
			iResult = (iResult ^ iLocalInnerSeed) & iMask;
			iInnerSeed = _rol_(iInnerSeed);
			break;
		case 1:
			// Inc
			iResult = (iResult + 1) & iMask;
			break;
		case 2:
			// ROL Bits
			iResult = ((iResult << 1) | ((iResult >> iRolBackBits) & 1))
					& iMask;
			break;
		default:
			// Not
			iResult = (iResult ^ 0xFFFFFFFF) & iMask;
			break;
		}
		++iSeed;
		iInnerSeed = _rol_(iInnerSeed);
	}
	return iResult;
}

int main(void) {
	printf("Xincrol demonstration\n");
	int iBits = 16;
	unsigned int iSeed = currentTimeMillis();
	for (unsigned int i = 0; i < 1 << iBits; ++i) {
		printInt(xincrol(i, iBits, iSeed));
	}
	return 0;
}
