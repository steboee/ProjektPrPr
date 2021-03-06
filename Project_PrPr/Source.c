﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//VYPIS ZO SUBORU
void function_v(int* pacienti,FILE** ptr,int *pocet_riadkov) {
	*ptr = fopen("pacienti.txt", "r");
	
	if (*ptr == NULL) {
		printf("NEPODARILO SA OTVORIT SUBOR");
		exit(1);
	}
	char buff[100];
	(*pocet_riadkov) = 0;
	if (*pacienti == 0) {
		rewind(*ptr);	// nastavenie sa v subore na zaciatok.
		for (int i = 1; fgets(buff, sizeof(buff), *ptr) != NULL; i++) { // zistovanie poctu riadkov v zaznamoch
			(*pocet_riadkov) = (*pocet_riadkov) + 1;
		}
		int x;
		x = (*pocet_riadkov);								//x = lokalna premenna pre nasledujuci for aby nsa zachovala premenná "pocet_riadkov"
		for (x; x > 0; x = x - 7) {						// zistenie poctu pacientov
			(*pacienti) = (*pacienti) + 1;
		}
	}
	else {
		for (int i = 1; fgets(buff, sizeof(buff), *ptr) != NULL; i++) { // zistovanie poctu riadkov v zaznamoch
			(*pocet_riadkov) = (*pocet_riadkov) + 1;
		}
	}
	
 	fseek(*ptr, 0, SEEK_SET);
	int korektnost = 0;
	int pocitadlo = 0;
	printf("\n------------------- ZACIATOK ZAZNAMOV -------------------\n\n");

	for (int i = 1; i <= (*pocet_riadkov); i++) {
		fgets(buff, sizeof(buff), *ptr);
		//MENO PRIEZVISKO
		if (i == 1 + 7 * pocitadlo) {
			printf("Meno prizevisko: %s", buff);
			if (strlen(buff) - 1 > 50) {					// Meno priezvisko moze byt najviac 50 znakovy retazec	
				printf("###### - Nekorektne zadany vstup Meno priezvisko - #######\n\n");
				korektnost++;
			}
			else {
				for (int i = 0; i < (int)strlen(buff) - 1; i++) {
					if ('A' <= buff[i] && buff[i] <= 'Z' || 'a' <= buff[i] && buff[i] <= 'z' || buff[i] == ' ') {
						continue;
					}
					else {
						korektnost++;
						printf("###### - Nekorektne zadany vstup Meno priezvisko - #######\n\n");
					}
				}
			}
		}
		//RODNE CISLO
		else if (i == 2 + 7 * pocitadlo) {
			printf("Rodne cislo: %s", buff);
			long long cislo = atoll(buff);				// Vytvorenie long long zo stringu
			if (strlen(buff) != 11) {						// Rodne cislo musi byt 10-miestne 
				printf("###### - Nekorektne zadany vstup Rodne cislo - #######\n\n");
				korektnost++;
			}
			else if ((cislo % 11) != 0) {									// Rodne cislo musi byt delitelne 11
				printf("###### - Nekorektne zadany vstup Rodne cislo - #######\n\n");
				korektnost++;
			}

		}
		//DIAGNOZA
		else if (i == 3 + 7 * pocitadlo) {
			printf("Diagnoza: %s", buff);
			int dia = atoi(buff);
			if (strlen(buff) != 4) {
				printf("###### - Nekorektne zadany vstup Diagnoza1 - #######\n\n");
				korektnost++;
			}
			else if (buff[0] < 'A' || buff[0] > 'Z') {
				printf("###### - Nekorektne zadany vstup Diagnoza2 - #######\n\n");
				korektnost++;
			}
			else if (dia > 99) {
				printf("###### - Nekorektne zadany vstup Diagnoza3 - #######\n\n");
				korektnost++;
			}

		}
		//VYSETRENIE
		else if (i == 4 + 7 * pocitadlo) {
			printf("Vysetrenie: %s", buff);
			if (strlen(buff) - 1 > 50) {
				printf("###### - Nekorektne zadany vstup Vysetrenie - #######\n\n");
				korektnost++;
			}
		}
		//VYSLEDOK
		
		else if (i == 5 + 7 * pocitadlo) {
			int pozicia = 0;
			int bodka=0;
			printf("Vysledok: %s", buff);
			if (atoi(buff) > 1000) {
				printf("###### - Nekorektne zadany vstup Vysledok - #######\n\n");
				korektnost++;
			}
			else {
				while (buff[pozicia] != '\0') {
					if (buff[pozicia] == '.') {
						bodka = pozicia;
					}
					pozicia++;
				}
				int pocet_desatinnych = (int)((strlen(buff)-1)) - (bodka + 1);
				if (pocet_desatinnych > 4) {
					printf("###### - Nekorektne zadany vstup Vysledok - #######\n\n");
					korektnost++;
				}
			}
		}

		//DATUM
		else if (i == 6 + 7 * pocitadlo) {
			printf("Datum: %s", buff);
			if (strlen(buff) > 9) {					// string ma na konci este jeden znak okrem toho co je v.txt preto 9
				printf("###### - Nekorektne zadany vstup Datum - #######\n\n");
				korektnost++;
			}
			else {
				for (int j = 0; j < 8; j++) {			//prehcadzam jedntolivymi znakmi v stringu ale poslendy \n neberie
					if (48 <= (int)buff[j] && (int)buff[j] <= 57) {
						continue;
					}
					else {
						printf("###### - Nekorektne zadany vstup Datum - #######\n\n");
						korektnost++;
					}
				}
			}

		}
		else if (i == 7 + 7 * pocitadlo) {
			puts("");
			pocitadlo++;
		}

	}
	printf("\n------------------- KONIEC ZAZNAMOV -------------------\n");
	
	if (korektnost > 0) {
		printf("Niektore zapisy boli zadane nekoretkne\n");
		exit(1);
	}
	

}



