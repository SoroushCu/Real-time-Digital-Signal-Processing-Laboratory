#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "fdacoefsDSPLab.h"
#define Size 24000
float sin1[Size],sin2[Size],sin3[Size], sin4[Size];
float sin5[Size], sin6[Size],WhiteNoise[Size],x[Size];
float osin1[Size], osin2[Size], osin3[Size], osin4[Size];
float osin5[Size], osin6[Size],WhiteNoiseO[Size];
float y;
int i,j,k,n,x_index, newest = 0;
void FileRead(float* array, char* readname);
void FileWrite(float* arr, char* outname);
float FIR_filter2(float newsample);
int main()
{
	FileRead(sin1,"Sinewavepass1.txt");
	FileRead(sin2, "Sinewavepass2.txt");
	FileRead(sin3, "Sinewavetrans1.txt");
	FileRead(sin4, "Sinewavetrans2.txt");
	FileRead(sin5, "Sinewavestop1.txt");
	FileRead(sin6, "Sinewavestop2.txt");
	FileRead(WhiteNoise, "WhiteNoise.txt");

	for (n = 0; n < Size; n++) {
		osin1[n] = FIR_filter2(sin1[n]);
	}
	for (n = 0; n < Size; n++) {
		osin2[n] = FIR_filter2(sin2[n]);
	}
	for (n = 0; n < Size; n++) {
		osin3[n] = FIR_filter2(sin3[n]);
	}
	for (n = 0; n < Size; n++) {
		osin4[n] = FIR_filter2(sin4[n]);
	}
	for (n = 0; n < Size; n++) {
		osin5[n] = FIR_filter2(sin5[n]);
	}
	for (n = 0; n < Size; n++) {
		osin6[n] = FIR_filter2(sin6[n]);
	}
	for (n = 0; n < Size; n++) {
		WhiteNoiseO[n] = FIR_filter2(WhiteNoise[n]);
	}
	FileWrite(osin1,"Sinewavepass1Fil.txt");
	FileWrite(osin2, "Sinewavepass2Fil.txt");
	FileWrite(osin3, "Sinewavetrans1Fil.txt");
	FileWrite(osin4, "Sinewavetrans2Fil.txt");
	FileWrite(osin5, "Sinewavestop1Fil.txt");
	FileWrite(osin6, "Sinewavestop2Fil.txt");
	FileWrite(WhiteNoiseO, "WhiteNoiseFil.txt");
	return 0;
}

void FileRead(float* array,char* readname) {
	FILE* fp;
	fp = fopen(readname, "r+");
	for (j = 0; j < Size; j++)
	{
		fscanf(fp, "%f", &array[j]);
	}
	fclose(fp);
}

void FileWrite(float* arr, char *outname) {
	FILE* fp2;
	fp2 = fopen(outname, "w+");
	for (k = 0; k < Size; k++)
	{
		fprintf(fp2, "%f ", arr[k]);
	}
	fclose(fp2);
}
float FIR_filter2(float newsample)
{
	++newest;
	if (newest == BL) 
		newest = 0;
	x[newest] = newsample;
	y = 0;
	x_index = newest;
	for (i = 0; i < BL; i++)
	{
		y += B[i] * x[x_index];
		--x_index;
		if (x_index == -1) 
			x_index = BL - 1;
	}
	return (y);
}