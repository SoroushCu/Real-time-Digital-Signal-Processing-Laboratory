#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#define N 160000 //filter length

float FIR_Filter1(float newsample);
void FileWrite(float *arr);
void FileRead(float* arr);
float x[N];
float y[N];
float h[N] = { 1,-1.618,1 };
float fil, arr[N];
int i, j, k, n;

int main(){
    FileRead(arr);

    for (n = 0; n < N; n++) {
        y[n] = FIR_Filter1(arr[n]);
    }
    FileWrite(y);
    return 0;
}

void FileRead(float *array) {
    FILE* fp;
    fp = fopen("Noisy_Monotone.txt", "r+");
    for (j = 0; j < N; j++)
    {
        fscanf(fp, "%f", &array[j]);
    }
    fclose(fp);
}

void FileWrite(float *arr) {
    FILE* fp2;
    fp2 = fopen("MefsinFiltered.txt", "w+");
    for (k = 0; k < N; k++)
    {
        fprintf(fp2, "%f ", arr[k]);
    }
    fclose(fp2);
}

float FIR_Filter1(float newsample) { 
    fil = 0;
    x[0] = newsample;

    for (i = 0; i < N; i++)
        fil += h[i] * x[i];

    for (i = N - 1; i > 0; i--)
        x[i] = x[i - 1];

    return fil;
}