//NAJCASTEJSIA DIAGNOZA
void function_o(FILE*file) {
	if (file == NULL) {
		printf("Nebol otvoreny subor pacienti.txt , otvor stalcenim v\n");
		return;
	}
	
	char inputdatum[100];
	printf("Nacitaj datum vo formate rrrrmmdd: ");
	scanf("%s", inputdatum);
	inputdatum[strlen(inputdatum)] = '\0';
	if (strlen(inputdatum) > 8) {
		printf("###### - Nekoretny vstup - ######\n");
		return;
	}
	
	
	char buff[100];
	int pocet_riadkov = 0;
	int pacienti = 0;
	fseek(file, 0, SEEK_SET);
	
	//POCET RIADKOV
	for (int i = 1; fgets(buff, sizeof(buff), file) != NULL; i++) { // zistovanie poctu riadkov v zaznamoch
		pocet_riadkov++;
	}
	
	fseek(file, 0, SEEK_SET);	// nastavenie sa v subore na zaciatok.
	int x;
	x = pocet_riadkov;		//x = lokalna premenna pre nasledujuci for aby nsa zachovala premenná "pocet_riadkov"
	
	//POCET PACIENTOV
	for (x; x > 0; x = x - 7) {						// zistenie poctu pacientov
		pacienti++;
	}

	//ALOKUJ premenné datumov a diagnoz
	char** pole_datum_o, ** pole_diagnoza_o;

	pole_diagnoza_o = calloc(pacienti, sizeof(char*));
	pole_datum_o = calloc(pacienti, sizeof(char*));

	// VLOZENIE DIAGNOZ A DATUMOV DO POLÍ
	for (int i = 0; i < pacienti; i++) {
		fgets(buff, sizeof(buff), file);					//Meno priezvisko
		fgets(buff, sizeof(buff), file);					//Rodne cislo

		pole_diagnoza_o[i] = calloc(50, sizeof(char));		//Diagnoza
		fgets(pole_diagnoza_o[i], 50 - 1, file);
		pole_diagnoza_o[i][strlen(pole_diagnoza_o[i]) -1] = '\0';

		fgets(buff, sizeof(buff), file);					//Vysetrenie
		fgets(buff, sizeof(buff), file);					//Vysledok

		pole_datum_o[i] = calloc(50, sizeof(char));		//Datum
		fgets(pole_datum_o[i], 50 - 1, file);
		
		fgets(buff, sizeof(buff), file);					//prazdny riadok za kazdym zaznamom
	}
	

	

	
	//FUNCKIA o ... realne :
	int inputdate = atoi(inputdatum);		//vlozeny datum daj na int 
	char** pole_DIAGNOZY;
	pole_DIAGNOZY = calloc(pacienti, sizeof(char*));
	

	int pocet_mensich_datumov = 0;
	int position = 0;			
	for (int i = 0; i < pacienti; i++) {								// ALOKOVALIE POLA DIAGNOZA[i] + zistovanie kolko datumov je mensich ako vstupny
		if (inputdate > atoi(pole_datum_o[i])) {
			pole_DIAGNOZY[position] = calloc(5, sizeof(char));
			strcpy(pole_DIAGNOZY[position], pole_diagnoza_o[i]);
			position++;
			pocet_mensich_datumov++;
		}
	}
	
	

	int dlzka = 5;
	int max = 0;
	int pocet[100] = { 0 };
	char* str[5] = { "" };
	for (int i = 0; i < pocet_mensich_datumov; i++) {
		for (int j = 0; j < pocet_mensich_datumov; j++) {
			if (strcmp(pole_DIAGNOZY[i],pole_DIAGNOZY[j])==0) {
				pocet[i]++;
			}

		}
		if (pocet[i] > max) {
			max = pocet[i];
			
			*str = pole_DIAGNOZY[i];
		}
	}
	printf("Najcastejsie vysetrovana diagnoza do %s je %s vyskytla sa %d-krat\n",inputdatum, *str,max);
	for (int i = 0; i < pacienti; i++) {
		free(pole_datum_o[i]);
		free(pole_diagnoza_o[i]);
	}
	for (int i = 0; i < position; i++) {
		free(pole_DIAGNOZY[i]);
	}
	free(pole_diagnoza_o);
	free(pole_datum_o);
	free(pole_DIAGNOZY);
}



