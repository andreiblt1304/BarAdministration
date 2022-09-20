//AM FOLOSIT PRINCIPIUL DE LUCRU CU O COADA(FIFO)
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Bar Bar;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Bar
{
	char* nume;
	int nrAngajati;
	int nrBauturi;
};

struct Nod
{
	Bar bar;
	Nod* next;
	Nod* prev;
};

struct LDI
{
	Nod* prim;
	Nod* ultim;
};

Bar initializareBar(char* nume, int nrAngajati, int nrBauturi)
{
	Bar bar1;
	bar1.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy_s(bar1.nume, strlen(nume) + 1, nume);
	bar1.nrAngajati = nrAngajati;
	bar1.nrBauturi = nrBauturi;

	return bar1;
}

void inserareInceput(Bar b, LDI* lista)
{
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));
	nou->bar = b;
	nou->next = lista->prim;
	nou->prev = NULL;

	if (lista->prim != NULL)
	{
		lista->prim->prev = nou;
	}
	else
	{
		lista->ultim = nou;
	}

	lista->prim = nou;
}

void afisareBar(Bar bar)
{
	printf("Barul %s, are un numar de %d angajati si meniul cuprinde %d bauturi\n", bar.nume, 
																					bar.nrAngajati, 
																					bar.nrBauturi);
}

void afisareLista(LDI lista)
{
	Nod* pointer = lista.prim;

	while (pointer)
	{
		afisareBar(pointer->bar);
		pointer = pointer->next;
	}
}

//metoda returneaza barurile care au ori numarul de angajati 
//sau de bauturi mai mare decat criteriul impus de utilizator
void filter(LDI lista, LDI* listaNoua)
{
	int tipFiltrare;
	int crtMinim;
	Nod* pointer = lista.prim;

	printf("Filtrare in functie de: 1.numarul de angajati sau 2.numarul de bauturi\n");
	scanf_s("%d", &tipFiltrare);
	
	if (tipFiltrare != 1 && tipFiltrare != 2)
	{
		printf("Input gresit");
	}
	else if (tipFiltrare == 1)
	{
		printf("Introduceti numarul de angajati minim dupa care sa se faca filtrarea: ");
		scanf_s("%d", &crtMinim);

		while (crtMinim && pointer->next != NULL)
		{
			if (pointer->bar.nrAngajati > crtMinim)
			{
				Bar b = initializareBar(pointer->bar.nume, pointer->bar.nrAngajati, pointer->bar.nrBauturi);
				inserareInceput(b, &listaNoua);

				afisareBar(b);
			}

			//afisareLista(*(listaNoua));
			pointer = pointer->next;			
		}
	}
	else if (tipFiltrare == 2)
	{
		printf("Introduceti numarul de bauturi minim dupa care sa se faca filtrarea: ");
		scanf_s("%d", &crtMinim);

		while (crtMinim && pointer->next != NULL)
		{
			if (pointer->bar.nrBauturi > crtMinim)
			{
				Bar b = initializareBar(pointer->bar.nume, pointer->bar.nrAngajati, pointer->bar.nrBauturi);
				inserareInceput(b, &listaNoua);

				afisareBar(b);
			}

			//afisareLista(listaNoua);
			pointer = pointer->next;
		}
	}	
}

void dezalocareLista(LDI* lista)
{
	while (lista->prim)
	{
		free(lista->prim->bar.nume);
		lista->prim = lista->prim->next;

		if (lista->prim)
		{
			free(lista->prim->prev);
		}
		else
		{
			free(lista->ultim);
			lista->ultim = NULL;
		}
	}
}

void main()
{
	LDI lista;
	LDI listaNoua;

	lista.prim = NULL;
	lista.ultim = NULL;

	listaNoua.prim = NULL;
	listaNoua.ultim = NULL;

	inserareInceput(initializareBar("Bar1", 2, 10), &lista);
	inserareInceput(initializareBar("Bar2", 30, 150), &lista);
	inserareInceput(initializareBar("Bar3", 11, 50), &lista);
	inserareInceput(initializareBar("Bar4", 15, 75), &lista);
	inserareInceput(initializareBar("Bar5", 3, 12), &lista);
	inserareInceput(initializareBar("Bar6", 9, 20), &lista);
	inserareInceput(initializareBar("Bar7", 50, 130), &lista);

	//afisareLista(lista);
	filter(lista, &listaNoua);
}