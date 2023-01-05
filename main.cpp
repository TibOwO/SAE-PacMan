#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

using namespace std;


void map (MinGL &window) {
    /* 1 */    window << nsShape::Line(nsGraphics::Vec2D(110, 110),nsGraphics::Vec2D(400, 110),nsGraphics::KWhite, 5);
    /* 2 */    window << nsShape::Line(nsGraphics::Vec2D(400, 110),nsGraphics::Vec2D(400, 200),nsGraphics::KWhite, 5);
    /* 3 */    window << nsShape::Line(nsGraphics::Vec2D(400, 200),nsGraphics::Vec2D(110, 200),nsGraphics::KWhite, 5);
    /* 4 */    window << nsShape::Line(nsGraphics::Vec2D(110, 200),nsGraphics::Vec2D(110, 400),nsGraphics::KWhite, 5);
    /* 5 */    window << nsShape::Line(nsGraphics::Vec2D(310, 310),nsGraphics::Vec2D(310, 400),nsGraphics::KWhite, 5);
    /* 6 */    window << nsShape::Line(nsGraphics::Vec2D(400, 310),nsGraphics::Vec2D(310, 310),nsGraphics::KWhite, 5);
    /* 7 */    window << nsShape::Line(nsGraphics::Vec2D(400, 310),nsGraphics::Vec2D(400, 400),nsGraphics::KWhite, 5);
    /* 8 */    window << nsShape::Line(nsGraphics::Vec2D(510, 110),nsGraphics::Vec2D(510, 400),nsGraphics::KWhite, 5);
    /* 9 */    window << nsShape::Line(nsGraphics::Vec2D(510, 110),nsGraphics::Vec2D(620, 110),nsGraphics::KWhite, 5);
    /* 10 */    window << nsShape::Line(nsGraphics::Vec2D(620, 110),nsGraphics::Vec2D(620, 310),nsGraphics::KWhite, 5);
    /* 11 */    window << nsShape::Line(nsGraphics::Vec2D(730, 0),nsGraphics::Vec2D(730, 200),nsGraphics::KWhite, 5);
    /* 12 */    window << nsShape::Line(nsGraphics::Vec2D(730, 200),nsGraphics::Vec2D(800, 200),nsGraphics::KWhite, 5);
    /* 13 */    window << nsShape::Line(nsGraphics::Vec2D(800, 200),nsGraphics::Vec2D(800, 400),nsGraphics::KWhite, 5);
    /* 14 */
}

void dessiner(MinGL &window) {
    int posXPacMan = 55;
    int posYPacMan = 55;
    //Corps du Pacman
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan, posYPacMan), 50, nsGraphics::KYellow);
    //Oeil de Pacman
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan+15, posYPacMan-20), 8, nsGraphics::KBlack);
    // Bouche de Pacman.
    window << nsShape::Triangle(nsGraphics::Vec2D(posXPacMan, posYPacMan), nsGraphics::Vec2D(posXPacMan+52, posYPacMan-15), nsGraphics::Vec2D(posXPacMan+45, posYPacMan+35), nsGraphics::KBlack);

    //Bords de la fenetre
    window << nsShape::Line(nsGraphics::Vec2D(0, 0),nsGraphics::Vec2D(1280, 0),nsGraphics::KWhite, 5);
    window << nsShape::Line(nsGraphics::Vec2D(0, 0),nsGraphics::Vec2D(0, 720),nsGraphics::KWhite, 5);
    window << nsShape::Line(nsGraphics::Vec2D(1280, 0),nsGraphics::Vec2D(1280, 720),nsGraphics::KWhite, 5);
    window << nsShape::Line(nsGraphics::Vec2D(0, 720),nsGraphics::Vec2D(1280, 720),nsGraphics::KWhite, 5);




}


int main()
{
    // Initialise le système
    MinGL window("01 - Shapes", nsGraphics::Vec2D(1280, 720), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
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
