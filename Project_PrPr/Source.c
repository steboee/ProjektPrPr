#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void function_v(int* pacienti,FILE** ptr) {
	*ptr = fopen("pacienti.txt", "r");
	if (*ptr == NULL) {
		printf("NEPODARILO SA OTVORIT SUBOR");
		exit(1);
	}
	char buff[100];
	int pocet_riadkov = 0;
	*pacienti = 0;
	for (int i = 1; fgets(buff, sizeof(buff), *ptr) != NULL; i++) { // zistovanie poctu riadkov v zaznamoch
		pocet_riadkov++;
	}		
	rewind(*ptr);			// nastavenie sa v subore na zaciatok.
	int x;
	x = pocet_riadkov;								//x = lokalna premenna pre nasledujuci for aby nsa zachovala premenná "pocet_riadkov"
	for (x; x > 0; x = x - 7) {						// zistenie poctu pacientov
		(*pacienti) = (*pacienti) + 1 ;
	}
	
	int korektnost = 0;
	int pocitadlo = 0;
	printf("\n------------------- ZACIATOK ZAZNAMOV -------------------\n\n");
	for (int i = 1; i <= pocet_riadkov; i++) {
		fgets(buff, sizeof(buff), *ptr);
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
		else if (i == 4 + 7 * pocitadlo) {
			printf("Vysetrenie: %s", buff);
			if (strlen(buff) - 1 > 50) {
				printf("###### - Nekorektne zadany vstup Vysetrenie - #######\n\n");
				korektnost++;
			}
		}
		else if (i == 5 + 7 * pocitadlo) {
			printf("Vysledok: %s", buff);
			if (atoi(buff) >= 1000) {
				printf("###### - Nekorektne zadany vstup Vysledok - #######\n\n");
				korektnost++;
			}
		}
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

void function_o(FILE*file) {
	
	char** pole_datum_o,** pole_diagnoza_o;
	
	
	if (file == NULL) {
		printf("Nebol otvoreny subor pacienti.txt , otvor stalcenim v\n");
		return;
	}
	char inputdatum[100];
	printf("Macitaj datum vo formate rrrrmmdd: ");
	scanf("%s", inputdatum);
	if (strlen(inputdatum) > 8) {
		printf("###### - Nekoretny vstup - ######\n");
		return;
	}
	
	char buff[100];
	int pocet_riadkov = 0;
	int pacienti = 0;
	fseek(file, 0, SEEK_SET);
	
	for (int i = 1; fgets(buff, sizeof(buff), file) != NULL; i++) { // zistovanie poctu riadkov v zaznamoch
		pocet_riadkov++;
	}
	fseek(file, 0, SEEK_SET);					 // nastavenie sa v subore na zaciatok.
	int x;
	x = pocet_riadkov;								//x = lokalna premenna pre nasledujuci for aby nsa zachovala premenná "pocet_riadkov"
	
	for (x; x > 0; x = x - 7) {						// zistenie poctu pacientov
		pacienti++;
	}

	pole_diagnoza_o = calloc(pacienti, sizeof(char*));
	pole_datum_o = calloc(pacienti, sizeof(char*));

	for (int i = 0; i < pacienti; i++) {
		fgets(buff, sizeof(buff), file);					//Meno priezvisko
		fgets(buff, sizeof(buff), file);					//Rodne cislo

		pole_diagnoza_o[i] = calloc(50, sizeof(char*));		//Diagnoza
		fgets(pole_diagnoza_o[i], 50 - 1, file);

		fgets(buff, sizeof(buff), file);					//Vysetrenie
		fgets(buff, sizeof(buff), file);					//Vysledok

		pole_datum_o[i] = calloc(50, sizeof(char*));		//Datum
		fgets(pole_datum_o[i], 50 - 1, file);
		
		fgets(buff, sizeof(buff), file);					//prazdny riadok za kazdym zaznamom
	}
	
	int inputdate = atoi(inputdatum);
	printf("%d\n", inputdate);
	

	char **pole_DATES, **pole_DIAGNOSIS;
	int pocet_mensich_datumov = 0;
	for (int i = 0; i < pacienti; i++) {
		if (inputdate > atoi(pole_datum_o[i])) {
			pocet_mensich_datumov++;
		}
	}
	pole_DATES = calloc(pocet_mensich_datumov, sizeof(char*));
	pole_DIAGNOSIS = calloc(pocet_mensich_datumov, sizeof(char*));

	for (int i = 0; i < pocet_mensich_datumov; i++) {
		pole_DATES[i] = calloc(10, sizeof(char));
		pole_DIAGNOSIS[i] = calloc(10, sizeof(char));
	}
	int position = 0;
	for (int i = 0; i < pacienti; i++) {
		if (inputdate > atoi(pole_datum_o[i])) {
			pole_DATES[position] = pole_datum_o[i];
			pole_DIAGNOSIS[position] = pole_diagnoza_o[i];
			position++;
		}
	}
	
	for (int j = 0; j < pocet_mensich_datumov; j++) {
		int count = 0;
		for (int i = 0; i < pocet_mensich_datumov; i++) {
			if (strcmp(pole_DIAGNOSIS[j], pole_DIAGNOSIS[i]) == 0) {
				count++;

			}
			else {
			}
		}
		char number_str[100];
		sprintf(number_str, "%d", count);
		printf("%s\n", number_str);
		pole_DIAGNOSIS[j] = number_str;
		
	}
	printf("%s", pole_DIAGNOSIS[1]);
	
	
	
	
}

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
		(*pole_rodnecislo)[i][strlen((*pole_rodnecislo)[i]) - 1] = '\0';			//na posledne miesto kde je obycajne \n da znak \0

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
	printf("------------------- ALOKOVANIE  -------------------\n")
}

void function_s(FILE*file,char**pole_rodnecislo,char**pole_vysetrenie,char**pole_vysledok,int pacienti) {
	if (pole_rodnecislo == NULL) {
		printf("Polia niesu Vytvorene - alokuj stalcenim n\n");
		return;
	}
	
	char vstup[12];
	printf("Nacitaj rodne cislo: ");
	scanf("%s", &vstup);
	
	int position=0;
	int y = atoi(vstup);
	for (int i = 0; i < pacienti;i++) {
		int x = atoi(pole_rodnecislo[i]);
		if (x==y){
			position = i;
		}
	}
	puts("");
	printf("------------------- Rodne cislo : %d -------------------\n",vstup);
	printf("Vysetrenie: %s\n", pole_vysetrenie[position]);
	printf("Vysledok: %s\n", pole_vysledok[position]);
	puts("");
	
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
			function_s(file,pole_rodnecislo,pole_vysetrenie,pole_vysledok,pacienti);
		}
		if (input == 'k'){
			exit(1);
		}
		
	}
	
}