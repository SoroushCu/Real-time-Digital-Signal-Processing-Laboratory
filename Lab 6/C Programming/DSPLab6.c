#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define UNITQ14 0x4000
#define UNITQ15 0x7fff
float fcos1(float x)
{
	float fcoef[4] = { 1.0,-1 / 2.0,1.0 / (2.0 * 3.0 * 4.0),-1.0 / (2.0 * 3.0 * 4.0 * 5.0 * 6.0) };
	float out;
	out = fcoef[0];
	out += fcoef[1] * x * x;
	out += fcoef[2] * x * x * x * x;
	out += fcoef[3] * x * x * x * x * x * x;

	return out;
}

float fcos2(float x)
{
	float fcoef[4] = { 1.0,-1 / 2.0,1.0 / (2.0 * 3.0 * 4.0),-1.0 / (2.0 * 3.0 * 4.0 * 5.0 * 6.0) };
	float out, x2;
	x2 = x * x;
	out = x2 * fcoef[3];
	out = (out + fcoef[2]) * x2;
	out = (out + fcoef[1]) * x2;
	out += fcoef[0];
	return out;
}

short icos(short x)
{
	short iCoef[4] = { (short)(UNITQ15),(short)(-(UNITQ15 / 2.0)),
		(short)(UNITQ15 / (2.0 * 3.0 * 4.0)),
		(short)(-(UNITQ15 / (2.0 * 3.0 * 4.0 * 5.0 * 6.0))) };
	long cosine, z;
	short x2;
	z = (long)(x * x);
	x2 = (short)(z >> 15);
	cosine = (long)iCoef[3] * x2;
	cosine = cosine >> 13;
	cosine = (cosine + (long)iCoef[2]) * x2;
	cosine = cosine >> 13;
	cosine = (cosine + (long)iCoef[1]) * x2;
	cosine = cosine >> 13;
	cosine = cosine + (long)iCoef[0];
	return((short)cosine);
}
float FloatMaker(short input, int frac_bit) {
	return ((float)input / (float)(1 << frac_bit));
}

short FixMaker(float input, int frac_bit) {
	return (short)(input * (1 << frac_bit));
}

int main() {
	float Theta[7] = { 0, 0.1, -0.8, 19.373155, -0.523592, 1.5707963, 3.141592 };
	float cos_Theta1[7] = { 0 }, cos_Theta2[7] = { 0 };
	short icos_Theta[7] = {0};
	printf("First Implementation (fcos1) :\n");
	for (int i = 0; i < 7; i++) {
		cos_Theta1[i] = fcos1(Theta[i]);
		printf("cos(%f) = %f\n", Theta[i], cos_Theta1[i]);
	}
	printf("\nSecond Implementation (fcos2):\n");
	for (int i = 0; i < 7; i++) {
		cos_Theta2[i] = fcos2(Theta[i]);
		printf("cos(%f) = %f\n", Theta[i], cos_Theta2[i]);
	}
	printf("\niFixed Point (icos) :\n");
	for (int i = 0; i < 7; i++) {
		icos_Theta[i] = icos(FixMaker(Theta[i],14));
		printf("cos(%f) = %f\n", Theta[i], FloatMaker(icos_Theta[i],15));
	}
}
