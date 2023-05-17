#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define NUM_CONTACTS 30
/*
	Aplikacija kontakti: implementacija dvostruko vezanim skipped listama.
	Jedna osoba može imati više brojeva i ostalih podataka (fb, messenger, wapp, ...).

	Dodatno: pretraživanje kontakata, pravljenje grupa, 
	pravljenje veza (npr. Juri Juriæu je Ante Antiæ roðak, ...), dodavanje favorita, ...
*/

struct kontakt;
//typedef struct kontakt* Position;
typedef struct kontakt {
	char naziv[25];
	int broj[10];
	char fbProfil[25];
	char eMail[25];
	int favorit; //Je li kontakt favorit - 0 ili 1
	struct kontakt* next;
	struct kontakt* prev;
}Kontakt;

struct kontakt* NoviElement();
int Izbornik();
int NoviKontakt(struct kontakt*);
struct kontakt* PronadiKontakt(struct kontakt*);
int UrediKontakt(struct kontakt*);
struct kontakt* PronadiPrethodni(struct kontakt*, struct kontakt*);
int IzbrisiKontakt(struct kontakt**);
int PrikaziSve(struct kontakt*);
int PrikaziFavorite(struct kontakt*);

int main()
{
	int kraj = 0; int rezultat = 0; int izbor = 0;
	struct kontakt*  kontakti[NUM_CONTACTS] = { 0 };
	

	printf("\nDobrodosli u aplikaciju 'Kontakti'.\n");

	rezultat = Izbornik();
	if (rezultat == 0)
		printf("\nGreska u koristenju funkcije 'Izbornik'!\n");
	else
		printf("\n'Izbornik' uspjesno izvrsen!\n");

	while (1)
	{
		scanf(" %d", &izbor);

		switch (izbor)
		{
		case 0: { return 0;
			break;	}
		case 1: { rezultat = NoviKontakt(kontakti);
			if (rezultat == 1)
				printf("\nNovi kontakt uspjesno stvoren!\n");
			break;	}
		case 2: { PronadiKontakt(kontakti);
			break; }
		case 3: { rezultat = UrediKontakt(kontakti);
			if (rezultat == 1)
				printf("\nNovi kontakt uspjesno stvoren!\n");
			break;	}
		case 4: { IzbrisiKontakt(kontakti);
			if (rezultat == 1)
				printf("\nBrisanje kontakta uspjesno!\n");
			break; }
		case 5: { rezultat = PrikaziSve(kontakti);
			if (rezultat == 1)
				printf("\nSvi kontakti uspjesno prikazani!\n");
			break; }
		case 6: { rezultat = PrikaziFavorite(kontakti);
			if (rezultat == 1)
				printf("\nSvi favoriti uspjesno prikazani!\n");
			break; }
		
		default:
			printf("Unesite pravi broj!! \n");
			break;
		}
	}

	scanf(" %d", kraj);
	return 0;
}

struct kontakt* NoviElement()
{
	struct kontakt* noviElement = NULL;
	noviElement = (struct kontakt*)malloc(sizeof(Kontakt));
	noviElement->next = NULL;
	noviElement->prev = NULL;

	if (noviElement == NULL) {
		printf("\nGreska kod alokacije memorije novog elementa!\n");
		return NULL;
	}

	return noviElement;
}

