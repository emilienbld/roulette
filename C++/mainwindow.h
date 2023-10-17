#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class MainWindow;
}

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

    const std::vector<Carte>& obtenir_cartes_croupier() const {
        return cartes;
    }
};



class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tirerButton_clicked();
    void on_passerButton_clicked();

private:
    Ui::MainWindow *ui;
    Deck deck;
    Main main_joueur;
    Main main_croupier;

    void afficher_main_joueur();
    void afficher_main_croupier();
};

#endif // MAINWINDOW_H