//ALOKUJE POLIA
void function_n(FILE* file, char*** pole_meno, char*** pole_rodnecislo, char*** pole_diagnoza, char*** pole_vysetrenie, char*** pole_vysledok, char*** pole_datum) {
	
	if (file == NULL) {
		printf("Neotvoril sa subor , subor sa otvori stlacením v\n");
		return;
	}
	char buff[100];
	int pocet_riadkov = 0;
	fseek(file, 0, SEEK_SET);
	for (int i = 1; fgets(buff, sizeof(buff), file) != NULL; i++) { // zistovanie poctu riadkov v zaznamoch
		pocet_riadkov++;
	}
	fseek(file, 0, SEEK_SET);					 // nastavenie sa v subore na zaciatok.
	int x;
	x = pocet_riadkov;
	int pacienti = 0;					//x = lokalna premenna pre nasledujuci for aby nsa zachovala premenná "pocet_riadkov"
	for (x; x > 0; x = x - 7) {						// zistenie poctu pacientov
		pacienti ++;
	}
	if (*pole_meno != NULL) {
		for (int i = 0; i < pacienti; i++) {
			free((*pole_meno)[i]);
			free((*pole_rodnecislo)[i]);
			free((*pole_diagnoza)[i]);
			free((*pole_vysetrenie)[i]);
			free((*pole_vysledok)[i]);
			free((*pole_datum)[i]);
		}
		free(*pole_meno);
		free(*pole_rodnecislo);
		free(*pole_diagnoza);
		free(*pole_vysetrenie);
		free(*pole_vysledok);
		free(*pole_datum);
	}
	
	
	*pole_meno = calloc(pacienti, sizeof(char*));
	*pole_rodnecislo = calloc(pacienti, sizeof(char*));
	*pole_diagnoza = calloc(pacienti, sizeof(char*));
	*pole_vysetrenie = calloc(pacienti, sizeof(char*));
	*pole_vysledok = calloc(pacienti, sizeof(char*));
	*pole_datum = calloc(pacienti, sizeof(char*));

	for (int i = 0; i < pacienti; i++) {
		(*pole_meno)[i] = calloc(55, sizeof(char));
		fgets((*pole_meno)[i], 55, file);
		(*pole_meno)[i][strlen((*pole_meno)[i]) - 1] = '\0';			//na posledne miesto kde je obycajne \n da znak \0

		(*pole_rodnecislo)[i] = calloc(12, sizeof(char));
		fgets((*pole_rodnecislo)[i], 12, file);
		(*pole_rodnecislo)[i][strlen((*pole_rodnecislo)[i]) -1 ] = '\0';			//na posledne miesto kde je obycajne \n da znak \0

		(*pole_diagnoza)[i] = calloc(12, sizeof(char));
		fgets((*pole_diagnoza)[i], 10, file);
		(*pole_diagnoza)[i][strlen((*pole_diagnoza)[i]) - 1] = '\0';				//na posledne miesto kde je obycajne \n da znak \0

		(*pole_vysetrenie)[i] = calloc(55, sizeof(char));
		fgets((*pole_vysetrenie)[i], 50, file);
		(*pole_vysetrenie)[i][strlen((*pole_vysetrenie)[i]) - 1] = '\0';			//na posledne miesto kde je obycajne \n da znak \0

		(*pole_vysledok)[i] = calloc(55, sizeof(char));
		fgets((*pole_vysledok)[i], 50, file);
		(*pole_vysledok)[i][strlen((*pole_vysledok)[i]) - 1] = '\0';				//na posledne miesto kde je obycajne \n da znak \0

		(*pole_datum)[i] = calloc(50, sizeof(char));
		fgets((*pole_datum)[i], 50, file);
		(*pole_datum)[i][strlen((*pole_datum)[i]) - 1] = '\0';				//na posledne miesto kde je obycajne \n da znak \0

		fgets(buff, sizeof(buff), file);
	}
	puts("");
	printf("------------------- ALOKOVANIE POLI ZACALO -------------------\n");
	printf("------------------- ALOKOVANIE POLI UKONCILO -------------------\n");
	puts("");
	
}



