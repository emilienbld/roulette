#ifndef ROULETTE_H
#define ROULETTE_H

class RouletteGame {
public:
    RouletteGame();
    void Start();
    void Menu();
    void End();
    void Roulette();

private:
    int numeroAleatoire(int max);
    void afficherCouleur(int numeroChoisi);
    void afficherParite(int numero);
    void afficherPassManque(int numero);
    void afficherPlage(int numero);
    void gain(int paris[], int mises[], int nbParis, int numeroChoisi);

private:
    int numeros[37];
};

#endif
