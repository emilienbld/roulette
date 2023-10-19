#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>
#include <ctime>
#include <algorithm>
#include <QMessageBox>

//#include <mutex>

//std::mutex mtx;

// Définition de constantes pour les couleurs et la taille de la police
const QString COULEUR_FOND = "#FF5733";
const QString COULEUR_BOUTON = "#E8E1E1";
const QString COULEUR_TEXTE = "white";
const int TAILLE_POLICE = 16;

Deck::Deck() {
    // Initialisation du jeu de cartes
    QString noms[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As"};
    int valeurs[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            cartes.push_back(Carte(noms[i], valeurs[i]));
        }
    }
}

void Deck::melanger() {
    // Mélange les cartes en utilisant le temps comme graine
    srand(static_cast<unsigned>(time(0)));
    std::random_shuffle(cartes.begin(), cartes.end());
}

Carte Deck::tirer_carte() {
    // Tire une carte du dessus du jeu
    Carte carte = cartes.back();
    cartes.pop_back();
    return carte;
}


//Carte Deck::tirer_carte() {
//    // Verrouiller le jeu de cartes
//    std::lock_guard<std::mutex> lock(mtx);

//    // Tirer une carte du dessus du jeu
//    Carte carte = cartes.back();
//    cartes.pop_back();

//    // Déverrouiller le jeu de cartes lorsque la carte est tirée
//    return carte;
//}



void Main::ajouter_carte(Carte carte) {
    // Ajoute une carte à la main du joueur ou du croupier
    cartes.push_back(carte);
}

int Main::calculer_valeur() {
    // Calcule la valeur totale des cartes dans la main
    int valeur = 0;
    int nombre_as = 0;
    for (const Carte& carte : cartes) {
        valeur += carte.valeur;
        if (carte.nom == "As") {
            nombre_as++;
        }
    }
    while (nombre_as > 0 && valeur > 21) {
        valeur -= 10; // Réduit la valeur si un As provoque un dépassement de 21
        nombre_as--;
    }
    return valeur;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // Initialisation de l'interface utilisateur et du jeu
    ui->setupUi(this);
    this->setStyleSheet("background-color: " + COULEUR_FOND);
    ui->tirerButton->setStyleSheet("border-radius: 50px; background-color: " + COULEUR_BOUTON);
    ui->passerButton->setStyleSheet("border-radius: 50px; background-color: " + COULEUR_BOUTON);

    connect(ui->tirerButton, SIGNAL(clicked()), this, SLOT(on_tirerButton_clicked()));
    connect(ui->passerButton, SIGNAL(clicked()), this, SLOT(on_passerButton_clicked()));
    initialiserPartie();

    // Personnalisation du tapis, boutons et lables
    QWidget* tapis = this->findChild<QWidget*>("tapis");
    if (tapis) {
        tapis->setStyleSheet("background-color: #38754A; border-radius: 30px;");
        tapis->lower();
    }
    setLabelStyles(ui->maMain);
    setLabelStyles(ui->saMain);
    setLabelStyles(ui->mainJoueurLabel);
    setLabelStyles(ui->mainCroupierLabel);
    ui->mainJoueurLabel->setStyleSheet("background-color: white; color: black; font-size: " + QString::number(TAILLE_POLICE) + "px; border-radius: 30px;");
    ui->mainCroupierLabel->setStyleSheet("background-color: white; color: black; font-size: " + QString::number(TAILLE_POLICE) + "px; border-radius: 30px;");

}

void MainWindow::setLabelStyles(QLabel* label) {
    // Configure le style des étiquettes de la main
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("background-color: #66626B; color: " + COULEUR_TEXTE + "; font-size: " + QString::number(TAILLE_POLICE) + "px; border-radius: 20px;");
}

void MainWindow::initialiserPartie() {
    // Initialise une nouvelle partie en mélangeant le jeu et distribuant des cartes
    deck.melanger();
    main_joueur = Main();
    main_croupier = Main();
    main_joueur.ajouter_carte(deck.tirer_carte());
    main_croupier.ajouter_carte(deck.tirer_carte());
    main_joueur.ajouter_carte(deck.tirer_carte());
    afficher_main_joueur();
    afficher_main_croupier();
}

MainWindow::~MainWindow() {
    // Destructeur
    delete ui;
}

void MainWindow::on_tirerButton_clicked() {
    // Gère le clic sur le bouton "Tirer"
    main_joueur.ajouter_carte(deck.tirer_carte());
    afficher_main_joueur();
    int valeur_main_joueur = main_joueur.calculer_valeur();
    if (valeur_main_joueur > 21) {
        QString resultat = "Vous avez sauté (plus de 21 points). Le croupier gagne !";
            boiteMsg(resultat);
    }
}

void MainWindow::on_passerButton_clicked() {
    // Gère le clic sur le bouton "Passer"
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

void MainWindow::boiteMsg(const QString& resultat) {
    // Affiche une boîte de dialogue avec le résultat et une option de rejouer ou quitter
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
}

void MainWindow::afficher_main_joueur() {
    // Affiche la main du joueur et sa valeur
    const std::vector<Carte>& cartes_joueur = main_joueur.obtenir_cartes();
    QString main_joueur_str = "";
    for (const Carte& carte : cartes_joueur) {
        main_joueur_str += carte.nom + " ";
    }
    ui->mainJoueurLabel->setText(main_joueur_str + "(" + QString::number(main_joueur.calculer_valeur()) + " points)");
}

void MainWindow::afficher_main_croupier() {
    // Affiche la main du croupier et sa valeur
    const std::vector<Carte>& cartes_croupier = main_croupier.obtenir_cartes();
    QString main_croupier_str = "";
    int valeur_croupier = 0;
    for (const Carte& carte : cartes_croupier) {
        main_croupier_str += carte.nom + " ";
        valeur_croupier += carte.valeur;
    }
    ui->mainCroupierLabel->setText(main_croupier_str + "(" + QString::number(valeur_croupier) + " points)");
}
