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
void gain(int paris[], int mises[], int nbParis, int numeroChoisi);
void Roulette();
void temp();
int IncrementGame(int* Parties);
struct statistique;


#endif