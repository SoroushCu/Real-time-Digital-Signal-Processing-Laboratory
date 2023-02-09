#define _CRT_SECURE_NO_WARNINGS
#include "math.h"
#include "Complex.h"
#include "fft.c"
#include "Complex.c"
#define N 1024
void main()
{
	float fs = 16000;
	complex x1[N];
	complex x2[N];
	complex x3[N];
	for (int i = 0; i < N; i++)
	{
		x1[i].x = sin((2 * PI * 2000 * i) / fs);
		x1[i].y = 0;
		x2[i].x = cos((2 * PI * 2000 * i) / fs);
		x2[i].y = 0;
		x3[i].x = cos((2 * PI * 2000 * i) / fs);
		x3[i].y = sin((2 * PI * 2000 * i) / fs);
	}
	fft(x1, N, fs);
	fft(x2, N, fs);
	fft(x3, N, fs);
	FILE* FFTX1;
	FILE* FFTX2;
	FILE* FFTX3;
	FFTX1 = fopen("FFTX1.txt", "w");
	FFTX2 = fopen("FFTX2.txt", "w");
	FFTX3 = fopen("FFTX3.txt", "w");
	for (int i = 0; i < N; i++)
	{
		fprintf(FFTX1, "%lf\n", ccabs(x1[i]));
		fprintf(FFTX2, "%lf\n", ccabs(x2[i]));
		fprintf(FFTX3, "%lf\n", ccabs(x3[i]));
	}
	return;

}