//RODNE CISLO : VYSETRENIE a VYSLEDOK 
void function_s(char**pole_rodnecislo,char**pole_vysetrenie,char**pole_vysledok,int pacienti) {
	if (pole_rodnecislo == NULL) {
		printf("Polia niesu Vytvorene - alokuj stalcenim n\n");
		return;
	}
	puts("");
	printf("------------------- FUNKCIA S  -------------------\n");
	char vstup[12];												//lokalny string pre vstup
	printf("Nacitaj rodne cislo: ");
	scanf("%s", &vstup);
	int position = -1;											// Pre pripad zeby sa rodne cislo nenaslo v zozname
	for (int i = 0; i < pacienti;i++) {
		if (strncmp(vstup,pole_rodnecislo[i],10)==0){			// strncmp porovnava 2 stringy po znaku (10 prvych znakov skontroluje)
			position = i;										// nastav position na momentalnu poziciu ----> i
		}

	}
	if (position == -1) {										// Ak sa nenajde rodne cislo v zozname
		printf("Pacient s rodnym cislo: %s nie je v zozname!!\n", vstup);
		return;
	}
	//VYPIS
	puts("");
	printf("Rodne cislo : %s\n",vstup);
	printf("Vysetrenie: %s\n", pole_vysetrenie[position]);
	printf("Vysledok: %s\n", pole_vysledok[position]);
	puts("");
	printf("------------------- FUNKCIA S  -------------------\n");
	puts("");
	
}



