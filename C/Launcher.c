#define _CRT_SECURE_NO_WARNINGS
#include "Launcher.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// D�finition des constantes pour les types de paris
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

//Initialisation � 0 de la structure des statiqtiques
struct statistique gameStats = { 0,0 };

// Fonction pour l'incr�mentation du nombre de parties
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

// Fonction pour g�n�rer un nombre al�atoire en choisissant le maximum
int numeroAleatoire(int max) {
	return rand() % max;
}

//Fonction pour l'affichage de la couleur du num�ro gagnant
void afficherCouleur(int numeroGagnant) {
	const char* couleur = (numeroGagnant == 0) ? "Vert" : ((numeroGagnant % 2 == 0) ? "Rouge" : "Noir");
	printf("La couleur du numero gagnant est : %s\n", couleur);
}

//Fonction pour l'affichage de la parit� du num�ro gagnant
void afficherParite(int numero) {
	const char* parite = (numero == 0) ? "Neutre" : ((numero % 2 == 0) ? "Pair" : "Impair");
	printf("La parite du numero gagnant est : %s\n", parite);
}

//Fonction pour l'affichage du c�t� Pass ou Manque du num�ro gagnant
void afficherPassManque(int numero) {
	const char* PassManque = (numero == 0) ? "Nul" : ((numero >= 1 && numero <= 18) ? "Pass" : "Manque");
	printf("Le numero gagnant est du cote : %s\n", PassManque);
}

//Fonction pour l'affichage de la "plage" du num�ro gagnant
void afficherPlage(int numero) {
	const char* plage = (numero >= 1 && numero <= 12) ? "1ers 12" : ((numero >= 13 && numero <= 24) ? "2nds 12" : "3emes 12");
	printf("Plage du numero gagnant : %s\n", plage);
}

// Structure pour les types de paris et les coefficients correspondants
struct TypePari typesParis[] = {
	{0, 36, "Numero", 0, 0},
	{PARITE_PAIR, 2, "Parite (pair)", 1, 0},
	{PARITE_IMPAIR, 2, "Parite (impair)", 1, 1},
	{COTE_PASS, 2, "C�te (pass)", 2, 18},
	{COTE_MANQUE, 2, "C�te (manque)", 2, 36},
	{PLAGE_1ER_12, 3, "Plage (1ers 12)", 3, 12},
	{PLAGE_2ND_12, 3, "Plage (2nds 12)", 3, 24},
	{PLAGE_3EME_12, 3, "Plage (3emes 12)", 3, 36},
	{COULEUR_ROUGE, 2, "Couleur (rouge)", 4, 0},
	{COULEUR_NOIR, 2, "Couleur (noir)", 4, 1}
};

//Fonction pour afficher les paris gagnants
void gain(int paris[], int mises[], int nbParis, int numeroChoisi, int numeroGagnant) {
	for (int i = 0; i < nbParis; i++) {
		int gainPartie = 0;
		for (int j = 0; j < sizeof(typesParis) / sizeof(typesParis[0]); j++) {
			if (paris[i] == typesParis[j].code) {
				int condition = typesParis[j].condition;
				int valeur = typesParis[j].valeur;

				switch (condition) {
				case 0: // Condition pour "Numero" (toujours vrai)
					gainPartie = mises[i] * typesParis[j].coefficient;
					break;
				case 1: // Condition pour la parit�
					if ((numeroChoisi % 2 == valeur))
						gainPartie = mises[i] * typesParis[j].coefficient;
					break;
				case 2: // Condition pour la c�te
					if ((numeroChoisi >= 1 && numeroChoisi <= valeur))
						gainPartie = mises[i] * typesParis[j].coefficient;
					break;
				case 3: // Condition pour la plage
					if ((numeroChoisi >= 1 && numeroChoisi <= valeur))
						gainPartie = mises[i] * typesParis[j].coefficient;
					break;
				case 4: // Condition pour la couleur
					if ((numeroGagnant % 2 == valeur))
						gainPartie = mises[i] * typesParis[j].coefficient;
					break;
				}

				if (gainPartie > 0) {
					gameStats.gainTotal += gainPartie;
					printf("Pari sur %s, mise : %d, gain : %d\n", typesParis[j].description, mises[i], gainPartie);
				}
				break;
			}
		}
	}
}

void Roulette() {
	srand(time(0));

	//Tableau des num�ros de la roulette dans l'ordre
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
			i--; // R�p�ter la saisie du pari pour cette it�ration.
			continue;
		}

		printf("Entrez la mise correspondante : ");
		scanf("%d", &mises[i]);
	}

	int numeroGagnant = numeroAleatoire(37); // G�n�re un num�ro al�atoire entre 0 et 36
	int numeroChoisi = numeros[numeroGagnant]; // Le num�ro en fonction de son rang tir� au sort dans le tableau 
	printf("\nRien ne va plus...\n"); // Phrase dite quand la roue tourne
	printf("Le numero gagnant est : %d\n", numeroChoisi); // Affichage du num�ro gagnant

	//Appel des fonctions pr�c�dentes
	afficherParite(numeroChoisi);
	afficherPassManque(numeroChoisi);
	afficherPlage(numeroChoisi);
	afficherCouleur(numeroChoisi);
	gain(paris, mises, nbParis, numeroChoisi, numeroGagnant);
	resume();
}
