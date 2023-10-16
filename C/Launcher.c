#define _CRT_SECURE_NO_WARNINGS
#include "Launcher.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Définition des constantes pour les types de paris
#define NUMERO 0
#define PARITE_PAIR 37
#define PARITE_IMPAIR 38
#define COTE_PASS 39
#define COTE_MANQUE 40
#define PLAGE_1ER_12 41
#define PLAGE_2ND_12 42
#define PLAGE_3EME_12 43
#define COULEUR_ROUGE 44
#define COULEUR_NOIR 45

void Start() {
	printf("Bonjour et bienvenu dans le jeu de la Roulette de Casino.\n");
};

void Menu() {
	enum Jouer {
		Jouer = 1,
		Quiter
	};
	const char* ChoixJouer = "\nQue voulez vous faire ? Jouer tapez [1] Autre touche pour Quitter : ";
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

//Fonction le joueur veux quiter le jeu
void End() {
	printf("Au revoir et a bientot.\nVoici vos statistiques :\n");
	//resume();
	exit(0);
};

//Initialisation à 0 de la structure des statiqtiques
struct statistique gameStats = { 0,0 };

// Fonction pour l'incrémentation du nombre de parties
int IncrementGame(int* Parties) {
	++(*Parties);
	return *Parties;
}

//Fontion pour l'affichage des statistiques
void resume() {
	IncrementGame(&gameStats.nbPartie);
	printf("\nVous avez joue %d parties\n", gameStats.nbPartie);
	printf("Gain total : %d\n", gameStats.gainTotal);
}

// Fonction pour générer un nombre aléatoire en choisissant le maximum
int numeroAleatoire(int max) {
	return rand() % max;
}

//Fonction pour l'affichage de la couleur du numéro gagnant
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

//Fonction pour l'affichage de la parité du numéro gagnant
void afficherParite(int numero) {
	//const char* parite = "";
	//if (numero == 0) {
	//	parite = "Neutre";
	//}
	//else if (numero % 2 == 0) {
	//	parite = "Pair";
	//}
	//else {
	//	parite = "Impair";
	//}
	//printf("La parite du numero gagnant est : %s\n", parite);
	const char* parite = (numero == 0) ? "Neutre" : ((numero % 2 == 0) ? "Pair" : "Impair");
	printf("La parité du numéro gagnant est : %s\n", parite);
}

//Fonction pour l'affichage du côté Pass ou Manque du numéro gagnant
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

//Fonction pour l'affichage de la "plage" du numéro gagnant
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

//Fonction pour le calcule des gains en fonction de chaque paris
//void gain(int paris[], int mises[], int nbParis, int numeroChoisi) {
//	for (int i = 0; i < nbParis; i++) {
//		int gainPartie = 0; // Initialisez le gain de cette partie à zéro
//		if (paris[i] >= 0 && paris[i] <= 36) {
//			if (paris[i] == numeroChoisi) {
//				gainPartie = mises[i] * 36;
//				gameStats.gainTotal += gainPartie; // Pour les statiqtique du joueur (gain total)
//				printf("Pari sur le numero %d, mise : %d, gain : %d\n", paris[i], mises[i], gainPartie);
//			}
//		}
//		else if (paris[i] == 37) { // Pari sur la parité (pair)
//			if (numeroChoisi % 2 == 0) {
//				gainPartie = mises[i] * 2;
//				gameStats.gainTotal += gainPartie; // Pour les statiqtique du joueur (gain total)
//				printf("Pari sur la parite (pair), mise : %d, gain : %d\n", mises[i], gainPartie);
//			}
//		}
//		else if (paris[i] == 38) { // Pari sur la parité (impair)
//			if (numeroChoisi % 2 != 0) {
//				gainPartie = mises[i] * 2;
//				gameStats.gainTotal += gainPartie; // Pour les statiqtique du joueur (gain total)
//				printf("Pari sur la parite (impair), mise : %d, gain : %d\n", mises[i], gainPartie);
//			}
//		}
//		else if (paris[i] == 39) { // Pari sur le côté (pass)
//			if (numeroChoisi >= 1 && numeroChoisi <= 18) {
//				gainPartie = mises[i] * 2;
//				gameStats.gainTotal += gainPartie; // Pour les statiqtique du joueur (gain total)
//				printf("Pari sur le cote (pass), mise : %d, gain : %d\n", mises[i], gainPartie);
//			}
//		}
//		else if (paris[i] == 40) { // Pari sur le côté (manque)
//			if (numeroChoisi >= 19 && numeroChoisi <= 36) {
//				gainPartie = mises[i] * 2;
//				gameStats.gainTotal += gainPartie; // Pour les statiqtique du joueur (gain total)
//				printf("Pari sur le cote (manque), mise : %d, gain : %d\n", mises[i], gainPartie);
//			}
//		}
//		else if (paris[i] == 41) { // Pari sur la plage (1 ers 12)
//			if (numeroChoisi >= 1 && numeroChoisi <= 12) {
//				gainPartie = mises[i] * 3;
//				gameStats.gainTotal += gainPartie; // Pour les statiqtique du joueur (gain total)
//				printf("Pari sur la plage (1 ers 12), mise : %d, gain : %d\n", mises[i], gainPartie);
//			}
//		}
//		else if (paris[i] == 42) { // Pari sur la plage (2 nds 12)
//			if (numeroChoisi >= 13 && numeroChoisi <= 24) {
//				gainPartie = mises[i] * 3;
//				gameStats.gainTotal += gainPartie; // Pour les statiqtique du joueur (gain total)
//				printf("Pari sur la plage (2 nds 12), mise : %d, gain : %d\n", mises[i], gainPartie);
//			}
//		}
//		else if (paris[i] == 43) { // Pari sur la plage (3 emes 12)
//			if (numeroChoisi >= 25 && numeroChoisi <= 36) {
//				gainPartie = mises[i] * 3;
//				gameStats.gainTotal += gainPartie; // Pour les statiqtique du joueur (gain total)
//				printf("Pari sur la plage (3 emes 12), mise : %d, gain : %d\n", mises[i], gainPartie);
//			}
//		}
//		else if (paris[i] == 44) { // Pari sur la couleur rouge
//			if (numeroChoisi >= 1 && numeroChoisi <= 10 || numeroChoisi >= 19 && numeroChoisi <= 28) {
//				gainPartie = mises[i] * 2;
//				gameStats.gainTotal += gainPartie; // Pour les statiqtique du joueur (gain total)
//				printf("Pari sur la couleur rouge, mise : %d, gain : %d\n", mises[i], gainPartie);
//			}
//		}
//		else if (paris[i] == 45) { // Pari sur la couleur noire
//			if (numeroChoisi >= 11 && numeroChoisi <= 18 || numeroChoisi >= 29 && numeroChoisi <= 36) {
//				gainPartie = mises[i] * 2;
//				gameStats.gainTotal += gainPartie; // Pour les statiqtique du joueur (gain total)
//				printf("Pari sur la couleur noire, mise : %d, gain : %d\n", mises[i], gainPartie);
//			}
//		}
//	}
//}






struct TypePari typesParis[] = {
	{0, 36, "Numéro"},
	{PARITE_PAIR, 2, "Parité (pair)"},
	{PARITE_IMPAIR, 2, "Parité (impair)"},
	{COTE_PASS, 2, "Côté (pass)"},
	{COTE_MANQUE, 2, "Côté (manque)"},
	{PLAGE_1ER_12, 3, "Plage (1ers 12)"},
	{PLAGE_2ND_12, 3, "Plage (2nds 12)"},
	{PLAGE_3EME_12, 3, "Plage (3èmes 12)"},
	{COULEUR_ROUGE, 2, "Couleur (rouge)"},
	{COULEUR_NOIR, 2, "Couleur (noir)"}
};

void gain(int paris[], int mises[], int nbParis, int numeroChoisi, int numeroGagnant) {
	for (int i = 0; i < nbParis; i++) {
		int gainPartie = 0;
		for (int j = 0; j < sizeof(typesParis) / sizeof(typesParis[0]); j++) {
			if (paris[i] == typesParis[j].code) {
				if (paris[i] == 0 || (paris[i] == PARITE_PAIR && numeroChoisi % 2 == 0) ||
					(paris[i] == PARITE_IMPAIR && numeroChoisi % 2 != 0) ||
					(paris[i] == COTE_PASS && numeroChoisi >= 1 && numeroChoisi <= 18) ||
					(paris[i] == COTE_MANQUE && numeroChoisi >= 19 && numeroChoisi <= 36) ||
					(paris[i] == PLAGE_1ER_12 && numeroChoisi >= 1 && numeroChoisi <= 12) ||
					(paris[i] == PLAGE_2ND_12 && numeroChoisi >= 13 && numeroChoisi <= 24) ||
					(paris[i] == PLAGE_3EME_12 && numeroChoisi >= 25 && numeroChoisi <= 36) ||
					(paris[i] == COULEUR_ROUGE && numeroGagnant % 2 == 0) ||
					(paris[i] == COULEUR_NOIR && numeroGagnant % 2 != 0)) {
					gainPartie = mises[i] * typesParis[j].coefficient;
						gameStats.gainTotal += gainPartie; //Statiqtique des gains total du joueurs
						printf("Pari sur %s, mise : %d, gain : %d\n", typesParis[j].description, mises[i], gainPartie);
				}
				break;
			}
		}
	}
}













void Roulette() {
	srand(time(0));

	//Tableau des numéros de la roulette dans l'ordre
	int numeros[37] = {
		0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26
	};

	//Choix du nombre de pari dans cette partie
	int nbParis;
	printf("\nCombien de paris souhaitez-vous faire ? ");
	scanf("%d", &nbParis);

	int paris[100];
	int mises[100];
	int totalDesMises = 0;
	int totalDesGains = 0;

	//Boucle pour parier en mettant le type de parie et sa mise
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
	int numeroChoisi = numeros[numeroGagnant]; // Le numéro en fonction de son rang tiré au sort dans le tableau 
	printf("\nRien ne va plus...\n"); // Phrase dite quand la roue tourne
	printf("Le numero gagnant est : %d\n", numeroChoisi); // Affichage du numéro gagnant

	//Appel des fonctions précédentes
	afficherParite(numeroChoisi);
	afficherPassManque(numeroChoisi);
	afficherPlage(numeroChoisi);
	afficherCouleur(numeroChoisi);
	gain(paris, mises, nbParis, numeroChoisi, numeroGagnant);
	resume();
}