// HISTOGRAM ZENY MUZI
void function_h(char** pole_rodnecislo,char**pole_diagnoza,int pacienti) {
	if (pole_rodnecislo == NULL || pole_diagnoza == NULL) {
		printf("Polia niesu Vytvorene - alokuj stalcenim n\n");
		return;
	}
	int pocetpac = pacienti;
	char diagnoza[4] = {""};
	printf("Zadaj Diagnozu: ");
	scanf("%s", diagnoza);
	
	int* vek_m = calloc(pacienti, sizeof(int));
	int* vek_z = calloc(pacienti, sizeof(int));
	int pohlavie = 0;
	int roknarodenia=0;
	int pocet_m = 0;
	int pocet_z = 0;
	//vek muzov a zien uklada do polí
	for (int i = 0; i < pocetpac; i++) {
		if (strcmp(diagnoza, pole_diagnoza[i]) == 0) {
			int desiatky = ((pole_rodnecislo[i])[0] - '0') * 10 + ((pole_rodnecislo[i])[1] - '0') * 1;
			pohlavie = ((pole_rodnecislo[i])[2] - '0');				//ZENY MAJU V RODNOM CISLE PRI MESIACOCH +50 takze staci desiatky poziret

			if (desiatky < 20) {					//ZISTOVANIE ČI narodeny v rokoch 2000 alebo 1900
				roknarodenia = 2000 + desiatky;
			}
			else {
				roknarodenia = 1900 + desiatky;
			}


			if (pohlavie >= 5) {				//AK ZENA TAK
				vek_z[pocet_z] = 2020 - roknarodenia;
				pocet_z++;
			}
			else {
				vek_m[pocet_m] = 2020 - roknarodenia;
				pocet_m++;
			}
		}
		
	}
	printf("\n");
	printf("Pocet muzov s %s: %d\n", diagnoza, pocet_m);
	printf("Pocet zien s %s: %d\n", diagnoza, pocet_z);
	printf("\n");


	//BUBBLE SORT MUZOV
	int i1, j1, temp1;						//temp1 - dočasná premenná , aby mi neprepisovalo vek_m
	for (i1 = 0; i1 < (pocet_m - 1); ++i1)
	{
		for (j1 = 0; j1 < pocet_m - 1 - i1; ++j1)
		{
			if (vek_m[j1] > vek_m[j1 + 1])
			{
				temp1 = vek_m[j1 + 1];
				vek_m[j1 + 1] = vek_m[j1];
				vek_m[j1] = temp1;
			}
		}
	}

	//BUBBLE SORT ZIEN
	int i2, j2, temp2;						//temp2 - dočasná premenná , aby mi neprepisovalo vek_z[na nejakej pozicii]
	for (i2 = 0; i2 < (pocet_z - 1); ++i2)
	{
		for (j2 = 0; j2 < pocet_z - 1 - i2; ++j2)
		{
			if (vek_z[j2] > vek_z[j2 + 1])
			{
				temp2 = vek_z[j2 + 1];
				vek_z[j2 + 1] = vek_z[j2];
				vek_z[j2] = temp2;
			}
		}
	}

	//VYPIS MUZOV
	printf("Muzi:\n");
	for (int i = 0; i < 1; i++) { // Kvoli lokalnym premenným
		int Freq[100];
		int Count;
		for (int i = 0; i < pocet_m; i++){				//pocet_m --> pocet muzov s diagnozou
			Count = 1;									//pocitadlo je 1 lebo sa zacal cyklus čiže ---> pocet_m !=0
			for (int j = i + 1; j < pocet_m; j++)
			{
				if (vek_m[i] == vek_m[j])
				{
					Count++;			// pocet sa zvysi o 1 ak sa nasiel taky isty vek
					Freq[j] = 0;	
				}
			}
			if (Freq[i] != 0)			// Ak Freq[i] == 0  --> Tento prvok už  bol zarataný...... pozri komentár o jedno vyssie
			{
				Freq[i] = Count;		// Ak Freq[i] != 0 ---> Tak prirad pocet 
			}
		}
		for (int i = 0; i < pocet_m; i++)		//Vypis pre muzov ktory maju danu diagnozu , pocet_m --> pocet muzov so zadanou diagnozou 
		{
			if (Freq[i] != 0)				// Ak Freq[i] == 0 ---> Tak tento prvok uz som vypisal 
			{
				printf("%d: %d\n", vek_m[i], Freq[i]);
			}
		}
	}
	printf("\n");

	//VYPIS ZIEN
	printf("Zeny:\n");
	for (int i = 0; i < 1; i++) {
		int Freq[100];
		int Count;									
		for (int i = 0; i < pocet_z; i++){
			Count = 1;										//pocitadlo je 1 lebo sa zacal cyklus čiže ---> pocet_z !=0
			for (int j = i + 1; j < pocet_z; j++)
			{
				if (vek_z[i] == vek_z[j])
				{
					Count++;			// pocet sa zvysi o 1 ak sa nasiel taky isty vek
					Freq[j] = 0;		// Ak sa rovna tak nanho nastav nulu
				}
			}
			if (Freq[i] != 0)			// Ak Freq[i] == 0  --> Tento prvok u  bol zarataný...... pozri komentár o jedno vyssie
			{
				Freq[i] = Count;		// Ak Freq[i] != 0 ---> Tak prirad pocet 
			}
		}
		for (int i = 0; i < pocet_z; i++)		//Vypis pre zeny ktore maju danu diagnozu , pocet_z --> pocet zien so zadanou diagnozou 
		{
			if (Freq[i] != 0)				// Ak Freq[i] == 0 ---> Tak tento prvok uz som vypisal 
			{
				printf("%d: %d\n", vek_z[i], Freq[i]);
			}
		}
	}
	free(vek_m);
	free(vek_z);
}