int Izbornik()
{

	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("/0/ -- Izlaz iz programa\n");
	printf("/1/ -- Dodajte novi kontakt\n");
	printf("/2/ -- Prikazite kontakt\n");
	printf("/3/ -- Uredite konakt\n");
	printf("/4/ -- Izbrisite kontakt\n");
	printf("/5/ -- Prikazite sve kontakte\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	return 1;
}

int NoviKontakt(struct kontakt**kontakti)
{
	struct kontakt* noviElement = NoviElement();
	struct kontakt* slovoAdresara = NULL;
	char c = 0;
	int i = 0; int izbor = 0;

	printf("Upisite naziv osobe:\t");
	scanf(" %s", noviElement->naziv);
	printf("\nUpisite broj osobe:\t");
	scanf(" %s", noviElement->broj);

	printf("\nZelite li unijeti fb profil? (0 - Ne, 1 - Da)\n");
	scanf(" %d", izbor);
	if (izbor = 1) {
		printf("Upisite fb profil osobe:");
		scanf(" %s", noviElement->fbProfil);
	}
	printf("\nZelite li unijeti eMail? (0 - Ne, 1 - Da)\n");
	scanf(" %d", izbor);
	if (izbor = 1) {
		printf("Upisite eMail osobe:");
		scanf(" %s", noviElement->eMail);
	}
	printf("Status favorita osobe: (0 - Ne, 1 - Da)");
	scanf(" %s", noviElement->favorit);

	c = noviElement->naziv[0];
	c = c - 65;

	if (kontakti[c] == NULL)
	{
		kontakti[c] = (struct kontakt*)malloc(sizeof(Kontakt));
		kontakti[c]->next = NULL;
	}
	slovoAdresara = kontakti[c];
	
	while (slovoAdresara != NULL) {
		
		if (_strcmpi(slovoAdresara->naziv, noviElement->naziv) > 0)
			break;
		slovoAdresara = slovoAdresara->next;
	}

	noviElement->next = slovoAdresara->next;
	//slovoAdresara->next->prev = noviElement;
	slovoAdresara->next = noviElement;
	//noviElement->prev = slovoAdresara;

	return 1;
}

struct kontakt* PronadiKontakt(struct kontakt** kontakt)
{
	struct kontakt* temp = NULL;
	char posljednji[30] = { 0 };
	char index = 0;

	printf("\nUpisite naziv kontakta:\t");
	scanf(" %s", posljednji);
	index = posljednji[0] - 65;
	
		temp = kontakt[index];
		while (temp != NULL)
		{
			if (strcmp(temp->naziv, posljednji) == 0)
			{
				printf("\nKontakt pronaden!\n");
				printf("Naziv: %s \n ", temp->naziv);
				printf("Broj: %d \n ", temp->broj);
				if (temp->fbProfil != NULL)
					printf("FB profil: %s \n", temp->fbProfil);
				if (temp->eMail != NULL)
					printf("eMail: %s \n", temp->eMail);

				return temp;
			}
			temp = temp->next;
		}
	
	printf("Nije pronaden\n");
	return NULL;
}

int UrediKontakt(struct kontakt** kontakt)
{
	int izbor = 0;
	struct kontakt* trenutni = PronadiKontakt(kontakt);
	struct kontakt* temp = NULL;

	temp = trenutni;

	if (trenutni == NULL)
	{
		printf("\nTrazeni kontakt ne postoji!\n");
		return 0;
	}

	printf("\n0 - Ne, 1 - Da\n");
	printf("\nZelite li promijeniti naziv kontakta?\t");
	scanf(" %d", izbor);
	if (izbor = 1)
	{
		printf("\nUpisite naziv osobe:\t");
		scanf(" %s", trenutni->naziv);
	}
	printf("\nZelite li promijeniti broj kontakta?\t");
	scanf(" %d", izbor);
	if (izbor = 1)
	{
		printf("\nUpisite broj osobe:\t");
		scanf(" %s", trenutni->broj);
	}
	printf("\nZelite li promijeniti fb profil kontakta?\t");
	scanf(" %d", izbor);
	if (izbor = 1)
	{
		printf("\nUpisite fb profil osobe:\t");
		scanf(" %s", trenutni->fbProfil);
	}
	printf("\nZelite li promijeniti eMail kontakta?\t");
	scanf(" %d", izbor);
	if (izbor = 1)
	{
		printf("\nUpisite eMail osobe:\t");
		scanf(" %s", trenutni->eMail);
	}
	printf("\nZelite li promijeniti status favorita kontakta?\t");
	scanf(" %d", izbor);
	if (izbor = 1)
	{
		printf("\nUpisite status favorita osobe:\t");
		scanf(" %s", trenutni->favorit);
	}

	if (trenutni->naziv != temp->naziv)
	{
		NoviKontakt(trenutni);
		free(temp);
	}
	return 1;
}

int IzbrisiKontakt(struct kontakt** head)
{
	struct kontakt* prethodni = NULL;
	struct kontakt* izbrisi = PronadiKontakt(head);
	if (izbrisi == NULL)
	{
		printf("\nNema se što izbrisati!\n");
		return 0;
	}

	prethodni = PronadiPrethodni(head, izbrisi);
	prethodni->next = izbrisi->next;
	//izbrisi->next->prev = prethodni;

	free(izbrisi);

	return 1;
}

struct kontakt* PronadiPrethodni(struct kontakt** head, struct kontakt* trenutni)
{
	int i = 0;
	struct kontakt* temp = NULL;
	char index = trenutni->naziv[0] - 65;
	
		temp = head[index];
		while (temp != NULL && temp->next != trenutni)
		{
			temp = temp->next;
		}
		
		if (temp == NULL)
		{
			printf("Oprez - temp == NULL");
			return temp;
		}
			

		return temp;
}

int PrikaziSve(struct kontakt **prvi)
{
	for (int i = 0; i < NUM_CONTACTS; i++)
	{
		/*if (prvi[i] == NULL)
		{
			printf("\nPrazno!\n");
			return 0;
		}*/
		while (prvi[i] != NULL && prvi[i]->next != NULL)
		{
			prvi[i] = prvi[i]->next;
			printf("\nNaziv: %s \n", prvi[i]->naziv);
			printf("Broj: %d \n ", prvi[i]->broj);
			if (prvi[i]->fbProfil != NULL)
				printf("FB profil: %s \n", prvi[i]->fbProfil);
			if (prvi[i]->eMail != NULL)
				printf("eMail: %s \n", prvi[i]->eMail);
		}
	}
	return 1;
}

int PrikaziFavorite(struct kontakt** prvi)
{
	for (int i = 0; i < NUM_CONTACTS; i++)
	{
		/*if (prvi[i] == NULL)
		{
			printf("\nPrazno!\n");
			return 0;
		}*/
		while (prvi[i] != NULL && prvi[i]->next != NULL)
		{
			prvi[i] = prvi[i]->next;
			if(prvi[i]->favorit == 1)
			{
				printf("\nNaziv: %s \n", prvi[i]->naziv);
				printf("Broj: %d \n ", prvi[i]->broj);
				if (prvi[i]->fbProfil != NULL)
					printf("FB profil: %s \n", prvi[i]->fbProfil);
				if (prvi[i]->eMail != NULL)
					printf("eMail: %s \n", prvi[i]->eMail);
			}
		}
	}
	return 1;
}
