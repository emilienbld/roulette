#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QLabel>

class Carte {
public:
    QString nom;
    int valeur;

    Carte(QString nom, int valeur) : nom(nom), valeur(valeur) {}
};

class Deck {
private:
    std::vector<Carte> cartes;

public:
    Deck();

    void melanger();
    Carte tirer_carte();
};

class Main {
private:
    std::vector<Carte> cartes;

public:
    void ajouter_carte(Carte carte);
    int calculer_valeur();

    const std::vector<Carte>& obtenir_cartes() const {
        return cartes;
    }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void initialiserPartie();
    void on_tirerButton_clicked();
    void on_passerButton_clicked();

private:
    Ui::MainWindow *ui;
    Deck deck;
    Main main_joueur;
    Main main_croupier;
    int nombreDeVictoires;  // Ajout : compteur de victoires
    int nombreDePertes;     // Ajout : compteur de pertes

    QLabel* labelVictoires;  // Ajout : étiquette pour afficher le nombre de victoires
    QLabel* labelPertes;     // Ajout : étiquette pour afficher le nombre de pertes

    void setLabelStyles(QLabel* label);
    void boiteMsg(const QString& resultat);
    void afficher_main_joueur();
    void afficher_main_croupier();
};

#endif // MAINWINDOW_H
