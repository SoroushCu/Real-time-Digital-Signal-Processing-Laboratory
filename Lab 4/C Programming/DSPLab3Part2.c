#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIG_LENGTH 10000 
#define GAUSSIAN_ITRS 10000
#define ORDER 2
#define NUM_SECTIONS 2
#define OmegaT = 0.2617993878
float SOSCoef[NUM_SECTIONS][2 * (ORDER + 1)] = { {0,0.2588190451,0,1,-1.9318516526,1 } };
float GCoef[NUM_SECTIONS + 1] = { 1,1,1 };



void IIR_FILTER(float* input, float SOS[NUM_SECTIONS][(ORDER + 1)], float G[NUM_SECTIONS + 1], float* y) {
	float w[NUM_SECTIONS][2] = { 0, 0 };
	float x;
	float Wn = 0;
	float yn = 0;
	for (int i = 0; i < SIG_LENGTH; i++) {
		x = input[i] * G[0];
		for (int section = 0; section < NUM_SECTIONS-1; section++) {
			Wn = x - SOS[section][4] * w[section][0] - SOS[section][5] * w[section][1];
			yn = SOS[section][0] * Wn + SOS[section][1] * w[section][0] +
				SOS[section][2] * w[section][1];
			w[section][1] = w[section][0];
			w[section][0] = Wn;
			x = yn * G[section];
		}
		y[i] = yn * G[2];
	}
}

int main() {
	float Imp[SIG_LENGTH] = { 1,0,0 };
	for (int i = 1; i < SIG_LENGTH; i++)
		Imp[i] = 0;	
	FILE* FilterOutImp;
	FilterOutImp = fopen("FilterOutImp.txt", "w");
	float FilOutImpulse[SIG_LENGTH] = { 0 };
	IIR_FILTER(Imp, SOSCoef, GCoef, FilOutImpulse);
	for (int i = 0; i < SIG_LENGTH; i++)
		fprintf(FilterOutImp, "%lf\n", FilOutImpulse[i]);
	fclose(FilterOutImp);
	return 0;
}