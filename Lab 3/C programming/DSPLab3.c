#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIG_LENGTH 10000 
#define GAUSSIAN_ITRS 10000
#define ORDER 2
#define NUM_SECTIONS 3


float SOSCoef[NUM_SECTIONS][2 * (ORDER + 1)] = { {1,0.405944655718501,1,1,1.480445163690822,0.838610409335987},
											   {1,1.072516066003634,1,1,-0.524116670748896,0.752468794493461},
											   {1,0.763932022500211,1,1,0.314246435578836,-0.177292150811104} };
float GCoef[NUM_SECTIONS + 1] = { 0.529163671853004, 0.529163671853004, 0.810201815744512, 1 };


float Avg(float Sig[], int Len) {
	float Avg_value = 0;
	for (int i = 0; i < Len; i++)
		Avg_value += Sig[i] / Len;
	return Avg_value;
}

void White_Noise(float* Gaussian,int mean,int var) {

	srand((unsigned int)time(NULL));
	float Avg_value = 0;

	for (int j = 0; j < GAUSSIAN_ITRS; j++) {
		for (int i = 0; i < SIG_LENGTH; i++) {
			Gaussian[i] += ((float)rand()) / RAND_MAX;
		}
	}

	for (int i = 0; i < SIG_LENGTH; i++)
		Gaussian[i] *= sqrt((float)12 / GAUSSIAN_ITRS);

	Avg_value = Avg(Gaussian, SIG_LENGTH);
	for (int i = 0; i < SIG_LENGTH; i++)
		Gaussian[i] -= Avg_value;

	for (int i = 0; i < SIG_LENGTH; i++) {
		Gaussian[i] = sqrt(var) * Gaussian[i] + mean;
	}
}

void IIR_FILTER(float* input, float SOS[NUM_SECTIONS][2 * (ORDER + 1)], float G[NUM_SECTIONS + 1], float* y) {
	float w[NUM_SECTIONS][2] = { 0, 0 };
	float x;
	float Wn = 0;
	float yn = 0;

	for (int i = 0; i < SIG_LENGTH; i++) {
		x = input[i] * G[0];
		for (int section = 0; section < NUM_SECTIONS; section++) {
			Wn = x - SOS[section][4] * w[section][0] - SOS[section][5] * w[section][1];
			yn = SOS[section][0] * Wn + SOS[section][1] * w[section][0] +
				SOS[section][2] * w[section][1];
			w[section][1] = w[section][0];
			w[section][0] = Wn;
			x = yn * G[section];
		}
		y[i] = yn * G[3];
	}
}

int main() {
	FILE* FilOutMean0Var1;
	FilOutMean0Var1 = fopen("FilOutMean0Var1.txt", "w");
	FILE* FilOutMean4Var2;
	FilOutMean4Var2 = fopen("FilOutMean4Var2.txt", "w");
	FILE* FilOutMean20Var3;
	FilOutMean20Var3 = fopen("FilOutMean20Var3.txt", "w");
	FILE* WhiteMean0Var1;
	WhiteMean0Var1 = fopen("WhiteMean0Var1.txt", "w");
	FILE* WhiteMean4Var2;
	WhiteMean4Var2 = fopen("WhiteMean4Var2.txt", "w");
	FILE* WhiteMean20Var3;
	WhiteMean20Var3 = fopen("WhiteMean20Var3.txt", "w");


	float WhiteGMean0Var1[SIG_LENGTH] = { 0 };
	float WhiteGMean4Var2[SIG_LENGTH] = { 0 };
	float WhiteGMean20Var3[SIG_LENGTH] = { 0 };

	float FilOutGMean0Var1[SIG_LENGTH] = { 0 };
	float FilOutGMean4Var2[SIG_LENGTH] = { 0 };
	float FilOutGMean20Var3[SIG_LENGTH] = { 0 };


	White_Noise(WhiteGMean0Var1, 0, 1);
	White_Noise(WhiteGMean4Var2, 4, 2);
	White_Noise(WhiteGMean20Var3,20,3);

	IIR_FILTER(WhiteGMean0Var1, SOSCoef, GCoef, FilOutGMean0Var1);
	IIR_FILTER(WhiteGMean4Var2, SOSCoef, GCoef, FilOutGMean4Var2);
	IIR_FILTER(WhiteGMean20Var3, SOSCoef, GCoef, FilOutGMean20Var3);

	for (int i = 0; i < SIG_LENGTH; i++)
		fprintf(WhiteMean0Var1, "%lf\n", WhiteGMean0Var1[i]);

	for (int i = 0; i < SIG_LENGTH; i++)
		fprintf(WhiteMean4Var2, "%lf\n", WhiteGMean4Var2[i]);

	for (int i = 0; i < SIG_LENGTH; i++)
		fprintf(WhiteMean20Var3, "%lf\n", WhiteGMean20Var3[i]);



	for (int i = 0; i < SIG_LENGTH; i++)
		fprintf(FilOutMean0Var1, "%lf\n", FilOutGMean0Var1[i]);


	for (int i = 0; i < SIG_LENGTH; i++)
		fprintf(FilOutMean4Var2, "%lf\n", FilOutGMean4Var2[i]);


	for (int i = 0; i < SIG_LENGTH; i++)
		fprintf(FilOutMean20Var3, "%lf\n", FilOutGMean20Var3[i]);


	fclose(FilOutMean0Var1);
	fclose(FilOutMean4Var2);
	fclose(FilOutMean20Var3);
	fclose(WhiteMean0Var1);
	fclose(WhiteMean4Var2);
	fclose(WhiteMean20Var3);
	return 0;
}