//PREPIS UDAJoV
void function_p(FILE*ptr,char**pole_meno,char**pole_rodnecislo,char**pole_vysetrenie,char**pole_datum,char**pole_vysledok,int pacienti,int pocet_riadkov) {

	if (pole_rodnecislo == NULL) {
		printf("Polia niesu Vytvorene - alokuj stalcenim n\n");
		return;
	}
	FILE* tempfile = fopen("tempfile.txt", "w");
	if (ptr == NULL) {
		printf("Neotvoreny subor\n");
	}


	char rodnecislo[11];
	char vysetrenie[100];
	char datum[9];
	
	int in_zoznam=0;
	int pozicia = 0;
	double cislo;
	printf("Nacitaj rodne cislo: ");
	scanf("%s", &rodnecislo);
	printf("Nacitaj vysetrenie: ");
	scanf("%s", &vysetrenie);
	printf("Nacitaj datum vysetrenia: ");
	scanf("%s", &datum);
	for (int i = 0; i < pacienti; i++) {
		if (strcmp(pole_rodnecislo[i], rodnecislo) == 0) {			//Ak sa rovna rodne cisla vnor sa dalej 
			
			if (strcmp(pole_vysetrenie[i], vysetrenie) == 0) {		//Ak sa rovna rodne cislo aj vysetrenie vnor sa dalej
				
				if (strcmp(pole_datum[i], datum) == 0){				//Ak sa rovnaju vsetky tak uloz danu poziciu do pozicia
					
					pozicia = i;
					in_zoznam = 1; //pre zistenie ci pacient s danym rodnym cislom, vysetrenim obl vysetreovany v danom datume
				}
			}
		}
	}
	if (in_zoznam == 0) {				//V pripade ak pacient s takymi parametrami nebol najdeny v zozname
		printf("pacient s rodnym cislo %s nieje v zozname!\n", rodnecislo);
		return;
	}
	
	// UKLADA DO DYNAMICKEHO POLA
	cislo = atof((pole_vysledok)[pozicia]);
	printf("Nacitaj novy vysledok: ");
	scanf("%s", pole_vysledok[pozicia]);

	int replace_line = ((pozicia + 1) * 7) - 2;
	int line = 1;

	fseek(ptr, 0, SEEK_SET); //nastavenie na zaciatok file
	char string[100];
	
	fgets(string, sizeof(string), ptr);
	for (int i = 1; i <= pocet_riadkov; i++){
		if (i == replace_line) {
			fputs(pole_vysledok[pozicia],tempfile);
			fputs("\n",tempfile);
		}
		else {
			fputs(string,tempfile);
		}
		fgets(string, sizeof(string), ptr);
	}
	fclose(tempfile);
	fclose(ptr);
	
	//PREPIS SUBORU A ODSTRANENIE docasneho Suboru
	rename("pacienti.txt", "tempfile1.txt");
	rename("tempfile.txt", "pacienti.txt");
	rename("tempfile1.txt", "tempfile.txt");
	remove("tempfile.txt");
	ptr = fopen("pacienti.txt", "r");

	printf("Pacientovi s rodnym cislom %s bol zmeneny vysledok\nvysetrenia %s z povodnej hodnoty %.7g na novu hodnotu %s\n", rodnecislo, vysetrenie, cislo, pole_vysledok[pozicia]);
	
}



