#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

function_v(FILE** ptr, int* subor) {
	*ptr = fopen("pacienti.txt", "r");
	if (*ptr == NULL) {
		printf("NEPODARILO SA OTVORIT SUBOR");
		exit(1);
	}
	*subor = 1;
	char buff[100];
	int pocet_riadkov = 0, pacienti = 0;

	for (int i = 1; fgets(buff, sizeof(buff), *ptr) != NULL; i++) { // zistovanie poctu riadkov v zaznamoch
		pocet_riadkov++;
	}
	fseek(*ptr, 1, SEEK_SET);						 // nastavenie sa v subore na zaciatok.
	int x;
	x = pocet_riadkov;								//x = lokalna premenna pre nasledujuci for aby nsa zachovala premenná "pocet_riadkov"
	for (x; x > 0; x = x - 7) {						// zistenie poctu pacientov
		pacienti++;
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
				for (int i = 0; i < strlen(buff) - 1; i++) {
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

void function_o(char*** pole_datum) {
	char buff[100];
	printf("%s", ((*pole_datum)[1]));
	scanf("%s", buff);
	if (strlen(buff) > 8) {
		printf("###### - Nekoretny vstup - ######\n");
		return;
	}
	return;


}





void function_n(int* subor, FILE** file, char*** pole_meno, char*** pole_rodnecislo, char*** pole_diagnoza, char*** pole_vysetrenie, char*** pole_vysledok, char*** pole_datum) {

	if (*subor == 0) {
		printf("Neotovirl sa subor");
		return;
	}


	else {
		char buff[100];
		printf("%s", fgets(buff, sizeof(buff), *file));
		printf("OTvoril sa");
		int pocet_riadkov = 0;
		int pacienti = 0;
		for (int i = 1; fgets(buff, sizeof(buff), *file) != NULL; i++) { // zistovanie poctu riadkov v zaznamoch
			pocet_riadkov++;
		}
		fseek(*file, 1, SEEK_SET);						 // nastavenie sa v subore na zaciatok.
		int x;
		x = pocet_riadkov;								//x = lokalna premenna pre nasledujuci for aby nsa zachovala premenná "pocet_riadkov"
		for (x; x > 0; x = x - 7) {						// zistenie poctu pacientov
			pacienti++;
		}
		printf("HAL");
		*pole_meno = calloc(pacienti, sizeof(char*));
		*pole_rodnecislo = calloc(pacienti, sizeof(char*));
		*pole_diagnoza = calloc(pacienti, sizeof(char*));
		*pole_vysetrenie = calloc(pacienti, sizeof(char*));
		*pole_vysledok = calloc(pacienti, sizeof(char*));
		*pole_datum = calloc(pacienti, sizeof(char*));

		for (int i = 0; i < pacienti; i++) {
			((*pole_meno)[i]) = calloc(100, sizeof(char));
			fgets((*pole_meno)[i], 100, *file);
			((*pole_rodnecislo)[i]) = calloc(pacienti, sizeof(char));
			fgets((*pole_rodnecislo)[i], 50 - 1, *file);
			(*pole_diagnoza)[i] = calloc(pacienti, sizeof(char));
			fgets((*pole_diagnoza)[i], 50 - 1, *file);
			(*pole_vysetrenie)[i] = calloc(pacienti, sizeof(char));
			fgets((*pole_vysetrenie)[i], 50 - 1, *file);
			(*pole_vysledok)[i] = calloc(pacienti, sizeof(char));
			fgets((*pole_vysledok)[i], 50 - 1, *file);
			(*pole_datum)[i] = calloc(pacienti, sizeof(char));
			fgets((*pole_datum)[i], 50 - 1, *file);
			fgets(buff, sizeof(buff), *file);
			printf("Helloooo");
		}
	}




}


int main() {
	char input;
	FILE* file;
	int subor = 0;
	char** pole_meno, ** pole_rodnecislo, ** pole_diagnoza, ** pole_vysetrenie, ** pole_vysledok, ** pole_datum;
	for (int i = 0;; i) {
		scanf("%c", &input);
		if (input == 'v') {
			function_v(&subor, &file);
		}
		if (input == 'o') {
			function_o(&pole_datum);
		}
		if (input == 'n') {
			function_n(&subor, &file, &pole_meno, &pole_rodnecislo, &pole_diagnoza, &pole_vysetrenie, &pole_vysledok, &pole_datum);
		}
		else {
			continue;
		}
	}
	exit(1);
}