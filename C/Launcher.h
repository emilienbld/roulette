#ifndef LAUNCHER_H
#define LAUNCHER_H

void Start();
void Menu();
void End();
int numeroAleatoire(int max);
void afficherCouleur(int numeroChoisi);
void afficherParite(int numero);
void afficherPassManque(int numero);
void afficherPlage(int numero);
void gain(int paris[], int mises[], int nbParis, int numeroChoisi, int numeroGagnant);
void Roulette();
void resume();
int IncrementGame(int* Parties);

// Structures pour les types de paris et les statistiques
struct statistique {
	int nbPartie;
	int gainTotal;
};

// Structures pour les gains
struct TypePari {
	int code;
	int coefficient;
	const char* description;
};

#endif