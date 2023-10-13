#define _CRT_SECURE_NO_WARNINGS
#include "Launcher.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Start() {
	printf("Jeu de Roulette de Casino.\n");
};

void Menu() {
	enum Jouer {
		Jouer = 1,
		Quiter
	};

	const char* ChoixJouer = "\nQue voulez vous faire ? Jouer tapez [1] Quiter tapez [2] \n";

	printf (ChoixJouer);
	int action;
	scanf_s("%d", &action);

	enum MenuButtons MonMenuBoutons = action;

	switch (MonMenuBoutons) {
	case Jouer:
		while (1) {
			Roulette();
			int choix;
			printf(ChoixJouer);
			scanf_s("%d", &choix);
			system("cls");
			if (choix == 2) {
				break;
			}
		}
		break;
	case Quiter:
		End();
	default:
		break;
	};
};

void End() {
	exit(0);
};

int numeroAleatoire(int max) {
	return rand() % max;
}

void afficherCouleur(int numeroGagnant) {
	const char* couleur = "";
	if (numeroGagnant == 0) {
		couleur = "Vert";
	}
	else if (numeroGagnant % 2 == 0) {
		couleur = "Rouge";
	}
	else {
		couleur = "Noir";
	}
	printf("La couleur du numero gagnant est : %s\n", couleur);
}


void afficherParite(int numero) {
	const char* parite = "";
	if (numero == 0) {
		parite = "Neutre";
	}
	else if (numero % 2 == 0) {
		parite = "Pair";
	}
	else {
		parite = "Impair";
	}
	printf("La parite du numero gagnant est : %s\n", parite);
}

void afficherPassManque(int numero) {
	const char* PassManque = "";
	if (numero == 0) {
		PassManque = "Nul";
	}
	else if (numero >= 1 && numero <= 18) {
		PassManque = "Pass";
	}
	else if (numero >= 19 && numero <= 36) {
		PassManque = "Manque";
	}
	printf("Le numero gagnant est du cote : %s\n", PassManque);
}

void afficherPlage(int numero) {
	const char* plage = "";
	if (numero >= 1 && numero <= 12) {
		plage = "1 ers 12";
	}
	else if (numero >= 13 && numero <= 24) {
		plage = "2 nds 12";
	}
	else if (numero >= 25 && numero <= 36) {
		plage = "3 emes 12";
	}
	printf("Plage du numero gagnant : %s\n", plage);

}

void gain(int paris[], int mises[], int nbParis, int numeroChoisi) {
	for (int i = 0; i < nbParis; i++) {
		if (paris[i] >= 0 && paris[i] <= 36) {
			if (paris[i] == numeroChoisi) {
				printf("Pari sur le numero %d, mise : %d, gain : %d\n", paris[i], mises[i], mises[i] * 36);
			}
		}
		else if (paris[i] == 37) { // Pari sur la parité (pair)
			if (numeroChoisi % 2 == 0) {
				printf("Pari sur la parite (pair), mise : %d, gain : %d\n", mises[i], mises[i] * 2);
			}
		}
		else if (paris[i] == 38) { // Pari sur la parité (impair)
			if (numeroChoisi % 2 != 0) {
				printf("Pari sur la parite (impair), mise : %d, gain : %d\n", mises[i], mises[i] * 2);
			}
		}
		else if (paris[i] == 39) { // Pari sur le côté (pass)
			if (numeroChoisi >= 1 && numeroChoisi <= 18) {
				printf("Pari sur le cote (pass), mise : %d, gain : %d\n", mises[i], mises[i] * 2);
			}
		}
		else if (paris[i] == 40) { // Pari sur le côté (manque)
			if (numeroChoisi >= 19 && numeroChoisi <= 36) {
				printf("Pari sur le cote (manque), mise : %d, gain : %d\n", mises[i], mises[i] * 2);
			}
		}
		else if (paris[i] == 41) { // Pari sur la plage (1 ers 12)
			if (numeroChoisi >= 1 && numeroChoisi <= 12) {
				printf("Pari sur la plage (1 ers 12), mise : %d, gain : %d\n", mises[i], mises[i] * 3);
			}
		}
		else if (paris[i] == 42) { // Pari sur la plage (2 nds 12)
			if (numeroChoisi >= 13 && numeroChoisi <= 24) {
				printf("Pari sur la plage (2 nds 12), mise : %d, gain : %d\n", mises[i], mises[i] * 3);
			}
		}
		else if (paris[i] == 43) { // Pari sur la plage (3 emes 12)
			if (numeroChoisi >= 25 && numeroChoisi <= 36) {
				printf("Pari sur la plage (3 emes 12), mise : %d, gain : %d\n", mises[i], mises[i] * 3);
			}
		}
		else if (paris[i] == 44) { // Pari sur la couleur rouge
			if (numeroChoisi >= 1 && numeroChoisi <= 10 || numeroChoisi >= 19 && numeroChoisi <= 28) {
				printf("Pari sur la couleur rouge, mise : %d, gain : %d\n", mises[i], mises[i] * 2);
			}
		}
		else if (paris[i] == 45) { // Pari sur la couleur noire
			if (numeroChoisi >= 11 && numeroChoisi <= 18 || numeroChoisi >= 29 && numeroChoisi <= 36) {
				printf("Pari sur la couleur noire, mise : %d, gain : %d\n", mises[i], mises[i] * 2);
			}
		}
	}
}

void Roulette() {
	srand(time(0));

	int numeros[37] = {
		0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26
	};

	int nbParis;
	printf("\nCombien de paris souhaitez-vous faire ? ");
	scanf("%d", &nbParis);

	int paris[100];
	int mises[100];

	for (int i = 0; i < nbParis; i++) {
		printf("Pari %d : Pour un nombre de 0 a 36 [0-36], pair [37] impair [38], pass [39] manque[40], 1 ers 12 [41], 2 nds 12 [42], 3 emes 12 [43], rouge [44], noir [45] : ", i + 1);
		scanf("%d", &paris[i]);

		if (paris[i] < 0 || (paris[i] > 36 && paris[i] < 37) || (paris[i] > 45)) {
			printf("Pari invalide. Choisissez un numero entre 0 et 36, ou [37] pour pair, [38] pour impair, [39] pour pass, [40] pour manque, [41] pour 1 ers 12, [42] pour 2 nds 12, [43] pour 3 emes 12, rouge [44], noir [45].\n");
			i--; // Répéter la saisie du pari pour cette itération.
			continue;
		}

		printf("Entrez la mise correspondante : ");
		scanf("%d", &mises[i]);
	}

	int numeroGagnant = numeroAleatoire(37); // Génère un numéro aléatoire entre 0 et 36

	printf("Rien ne va plus...\n");
	int numeroChoisi = numeros[numeroGagnant];
	printf("Le numero gagnant est : %d\n", numeroChoisi);

	afficherParite(numeroChoisi);
	afficherPassManque(numeroChoisi);
	afficherPlage(numeroChoisi);
	afficherCouleur(numeroChoisi);
	gain(paris, mises, nbParis, numeroChoisi);
}