#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100

/*
	Na moim komputerze ten program skompilowany z wy��czon� optymalizacj� to:
	Dla algorytmu zgodnym z pseudokodem wyk�adu:
		Czas sortowania 100000 razy tablicy A: 15.261000
		Czas sortowania 20000000 razy tablicy B: 20.799000
	Dla mojej wersji:
		Czas sortowania 100000 razy tablicy A: 13.279000
		Czas sortowania 20000000 razy tablicy B: 15.496000
*/

/*
	MY == 1 - moja implementacja sortowania przez zliczanie.
	MY != 1 - implementacja sortowania przez zliczanie zgodna z pseudokodem z wyk�adu.
	Z do�wiadcze� wynika, �e moja wersja jest szybsza, ale nie jest stabilna.
*/
#define MY 0
#if MY == 1
	#define CountSort(__A, __B, __N, __FROM, __TO) myCountSort(__A, __B, __N, __FROM, __TO)
#else
	#define CountSort(__A, __B, __N, __FROM, __TO) wykladCountSort(__A, __B, __N, __FROM, __TO)
#endif

//Losowanie liczb 2x wiekszych niz 0x7FFF
int myrand()
{
	int r = 0;
	for (int i = 0; i < 2; ++i)
		r = (r << 15) | (rand() & 0x7FFF);
	return r;
}

void arrayRandomFill(int tab[], int n, int from, int to)
{
	for (int i = 0; i < n; i++)
		tab[i] = (myrand() % (to - from + 1)) + from;
}

void errorcheck(int warunek, const char* wiadomosc)
{
	if (warunek)
	{
		puts(wiadomosc);
		exit(1);
	}
}

//moja implementacja sortowania przez zliczanie
void myCountSort(int A[], int B[], int iloscElementow, int from, int to)
{
	int rozpietoscElementow = to - from + 1;
	int* C = (int*)calloc(rozpietoscElementow, sizeof(int));
	errorcheck(C == NULL, "Brak pamieci!");

	for (int i = 0; i < iloscElementow; i++)
		C[A[i] - from]++;

	int idx = 0;
	for (int i = 0; i < rozpietoscElementow; i++)
	{
		for (int j = 0; j < C[i]; j++)
		{
			B[idx++] = from + i;
		}
	}
	free(C);
}

//implementacja sortowania przez zliczanie zgodna z wyk�adem
void wykladCountSort(int A[], int B[], int iloscElementow, int from, int to)
{
	int rozpietoscElementow = to - from + 1;
	int* C = (int*)calloc(rozpietoscElementow, sizeof(int));
	errorcheck(C == NULL, "Brak pamieci!");

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

double czasWykonaniaSortowania(int tab[], int iloscElementow, int zakresOd, int zakresDo, int Niter)
{
	int* tabout = (int*)malloc(sizeof(int) * iloscElementow);
	errorcheck(tabout == NULL, "Brak pamieci!");

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

	Niter = 20000000;
	time = czasWykonaniaSortowania(B, N, 1, 128, Niter);
	printf("Czas sortowania %d razy tablicy B: %lf\n", Niter, time);

	printf("Nacisnij enter aby kontynuowac");
	getchar();
	return 0;
}

