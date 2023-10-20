#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>
#include <ctime>
#include <algorithm>
#include <QMessageBox>


///////////////////////////////////////////////////////////////////////////////////////////////////


// Définition de constantes pour les couleurs et la taille de la police
const QString COULEUR_FOND = "#B21A33";
const QString COULEUR_BOUTON = "#E8E1E1";
const QString COULEUR_TEXTE = "white";
const int TAILLE_POLICE = 16;


///////////////////////////////////////////////////////////////////////////////////////////////////


// Initialisation du jeu de cartes
Deck::Deck() {
    QString noms[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As"};
    int valeurs[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            cartes.push_back(Carte(noms[i], valeurs[i]));
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Mélange les cartes en utilisant le temps comme graine
void Deck::melanger() {
    srand(static_cast<unsigned>(time(0)));
    std::random_shuffle(cartes.begin(), cartes.end());
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Tire une carte du dessus du jeu
Carte Deck::tirer_carte() {
    Carte carte = cartes.back();
    cartes.pop_back();
    return carte;
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Ajoute une carte à la main du joueur ou du croupier
void Main::ajouter_carte(Carte carte) {
    cartes.push_back(carte);
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Calcule la valeur totale des cartes dans la main
int Main::calculer_valeur() {
    int valeur = 0;
    int nombre_as = 0;
    for (const Carte& carte : cartes) {
        valeur += carte.valeur;
        if (carte.nom == "As") {
            nombre_as++;
        }
    }
    // Réduit la valeur si un As provoque un dépassement de 21
    while (nombre_as > 0 && valeur > 21) {
        valeur -= 10;
        nombre_as--;
    }
    return valeur;
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Initialisation de l'interface utilisateur et du jeu
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setStyleSheet("background-color: " + COULEUR_FOND);
    ui->tirerButton->setStyleSheet("border-radius: 50px; background-color: " + COULEUR_BOUTON);
    ui->passerButton->setStyleSheet("border-radius: 50px; background-color: " + COULEUR_BOUTON);

    // Initialisation des compteurs (stats)
    nombreDeVictoires = 0;
    nombreDePertes = 0;

    // Création des étiquettes stats
    labelVictoires = new QLabel("Victoires : 0", this);
    labelPertes = new QLabel("Pertes : 0", this);

    labelVictoires->setStyleSheet("color: white;");
    labelPertes->setStyleSheet("color: white;");

    // Positionnement des labels
    labelVictoires->move(20, 20);
    labelPertes->move(20, 50);

    initialiserPartie();

    // Personnalisation du tapis, boutons et labels
    QWidget* tapis = this->findChild<QWidget*>("tapis");
    if (tapis) {
        tapis->setStyleSheet("background-color: #085B12; border-radius: 30px;");
        tapis->lower();
    }
    setLabelStyles(ui->maMain);
    setLabelStyles(ui->saMain);
    setLabelStyles(ui->mainJoueurLabel);
    setLabelStyles(ui->mainCroupierLabel);
    ui->mainJoueurLabel->setStyleSheet("background-color: white; color: black; font-size: " + QString::number(TAILLE_POLICE) + "px; border-radius: 30px;");
    ui->mainCroupierLabel->setStyleSheet("background-color: white; color: black; font-size: " + QString::number(TAILLE_POLICE) + "px; border-radius: 30px;");
    setLabelStyles(ui->blackjack);
    ui->blackjack->setStyleSheet("background-color: #D6DF15; color: black; font-size: " + QString::number(TAILLE_POLICE) + "px; border-radius: 10px;");
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Configure le style des étiquettes de la main
void MainWindow::setLabelStyles(QLabel* label) {
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("background-color: #66626B; color: " + COULEUR_TEXTE + "; font-size: " + QString::number(TAILLE_POLICE) + "px; border-radius: 20px;");
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Initialise une nouvelle partie en mélangeant le jeu et distribuant des cartes
void MainWindow::initialiserPartie() {
    deck.melanger();
    main_joueur = Main();
    main_croupier = Main();
    main_joueur.ajouter_carte(deck.tirer_carte());
    main_croupier.ajouter_carte(deck.tirer_carte());
    main_joueur.ajouter_carte(deck.tirer_carte());
    afficher_main_joueur();
    afficher_main_croupier();
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Destructeur
MainWindow::~MainWindow() {
    delete ui;
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Gère le clic sur le bouton "Tirer"
void MainWindow::on_tirerButton_clicked() {
    main_joueur.ajouter_carte(deck.tirer_carte());

    // Afficher les cartes du joueur
    afficher_main_joueur();

    int valeur_main_joueur = main_joueur.calculer_valeur();
    if (valeur_main_joueur > 21) {
        QString resultat = "Vous avez sauté (plus de 21 points). Le croupier gagne !";
            boiteMsg(resultat);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Gère le clic sur le bouton "Passer"
void MainWindow::on_passerButton_clicked() {
    while (main_croupier.calculer_valeur() < 17) {
        main_croupier.ajouter_carte(deck.tirer_carte());
    }
    afficher_main_croupier();
    int valeur_main_joueur = main_joueur.calculer_valeur();
    int valeur_main_croupier = main_croupier.calculer_valeur();
    QString resultat;
    if (valeur_main_croupier > 21 || valeur_main_joueur > valeur_main_croupier) {
        resultat = "Vous gagnez !";
    } else if (valeur_main_joueur == valeur_main_croupier) {
        resultat = "Égalité !";
    } else {
        resultat = "Le croupier gagne !";
    }
    boiteMsg(resultat);
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Affiche une boîte de dialogue avec le résultat et une option de rejouer ou quitter
void MainWindow::boiteMsg(const QString& resultat) {
    QMessageBox messageBox;
    messageBox.setText(resultat);
    messageBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    messageBox.setDefaultButton(QMessageBox::Retry);
    int choice = messageBox.exec();
    if (choice == QMessageBox::Retry) {
        initialiserPartie();
    } else {
        this->close();
    }

    // Mettre à jour les compteurs
    if (resultat == "Vous gagnez !") {
        nombreDeVictoires++;
    } else {
        nombreDePertes++;
    }

    // Mettre à jour l'affichage des compteurs
    labelVictoires->setText("Victoires : " + QString::number(nombreDeVictoires));
    labelPertes->setText("Pertes : " + QString::number(nombreDePertes));
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Affiche la main du joueur et son total
void MainWindow::afficher_main_joueur() {
    const std::vector<Carte>& cartes_joueur = main_joueur.obtenir_cartes();
    QString main_joueur_str = "";
    for (const Carte& carte : cartes_joueur) {
        main_joueur_str += carte.nom + " ";
    }
    ui->mainJoueurLabel->setText(main_joueur_str + "(" + QString::number(main_joueur.calculer_valeur()) + " points)");
}


///////////////////////////////////////////////////////////////////////////////////////////////////


// Affiche la main du croupier et son total
void MainWindow::afficher_main_croupier() {
    const std::vector<Carte>& cartes_croupier = main_croupier.obtenir_cartes();
    QString main_croupier_str = "";
    for (const Carte& carte : cartes_croupier) {
        main_croupier_str += carte.nom + " ";
    }
    ui->mainCroupierLabel->setText(main_croupier_str + "(" + QString::number(main_croupier.calculer_valeur()) + " points)");
}
