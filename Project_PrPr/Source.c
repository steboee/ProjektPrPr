#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>






//VYPIS ZO SUBORU
void function_v(int* pacienti,FILE** ptr) {
	*ptr = fopen("pacienti.txt", "r");
	if (*ptr == NULL) {
		printf("NEPODARILO SA OTVORIT SUBOR");
		exit(1);
	}
	char buff[100];
	int pocet_riadkov = 0;
	if (*pacienti == 0) {
		rewind(*ptr);			// nastavenie sa v subore na zaciatok.
		int x;
		x = pocet_riadkov;								//x = lokalna premenna pre nasledujuci for aby nsa zachovala premenná "pocet_riadkov"
		for (x; x > 0; x = x - 7) {						// zistenie poctu pacientov
			(*pacienti) = (*pacienti) + 1;
		}
	}
	for (int i = 1; fgets(buff, sizeof(buff), *ptr) != NULL; i++) { // zistovanie poctu riadkov v zaznamoch
		pocet_riadkov++;
	}
 	fseek(*ptr, 0, SEEK_SET);
	int korektnost = 0;
	int pocitadlo = 0;
	printf("\n------------------- ZACIATOK ZAZNAMOV -------------------\n\n");
	for (int i = 1; i <= pocet_riadkov; i++) {
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
				printf("###### - Nekorektne zadany vstup Diagnoza - #######\n\n");
				korektnost++;
			}
			else if (buff[0] <= 'A' || buff[0] >= 'Z') {
				printf("###### - Nekorektne zadany vstup Diagnoza - #######\n\n");
				korektnost++;
			}
			else if (dia > 99) {
				printf("###### - Nekorektne zadany vstup Diagnoza - #######\n\n");
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
			//int pozicia = 0;
			//int bodka=0;
			printf("Vysledok: %s", buff);
			if (atoi(buff) > 1000) {
				printf("###### - Nekorektne zadany vstup Vysledok - #######\n\n");
				korektnost++;
			}
			/*else {
				while (buff[pozicia] != '\0') {
					if (buff[pozicia] == '.') {
						bodka = pozicia;
					}
					pozicia++;
				}
				int pocet_desatinnych = (strlen(buff)-1) - (bodka + 1);
				if (pocet_desatinnych > 4) {
					printf("###### - Nekorektne zadany vstup Vysledok - #######\n\n");
					korektnost++;
				}
			}*/
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
	

	int pocet_mensich_datumov = 0, position = 0;			
	for (int i = 0; i < pacienti; i++) {								// ALOKOVALIE POLA DIAGNOZA[i] + zistovanie kolko datumov je mensich ako vstupny
		if (inputdate > atoi(pole_datum_o[i])) {
			pole_DIAGNOZY[position] = calloc(5, sizeof(char));
			pole_DIAGNOZY[position] = (pole_diagnoza_o)[i];
			position++;
			pocet_mensich_datumov++;
		}
	}
	
	

	int dlzka = 5;
	int max = 0;
	int pocet[100] = { 0 };
	char* str[5] = {""};
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
		//free(pole_DIAGNOZY[i]);
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
		//(*pole_vysledok)[i][strlen((*pole_vysledok)[i]) - 1] = '\0';				//na posledne miesto kde je obycajne \n da znak \0

		(*pole_datum)[i] = calloc(50, sizeof(char));
		fgets((*pole_datum)[i], 50, file);
		(*pole_vysledok)[i][strlen((*pole_vysledok)[i]) - 1] = '\0';				//na posledne miesto kde je obycajne \n da znak \0

		fgets(buff, sizeof(buff), file);
	}
	puts("");
	printf("------------------- ALOKOVANIE POLI ZACALO -------------------\n");
	printf("------------------- ALOKOVANIE POLI UKONCILO -------------------\n");
	puts("");
	
}



