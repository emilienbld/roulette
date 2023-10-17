#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

class Carte {
public:
    string nom;
    int valeur;

    Carte(string nom, int valeur) : nom(nom), valeur(valeur) {}
};

class Deck {
private:
    vector<Carte> cartes;

public:
    Deck() {
        string noms[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As" };
        int valeurs[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

        for (int i = 0; i < 13; i++) {
            cartes.push_back(Carte(noms[i], valeurs[i]));
        }
    }

    void melanger() {
        srand(static_cast<unsigned>(time(0)));
        random_shuffle(cartes.begin(), cartes.end());
    }

    Carte tirer_carte() {
        Carte carte = cartes.back();
        cartes.pop_back();
        return carte;
    }
};

class Main {
private:
    vector<Carte> cartes;

public:
    void ajouter_carte(Carte carte) {
        cartes.push_back(carte);
    }

    int calculer_valeur() {
        int valeur = 0;
        int nombre_as = 0;
        for (const Carte& carte : cartes) {
            valeur += carte.valeur;
            if (carte.nom == "As") {
                nombre_as++;
            }
        }
        while (nombre_as > 0 && valeur > 21) {
            valeur -= 10;
            nombre_as--;
        }
        return valeur;
    }

    void afficher() {
        for (const Carte& carte : cartes) {
            cout << carte.nom << " ";
        }
    }
};

int main() {
    Deck deck;
    deck.melanger();

    Main main_joueur;
    Main main_croupier;

    main_joueur.ajouter_carte(deck.tirer_carte());
    main_croupier.ajouter_carte(deck.tirer_carte());
    main_joueur.ajouter_carte(deck.tirer_carte());
    main_croupier.ajouter_carte(deck.tirer_carte());

    cout << "Bienvenue au jeu de Blackjack !\n\n";

    while (true) {
        int valeur_main_joueur = main_joueur.calculer_valeur();
        int valeur_main_croupier = main_croupier.calculer_valeur();

        cout << "Votre main : ";
        main_joueur.afficher();
        cout << "(" << valeur_main_joueur << " points)\n";

        cout << "Main du croupier : ";
        main_croupier.afficher();
        cout << " X\n\n";

        if (valeur_main_joueur > 21) {
            cout << "Vous avez sauté (plus de 21 points). Le croupier gagne !\n";
            break;
        }

        char choix;
        cout << "Que voulez-vous faire ? (P pour passer, T pour tirer) : ";
        cin >> choix;

        if (choix == 'T' || choix == 't') {
            main_joueur.ajouter_carte(deck.tirer_carte());
        }
        else if (choix == 'P' || choix == 'p') {
            while (valeur_main_croupier < 17) {
                main_croupier.ajouter_carte(deck.tirer_carte());
                valeur_main_croupier = main_croupier.calculer_valeur();
            }

            cout << "Main du croupier : ";
            main_croupier.afficher();
            cout << "(" << valeur_main_croupier << " points)\n\n";

            if (valeur_main_croupier > 21 || valeur_main_joueur > valeur_main_croupier) {
                cout << "Vous gagnez !\n";
            }
            else if (valeur_main_joueur == valeur_main_croupier) {
                cout << "Égalité !\n";
            }
            else {
                cout << "Le croupier gagne !\n";
            }
            break;
        }
    }

    return 0;
}
