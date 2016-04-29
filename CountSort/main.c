#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100
/*
	MY == 1 - moja implementacja sortowania przez zliczanie.
	MY != 1 - implementacja sortowania przez zliczanie zgodna z pseudokodem z wyk³adu.
	Z doœwiadczeñ wynika, ¿e moja wersja jest szybsza, ale nie jest stabilna.
*/
#define MY 0
#if MY == 1
	#define CountSort(__A, __B, __N, __FROM, __TO) myCountSort(__A, __B, __N, __FROM, __TO)
#else
	#define CountSort(__A, __B, __N, __FROM, __TO) wykladCountSort(__A, __B, __N, __FROM, __TO)
#endif

//Losowanie liczb 2x wiekszych niz 0x7FFF
unsigned long long llrand()
{
	int r = 0;

	for (int i = 0; i < 2; ++i)
	{
		r = (r << 15) | (rand() & 0x7FFF);
	}

	return r;
}

void arrayRandomFill(int tab[], int n, int from, int to)
{
	for (int i = 0; i < n; i++)
	{
		tab[i] = (llrand() % (to - from + 1)) + from;
	}
}

//moja implementacja sortowania przez zliczanie
void myCountSort(int A[], int B[], int iloscElementow, int from, int to)
{
	int rozpietoscElementow = to - from + 1;
	int* C = (int*)calloc(rozpietoscElementow, sizeof(int));
	if (C == NULL) return;

	for (int i = 0; i < iloscElementow; i++)
	{
		C[A[i] - from]++;
	}

	int idx = 0;
	for (int i = 0; i < rozpietoscElementow; i++)
	{
		for (int j = 0; j < C[i]; j++)
		{
			B[idx] = from + i;
			idx++;
		}
	}
	free(C);
}

//implementacja sortowania przez zliczanie zgodna z wyk³adem
void wykladCountSort(int A[], int B[], int iloscElementow, int from, int to)
{
	int rozpietoscElementow = to - from + 1;
	int* C = (int*)calloc(rozpietoscElementow, sizeof(int));
	if (C == NULL) return;

	for (int i = 0; i < iloscElementow; i++)
		C[A[i] - from]++;

	for (int i = 1; i < rozpietoscElementow; i++)
		C[i] += C[i - 1];

	for (int i = iloscElementow - 1; i >= 0; i--)
	{
		int eidx = A[i] - from;
		B[--C[eidx]] = eidx;
	}
	free(C);
}

double czasWykonaniaSortowania(int tab[], int iloscElementow, int zakresOd, int zakresDo,  int Niter)
{
	int *tabout = (int*)malloc(sizeof(int)*iloscElementow);
	if (tabout == NULL) return -1;

	double time = clock();
	for (int i = 0; i < Niter; i++)
	{
		CountSort(tab, tabout, iloscElementow, zakresOd, zakresDo);
	}
	time = (clock() - time) / CLOCKS_PER_SEC;

	free(tabout);
	return time;
}

int main()
{
	srand(time(NULL));
	int A[N], B[N];

	arrayRandomFill(A, N, 1, 64000);
	arrayRandomFill(B, N, 1, 128);

#if MY == 1
	puts("Zastosowano wlasna implementacje algorytmu sortowania przez zliczanie");
#else
	puts("Zastosowano implementacje algorytmu sortowania przez zliczanie zgodna z pseudokodem z wykladu");
#endif

	int Niter = 100000;
	double time = czasWykonaniaSortowania(A, N, 1, 64000, Niter);
	printf("Czas sortowania %d razy tablicy A: %lf\n", Niter, time);

	Niter = 10000000;
	time = czasWykonaniaSortowania(B, N, 1, 128, Niter);
	printf("Czas sortowania %d razy tablicy B: %lf\n", Niter, time);

	printf("Nacisnij enter aby kontynuowac");
	getchar();
	return 0;
}

