#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10

/*
	Aby zastosowaæ implementacje algorytmu zgodn¹ z pseudokodem z wyk³adu pozostaw pole MY zakomentowane.
*/
//#define MY
#if defined MY
	#define CountSort(__A, __B, __N, __FROM, __TO) myCountSort(__A, __B, __N, __FROM, __TO)
#else
	#define CountSort(__A, __B, __N, __FROM, __TO) wykladCountSort(__A, __B, __N, __FROM, __TO)
#endif

const int Niter = 100000;

//Losowanie liczb wiekszych niz 0x7FFF
unsigned long long llrand()
{
	unsigned long long r = 0;

	for (int i = 0; i < 5; ++i)
	{
		r = (r << 15) | (rand() & 0x7FFF);
	}

	return r & 0xFFFFFFFFFFFFFFFFULL;
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

int main()
{
	srand(time(NULL));
	int A[N], B[N], Aout[N], Bout[N];

	arrayRandomFill(A, N, 1, 64000);
	arrayRandomFill(B, N, 1, 128);

#if defined MY
	puts("Zastosowano wlasna implementacje algorytmu sortowania przez zliczanie");
#else
	puts("Zastosowano implementacje algorytmu sortowania przez zliczanie zgodna z pseudokodem z wykladu");
#endif

	//SORTOWANIE TABLICY A
	printf("Testowanie dla tablicy A:\n");
	double time = clock();
	for (int i = 0; i < Niter; i++)
	{
		CountSort(A, Aout, N, 1, 64000);
	}
	printf("Czas sortowania %d razy tablicy A: %lf\n", Niter, (clock() - time) / CLOCKS_PER_SEC);

	//SORTOWANIE TABLICY B
	printf("\nTestowanie dla tablicy B:\n");
	time = clock();
	for (int i = 0; i < Niter; i++)
	{
		CountSort(B, Bout, N, 1, 64000);
	}
	printf("Czas sortowania %d razy tablicy B: %lf\n", Niter, (clock() - time) / CLOCKS_PER_SEC);

	printf("Nacisnij enter aby kontynuowac");
	getchar();
	return 0;
}