//VYPIS 3 NAJVACSICH VYSLEDKOV
void function_z(int pacienti, char** pole_datum, char** pole_vysetrenie, char** pole_vysledok,char**pole_meno){
	if (pole_datum == NULL || pole_vysetrenie == NULL || pole_vysledok == NULL || pole_meno == NULL) {
		printf("Polia niesu Vytvorene - alokuj stalcenim n\n");
		return;
	}
	puts("");
	printf("------------------- FUNKCIA Z  -------------------\n");
	char datum1[100];
	char datum2[100];
	char vysetrenie[100]; 
	printf("Nacitaj 1. datum vo formate rrrrmmdd: ");
	scanf("%s", datum1);
	if (strlen(datum1) != 8) {
		printf("Nekorektny datum!\nNacitaj novu funkciu \n");
		return;
	}
	datum1[strlen(datum1)] = '\0';
	printf("Nacitaj 2. datum vo formate rrrrmmdd: ");
	scanf("%s", datum2);
	if (strlen(datum2) != 8) {
		printf("Nekorektny datum!\nNacitaj novu funkciu \n");
		return;
	}
	datum2[strlen(datum1)] = '\0';

	int date1 = atoi(datum1);
	int date2 = atoi(datum2);
	if (date1 > date2) {
		printf("Koncovy datum sa nachadza pred pociatocnym datumom\n");
		printf("Nacitaj funkciu\n");
		return;
	}
	printf("Nacitaj vysetrenie: ");
	scanf("%s", vysetrenie);

	
	

	int pozicia = 0;
	
	
	char** vysledky, ** vysetrenia,**mena;
	vysledky = calloc(pacienti, sizeof(char*));
	vysetrenia = calloc(pacienti, sizeof(char*));
	mena = calloc(pacienti, sizeof(char*));

	//pozeram na datum a beriem vysledky pacientov v rozmedzi 2 datumov do noveho pola
	for (int i = 0; i < pacienti; i++) {
		if (date1 <= atoi(pole_datum[i]) && atoi(pole_datum[i]) <= date2) {
			vysledky[pozicia] = calloc(10, sizeof(char));
			vysetrenia[pozicia] = calloc(50, sizeof(char));
			mena[pozicia] = calloc(100, sizeof(char));
			strcpy(vysledky[pozicia],pole_vysledok[i]);
			strcpy(vysetrenia[pozicia],pole_vysetrenie[i]);
			strcpy(mena[pozicia], pole_meno[i]);
			pozicia++;
		}
	}

	double max1 = 0, max2 = 0, max3 = 0;
	int meno1=NULL, meno2=NULL, meno3 = NULL;
	int dia_je_v_zozname = 0;
	for (int i = 0; i <pozicia; i++) {
		if (strcmp(vysetrenia[i], vysetrenie) == 0) {
			dia_je_v_zozname++;
			if (atof(vysledky[i]) > max1) {
				max3 = max2;
				meno3 = meno2;
				max2 = max1;
				meno2 = meno1;
				max1 = atof(vysledky[i]);
				meno1 = i;
			
			}
			else if (atof(vysledky[i]) > max2) {
				max3 = max2;
				meno3 = meno2;
				max2 = atof(vysledky[i]);
				meno2 = i;
				
			}
			else if (atof(vysledky[i]) > max3) {
				max3 = atof(vysledky[i]);
				meno3 = i;
				
			}
			
		}
	}
	if (dia_je_v_zozname == 1) {
		puts("");
		printf("Traja pacienti s najvyssimi hodnotami ASLO za obdobie %s - %s su (namerana hodnota v zatvorke):\n", datum1, datum2);
		printf("%s (%s)\n", mena[meno1], vysledky[meno1]);
		for (int i = 0; i < pozicia; i++) {
			free(vysledky[i]);
			free(vysetrenia[i]);
			free(mena[i]);
		}
		free(vysledky);
		free(vysetrenia);
		free(mena);
	}
	else if (dia_je_v_zozname == 2) {
		puts("");
		printf("Traja pacienti s najvyssimi hodnotami ASLO za obdobie %s - %s su (namerana hodnota v zatvorke):\n", datum1, datum2);
		printf("%s (%s)\n", mena[meno1], vysledky[meno1]);
		printf("%s (%s)\n", mena[meno2], vysledky[meno2]);
		for (int i = 0; i < pozicia; i++) {
			free(vysledky[i]);
			free(vysetrenia[i]);
			free(mena[i]);
		}
		free(vysledky);
		free(vysetrenia);
		free(mena);
	}
	else if (dia_je_v_zozname >=3) {
		puts("");
		printf("Traja pacienti s najvyssimi hodnotami ASLO za obdobie %s - %s su (namerana hodnota v zatvorke):\n", datum1, datum2);
		printf("%s (%s)\n", mena[meno1], vysledky[meno1]);
		printf("%s (%s)\n", mena[meno2], vysledky[meno2]);
		printf("%s (%s)\n", mena[meno3], vysledky[meno3]);
		for (int i = 0; i < pozicia; i++) {
			free(vysledky[i]);
			free(vysetrenia[i]);
			free(mena[i]);
		}
		free(vysledky);
		free(vysetrenia);
		free(mena);
	}
	else {
		printf("Diagnoza nieje v zonzame!\n");
		for (int i = 0; i < pozicia; i++) {
			free(vysledky[i]);
			free(vysetrenia[i]);
			free(mena[i]);
		}
		free(vysledky);
		free(vysetrenia);
		free(mena);
		return;
	}


	puts("");
	printf("------------------- FUNKCIA Z  -------------------\n");
	

	
	
	

}



