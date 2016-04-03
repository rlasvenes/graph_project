#include "jeu.h"
#include <SFML/Graphics.hpp>

Jeu::Jeu()
    : m_fenetre (sf::VideoMode(LONGUEUR_ECRAN, LARGEUR_ECRAN, BPP)/*.getDesktopMode()*/,
                 L"RL - CASSE-BRIQUE",
                 sf::Style::Close)
{
    m_fenetre.setFramerateLimit(50);
    // m_fenetre.setSize(sf::Vector2u(100 ,100));

    m_sommet.setOrigin(20, 20);
    m_sommet.setPosition(LONGUEUR_ECRAN/2 - m_sommet.getRadius(), LARGEUR_ECRAN/2 - m_sommet.getRadius());
    m_sommet.setRadius(20);
    m_sommet.setOutlineThickness(5);
    m_sommet.setOutlineColor(sf::Color(255, 0, 0, 128));
    m_sommet.setFillColor(sf::Color(255, 0, 0, 255));

    // m_rect.setSize(sf::Vector2f(25, 25));
    // m_rect.setFillColor(sf::Color::Black);
    // m_rect.setOrigin(12.5, 12.5);
    // m_rect.setPosition(50, 50);

    m_barre.setSize(sf::Vector2f(LONGUEUR_ECRAN, 35));
    m_barre.setPosition(0, 0); // on n'a pas "set" d'origines donc il s'afficheras tout en haut à gauche
    m_barre.setFillColor(sf::Color::Red);

    m_selection_button.setSize(sf::Vector2f(m_barre.getSize().y / 1.2, m_barre.getSize().y / 1.2));
    m_selection_button.setFillColor(sf::Color::Cyan);

    double posBut = (m_barre.getSize().y - (m_barre.getSize().y / 1.2)) / 2;
    m_selection_button.setPosition(posBut, posBut);
    effacerEcran = false;
}

// ---------------------------------------------------------------------------------------------------

void Jeu::run() {
    while (m_fenetre.isOpen()) {
        gerer_evenements(); // on gere et on actualise les evenements
        dessiner(); // cette méthode va servir à afficher du contenu sur la fenetre de rendu
    }
}

// ---------------------------------------------------------------------------------------------------

void Jeu::gerer_evenements() {

    sf::Event event;
    while (m_fenetre.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed :
            m_fenetre.close();
            break;

        case sf::Event::KeyPressed :
            switch (event.key.code) {
            case sf::Keyboard::Escape :
                m_fenetre.close();
                break;

            case sf::Keyboard::Space :

                for(sf::CircleShape c : tabCercle) {
                    m_fenetre.draw(c);
                }


                break;

            default:
                break;
            }
            break;

        case sf::Event::MouseButtonPressed : // evenement souris
            if (event.mouseButton.button == sf::Mouse::Left  ) {
                //std::cout << "LEFT BUTTON PRESSED !" << std::endl;
                std::cout << "Vector's size : " << tabCercle.size()+1 << std::endl;
                m_sommet.setPosition(event.mouseButton.x, event.mouseButton.y);
                tabCercle.push_back(m_sommet); // ajout dans vecteur
            }
            else {

            }

            if (m_selection_button.getLocalBounds().contains(event.mouseButton.x, event.mouseButton.y)) { // penser a faire une
                // classe "button"
                std::cout << "__COLLISION__" << std::endl << std::endl;
                //m_fenetre.clear(sf::Color::White);
                tabCercle.clear();
                // effacerEcran = !effacerEcran;
            }

            break;

        case sf::Event::MouseMoved :
            // std::cout << "MOUSE POSITION.X = " << event.mouseMove.x << std::endl;
            // std::cout << "MOUSE POSITION.Y = " << event.mouseMove.y << std::endl << std::endl;

            // et donc => faire une méthode du genre "isHover" (polymorphe ?)

            // voir => faire un foreach en parcourant les element du tableau, et ne faire
            // un .push_back() que si le curseur ne se trouve pas au dessus d'un objet déjà existant.

            //std::cout << "POSITION BARRE (TEST) = " << m_barre.getPosition().x << std::endl;

            for(sf::CircleShape c : tabCercle) {
                if (c.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                    c.setFillColor(sf::Color::Blue);
                }
            }


            break;

        default:
            break;
        }
    }
}

// ---------------------------------------------------------------------------------------------------

void Jeu::dessiner() {
    m_fenetre.clear(sf::Color::White);

    for(sf::CircleShape c : tabCercle) { // on parcours le vecteur, puis on affiche chaque element
        m_fenetre.draw(c);
    }


    // m_fenetre.draw(tabCercle); // ne marche pas
    // m_fenetre.draw(m_rect);

    // barre de menu (temporaire, pour des tests)
    m_fenetre.draw(m_barre);

    // on feras les affichages des boutons après celui de la barre, sinon, en dessous
    m_fenetre.draw(m_selection_button);

    m_fenetre.display();
}
