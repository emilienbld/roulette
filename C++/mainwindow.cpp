#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>
#include <ctime>
#include <algorithm>

Deck::Deck() {
    QString noms[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As"};
    int valeurs[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    for (int i = 0; i < 13; i++) {
        cartes.push_back(Carte(noms[i], valeurs[i]));
    }
}

void Deck::melanger() {
    srand(static_cast<unsigned>(time(0)));
    std::random_shuffle(cartes.begin(), cartes.end());
}

Carte Deck::tirer_carte() {
    Carte carte = cartes.back();
    cartes.pop_back();
    return carte;
}

void Main::ajouter_carte(Carte carte) {
    cartes.push_back(carte);
}

int Main::calculer_valeur() {
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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    deck.melanger();
    main_joueur.ajouter_carte(deck.tirer_carte());
    main_croupier.ajouter_carte(deck.tirer_carte());
    main_joueur.ajouter_carte(deck.tirer_carte());
    main_croupier.ajouter_carte(deck.tirer_carte());
    afficher_main_joueur();
    afficher_main_croupier();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_tirerButton_clicked() {
    main_joueur.ajouter_carte(deck.tirer_carte());
    afficher_main_joueur();
    int valeur_main_joueur = main_joueur.calculer_valeur();
    if (valeur_main_joueur > 21) {
        // Le joueur a sauté, gérer ici
        qDebug() << "Vous avez sauté (plus de 21 points). Le croupier gagne !";
    }
}

void MainWindow::on_passerButton_clicked() {
    while (main_croupier.calculer_valeur() < 17) {
        main_croupier.ajouter_carte(deck.tirer_carte());
    }
    afficher_main_croupier();
    int valeur_main_joueur = main_joueur.calculer_valeur();
    int valeur_main_croupier = main_croupier.calculer_valeur();
    if (valeur_main_croupier > 21 || valeur_main_joueur > valeur_main_croupier) {
        // Le joueur gagne, gérer ici
        qDebug() << "Vous gagnez !";
    } else if (valeur_main_joueur == valeur_main_croupier) {
        // Égalité, gérer ici
        qDebug() << "Égalité !";
    } else {
        // Le croupier gagne, gérer ici
        qDebug() << "Le croupier gagne !";
    }
}

void MainWindow::afficher_main_joueur() {
    const std::vector<Carte>& cartes_joueur = main_joueur.obtenir_cartes();
    QString main_joueur_str = "Votre main : ";
    for (const Carte& carte : cartes_joueur) {
        main_joueur_str += carte.nom + " ";
    }
    main_joueur_str += "(" + QString::number(main_joueur.calculer_valeur()) + " points)";
    ui->mainJoueurLabel->setText(main_joueur_str);
}


void MainWindow::afficher_main_croupier() {
    const std::vector<Carte>& cartes_croupier = main_croupier.obtenir_cartes_croupier();
    QString main_croupier_str = "Main du croupier : " + cartes_croupier[0].nom + " X";
    ui->mainCroupierLabel->setText(main_croupier_str);
}