int main() {
	char input;
	FILE* file = NULL;
	int pacienti = 0;
	int pocet_riadkov = 0;
	char** pole_meno = NULL, ** pole_rodnecislo = NULL, ** pole_diagnoza = NULL, ** pole_vysetrenie = NULL, ** pole_vysledok = NULL, ** pole_datum = NULL;
	printf("FUNKCIE:\n");
	printf("v: Vypise vsetky zaznamy a upozorni na pripadne nekorektne zaznamy\n");
	printf("o: Vypise najcastejsiu diagnozu do zadaneho datumu\n");
	printf("n: Alokuje dynamicke polia pre polozky v zozname a vlozi zaznamy\n");
	printf("s: Nacita na zaklade rodneho cisla udaje o pacientovi\n");
	printf("h: Vypise histogram pre danu diagnozu\n");
	printf("p: Prepise vysledok v alokovanom poli aj v txt subore\n");
	printf("z: Vypise 3 pacientov s najvyssimi hodnotami\n");
	puts("");
	while (scanf("%c", &input)) {
		if (input == 'v') {
			function_v(&pacienti, &file, &pocet_riadkov);
		}
		if (input == 'o') {
			function_o(file);
		}
		if (input == 'n') {
			function_n(file, &pole_meno, &pole_rodnecislo, &pole_diagnoza, &pole_vysetrenie, &pole_vysledok, &pole_datum);
		}
		if (input == 's') {
			function_s(pole_rodnecislo,pole_vysetrenie,pole_vysledok,pacienti);
		}
		if (input == 'h') {
			function_h(pole_rodnecislo,pole_diagnoza,pacienti);
		}
		if (input == 'p') {
			function_p(file,pole_meno,pole_rodnecislo,pole_vysetrenie,pole_datum,pole_vysledok,pacienti,pocet_riadkov);
		}
		if (input == 'z') {
			function_z(pacienti,pole_datum,pole_vysetrenie,pole_vysledok,pole_meno);
		}
		if (input == 'k'){
			if (pole_meno != NULL) {
				for (int i = 0; i < pacienti; i++) {
					free((pole_meno)[i]);
					free((pole_rodnecislo)[i]);
					free((pole_diagnoza)[i]);
					free((pole_vysetrenie)[i]);
					free((pole_vysledok)[i]);
					free((pole_datum)[i]);
				}
				free(pole_meno);
				free(pole_rodnecislo);
				free(pole_diagnoza);
				free(pole_vysetrenie);
				free(pole_vysledok);
				free(pole_datum);
			}
			if (file != NULL) {
			
				fclose(file);
				file = NULL;
			}
			
			exit(1);
		}
		
	}
	
}
