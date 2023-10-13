#include "Roulette.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

RouletteGame::RouletteGame() {
    for (int i = 0; i <= 36; i++) {
        numeros[i] = i;
    }
}

void RouletteGame::Start() {
    std::cout << "Jeu de Roulette de Casino." << std::endl;
}

int RouletteGame::numeroAleatoire(int max) {
    return rand() % max;
}

void RouletteGame::afficherCouleur(int numeroGagnant) {
    if (numeroGagnant == 0) {
        std::cout << "La couleur du numéro gagnant est : vert" << std::endl;
    }
    else if (numeroGagnant % 2 == 0) {
        std::cout << "La couleur du numéro gagnant est : rouge" << std::endl;
    }
    else {
        std::cout << "La couleur du numéro gagnant est : noir" << std::endl;
    }
}

void RouletteGame::afficherParite(int numero) {
    if (numero == 0) {
        std::cout << "La parité du numéro gagnant est : neutre" << std::endl;
    }
    else if (numero % 2 == 0) {
        std::cout << "La parité du numéro gagnant est : pair" << std::endl;
    }
    else {
        std::cout << "La parité du numéro gagnant est : impair" << std::endl;
    }
}

void RouletteGame::afficherPassManque(int numero) {
    if (numero == 0) {
        std::cout << "Le numéro gagnant est : nul" << std::endl;
    }
    else if (numero >= 1 && numero <= 18) {
        std::cout << "Le numéro gagnant est du côté : pass" << std::endl;
    }
    else if (numero >= 19 && numero <= 36) {
        std::cout << "Le numéro gagnant est du côté : manque" << std::endl;
    }
}

void RouletteGame::afficherPlage(int numero) {
    if (numero >= 1 && numero <= 12) {
        std::cout << "Plage du numéro gagnant : 1ers 12" << std::endl;
    }
    else if (numero >= 13 and numero <= 24) {
        std::cout << "Plage du numéro gagnant : 2nds 12" << std::endl;
    }
    else if (numero >= 25 && numero <= 36) {
        std::cout << "Plage du numéro gagnant : 3èmes 12" << std::endl;
    }
}

void RouletteGame::gain(int paris[], int mises[], int nbParis, int numeroChoisi) {
    for (int i = 0; i < nbParis; i++) {
        if (paris[i] >= 0 && paris[i] <= 36) {
            if (paris[i] == numeroChoisi) {
                std::cout << "Pari sur le numéro " << paris[i] << ", mise : " << mises[i] << ", gain : " << mises[i] * 36 << std::endl;
            }
        }
        else if (paris[i] == 37) {
            if (numeroChoisi % 2 == 0) {
                std::cout << "Pari sur la parité (pair), mise : " << mises[i] << ", gain : " << mises[i] * 2 << std::endl;
            }
        }
        else if (paris[i] == 38) {
            if (numeroChoisi % 2 != 0) {
                std::cout << "Pari sur la parité (impair), mise : " << mises[i] << ", gain : " << mises[i] * 2 << std::endl;
            }
        }
        else if (paris[i] == 39) {
            if (numeroChoisi >= 1 && numeroChoisi <= 18) {
                std::cout << "Pari sur le côté (pass), mise : " << mises[i] << ", gain : " << mises[i] * 2 << std::endl;
            }
        }
        else if (paris[i] == 40) {
            if (numeroChoisi >= 19 && numeroChoisi <= 36) {
                std::cout << "Pari sur le côté (manque), mise : " << mises[i] << ", gain : " << mises[i] * 2 << std::endl;
            }
        }
        else if (paris[i] == 41) {
            if (numeroChoisi >= 1 && numeroChoisi <= 12) {
                std::cout << "Pari sur la plage (1ers 12), mise : " << mises[i] << ", gain : " << mises[i] * 3 << std::endl;
            }
        }
        else if (paris[i] == 42) {
            if (numeroChoisi >= 13 && numeroChoisi <= 24) {
                std::cout << "Pari sur la plage (2nds 12), mise : " << mises[i] << ", gain : " << mises[i] * 3 << std::endl;
            }
        }
        else if (paris[i] == 43) {
            if (numeroChoisi >= 25 && numeroChoisi <= 36) {
                std::cout << "Pari sur la plage (3èmes 12), mise : " << mises[i] << ", gain : " << mises[i] * 3 << std::endl;
            }
        }
        else if (paris[i] == 44) {
            if ((numeroChoisi >= 1 && numeroChoisi <= 10) || (numeroChoisi >= 19 && numeroChoisi <= 28)) {
                std::cout << "Pari sur la couleur rouge, mise : " << mises[i] << ", gain : " << mises[i] * 2 << std::endl;
            }
        }
        else if (paris[i] == 45) {
            if ((numeroChoisi >= 11 && numeroChoisi <= 18) || (numeroChoisi >= 29 && numeroChoisi <= 36)) {
                std::cout << "Pari sur la couleur noire, mise : " << mises[i] << ", gain : " << mises[i] * 2 << std::endl;
            }
        }
    }
}

void RouletteGame::Roulette() {
    srand(time(0));

    int nbParis;
    std::cout << "Combien de paris souhaitez-vous faire ? ";
    std::cin >> nbParis;

    int paris[100];
    int mises[100];

    for (int i = 0; i < nbParis; i++) {
        std::cout << "Pari " << i + 1 << " : Pour un numéro de 0 à 36, pair (37), impair (38), pass (39), manque (40), 1ers 12 (41), 2nds 12 (42), 3èmes 12 (43), rouge (44), noir (45) : ";
        std::cin >> paris[i];

        if (paris[i] < 0 || (paris[i] > 36 && paris[i] < 37) || (paris[i] > 45)) {
            std::cout << "Pari invalide. Choisissez un numéro entre 0 et 36, ou [37] pour pair, [38] pour impair, [39] pour pass, [40] pour manque, [41] pour 1ers 12, [42] pour 2nds 12, [43] pour 3èmes 12, rouge [44], noir [45]." << std::endl;
            i--;
            continue;
        }

        std::cout << "Entrez la mise correspondante : ";
        std::cin >> mises[i];
    }

    int numeroGagnant = numeroAleatoire(37);
    std::cout << "Rien ne va plus..." << std::endl;
    int numeroChoisi = numeros[numeroGagnant];
    std::cout << "Le numéro gagnant est : " << numeroChoisi << std::endl;
    afficherParite(numeroChoisi);
    afficherCouleur(numeroChoisi);
}

void RouletteGame::Menu() {
    enum MenuOptions {
        Jouer = 1,
        Quitter
    };

    std::cout << "\nQue voulez-vous faire ? Jouer (1) ou Quitter (2) : ";
    int action;
    std::cin >> action;

    switch (action) {
    case Jouer:
        while (true) {
            Roulette();
            int choix;
            std::cout << "Voulez-vous refaire une partie ? Jouer (1) ou Quitter (2) : ";
            std::cin >> choix;
            system("cls");
            if (choix == 2) {
                break;
            }
        }
        break;
    case Quitter:
        End();
        break;
    default:
        break;
    }
}

void RouletteGame::End() {
    std::cout << "Merci d'avoir joué à la Roulette de Casino. Au revoir !" << std::endl;
    exit(0);
}