//RODNE CISLO : VYSETRENIE a VYSLEDOK 
void function_s(char**pole_rodnecislo,char**pole_vysetrenie,char**pole_vysledok,int pacienti) {
	
	puts("");
	printf("------------------- FUNKCIA S  -------------------\n");
	char vstup[12];												//lokalny string pre vstup
	printf("Nacitaj rodne cislo: ");
	scanf("%s", &vstup);
	int position = -1;											// Pre pripad zeby sa rodne cislo nenaslo v zozname
	for (int i = 0; i < pacienti;i++) {
		printf("%s\n", vstup);
		printf("%s\n",pole_rodnecislo[i]);
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



void function_h(char** pole_rodnecislo,char**pole_diagnoza,int pacienti) {
	if (pole_rodnecislo == NULL) {
		printf("Polia niesu Vytvorene - alokuj stalcenim n\n");
		return;
	}
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
	for (int i = 0; i < pacienti; i++) {
		if (strcmp(diagnoza, pole_diagnoza[i]) == 0) {
			int desiatky = ((pole_rodnecislo[i])[0] - '0') * 10 + ((pole_rodnecislo[i])[1] - '0') * 1;
			pohlavie = ((pole_rodnecislo[i])[2] - '0');				//ZENY MAJU V RODNOM CISLE PRI MESIACOCH +50 takze staci desiatky poziret

			if (desiatky < 20) {					//ZISTOVANIE ÈI narodeny v rokoch 2000 alebo 1900
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

	//VYPIS MUZOV
	printf("Muzi:\n");
	for (int i = 0; i < 1; i++) {
		int Freq[100];
		int Count;
		for (int i = 0; i < pocet_m; i++)
		{
			Count = 1;								//Vždy je jeden prvok
			for (int j = i + 1; j < pocet_m; j++)
			{
				if (vek_m[i] == vek_m[j])
				{
					Count++;			// pocet sa zvysi o 1 ak sa nasiel taky isty vek
					Freq[j] = 0;		// Ak sa rovna tak nanho nastav nulu
				}
			}
			if (Freq[i] != 0)			// Ak Freq[i] == 0  --> Tento prvok už  bol zarataný...... pozri komentár o jedno vyssie
			{
				Freq[i] = Count;		// Ak Freq[i] != 0 ---> Tak prirad pocet 
			}
		}
		for (int i = 0; i < pocet_m; i++)		//Vypis pre muzov ktory maju danu diagnozu , pocet_z --> pocet muzov so zadanou diagnozou 
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
		for (int i = 0; i < pocet_z; i++)
		{
			Count = 1;								//Vždy je jedne prvok
			for (int j = i + 1; j < pocet_z; j++)
			{
				if (vek_z[i] == vek_z[j])
				{
					Count++;			// pocet sa zvysi o 1 ak sa nasiel taky isty vek
					Freq[j] = 0;		// Ak sa rovna tak nanho nastav nulu
				}
			}
			if (Freq[i] != 0)			// Ak Freq[i] == 0  --> Tento prvok už  bol zarataný...... pozri komentár o jedno vyssie
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


void function_p() {
	char* rodnecislo[10*sizeof(char)];
	char* vysetrenie[4];
	char* datum[4];
	int vysledok;
	printf("Nacitaj rodne cislo: ");
	scanf("%s", rodnecislo);
	printf("Nacitaj vysetrenie: ");
	scanf("%s", vysetrenie);
	printf("Nacitaj datum vysetrenia: ");
	scanf("%s", datum);
	printf("Nacitaj vysledok: ");
	scanf("%d", &vysledok);
	printf("Pacientovi s rodnym cislo %s bol zmeneny vysledok vysetrenia %s z povodnej hodnoty 214 na novu hodnotu %d", rodnecislo, vysetrenie, vysledok);
	

}






int main() {
	char input;
	FILE* file = NULL;
	int pacienti = 0;
	char** pole_meno = NULL, ** pole_rodnecislo = NULL, ** pole_diagnoza = NULL, ** pole_vysetrenie = NULL, ** pole_vysledok = NULL, ** pole_datum = NULL;
	while (scanf("%c", &input)) {
		if (input == 'v') {
			function_v(&pacienti, &file);
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
			function_p();
		}
		if (input == 'k'){
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
			exit(1);
		}
		
	}
	
}