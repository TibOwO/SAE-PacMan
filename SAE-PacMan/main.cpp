#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

using namespace std;



void dessiner(MinGL &window) {
    int posXPacMan = 50;
    int posYPacMan = 50;
    //Corps du Pacman
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan, posYPacMan), 50, nsGraphics::KYellow);
    //Oeil de Pacman
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan+15, posYPacMan-20), 8, nsGraphics::KBlack);
    // Bouche de Pacman.
    window << nsShape::Triangle(nsGraphics::Vec2D(posXPacMan, posYPacMan), nsGraphics::Vec2D(posXPacMan+52, posYPacMan-15), nsGraphics::Vec2D(posXPacMan+45, posYPacMan+35), nsGraphics::KBlack);

    window << nsShape::Line(nsGraphics::Vec2D(0, 0),nsGraphics::Vec2D(1680, 0),nsGraphics::KRed, 5);
    window << nsShape::Line(nsGraphics::Vec2D(0, 0),nsGraphics::Vec2D(0, 1050),nsGraphics::KGreen, 5);
    window << nsShape::Line(nsGraphics::Vec2D(1680, 0),nsGraphics::Vec2D(1680, 1050),nsGraphics::KYellow, 5);
    window << nsShape::Line(nsGraphics::Vec2D(0, 965),nsGraphics::Vec2D(1680, 965),nsGraphics::KWhite, 5);
}


int main()
{
    // Initialise le système
    MinGL window("01 - Shapes", nsGraphics::Vec2D(1680, 1050), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On dessine les formes géométriques
        dessiner(window);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    return 0;}
