#ifndef JEU_H
#define JEU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Jeu
{
public:
    // constructeur
    Jeu();
    void run();

private:
    //attributs
    sf::RenderWindow m_fenetre; // notre fenetre de jeu
    sf::CircleShape m_sommet;
    std::vector<sf::CircleShape> tabCercle; // tableau dynamique de cercles

    // attributs temporaires (tests)
    sf::RectangleShape m_rect;
    sf::RectangleShape m_barre;
    sf::RectangleShape m_selection_button;
    bool effacerEcran;

    // méthodes
    void gerer_evenements();
    void dessiner();

    // constantes statiques
    static const int LONGUEUR_ECRAN = 800.;
    static const int LARGEUR_ECRAN = 600.;
    static const int BPP = 32;
};

#endif // JEU_H
