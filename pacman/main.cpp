#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

using namespace std;

void dessiner(MinGL &window)
{
    // Pour dessiner quelque chose avec minGL 2, vous pouvez soit instancier l'objet dans une variable et l'injecter dans la fenêtre...
    //nsShape::Rectangle rect1(nsGraphics::Vec2D(300, 500), nsGraphics::Vec2D(150, 150), nsGraphics::KBlue);
    //window << rect1;

    // ...ou l'injecter directement dans la fenêtre!
    //window << nsShape::Rectangle(nsGraphics::Vec2D(600, 800), nsGraphics::Vec2D(400, 400), nsGraphics::KPurple);

    // (Vous voyez par ailleurs que l'ordre d'affichage est important, le rectangle violet masque maintenant une partie du rectangle bleu.)
    // Vous pouvez combiner les différentes formes disponibles pour faire des choses plus complexes.

    // Voilà un bouton de fermeture.
    //window << nsShape::Circle(nsGraphics::Vec2D(100, 320), 50, nsGraphics::KRed);
    //window << nsShape::Line(nsGraphics::Vec2D(70, 290), nsGraphics::Vec2D(130, 350), nsGraphics::KWhite, 3.f);
    //window << nsShape::Line(nsGraphics::Vec2D(130, 290), nsGraphics::Vec2D(70, 350), nsGraphics::KWhite, 3.f);

    // Et voilà la triforce.
    //window << nsShape::Triangle(nsGraphics::Vec2D(200, 620), nsGraphics::Vec2D(400, 620), nsGraphics::Vec2D(300, 420), nsGraphics::KYellow);
    //window << nsShape::Triangle(nsGraphics::Vec2D(400, 620), nsGraphics::Vec2D(600, 620), nsGraphics::Vec2D(500, 420), nsGraphics::KYellow);
    //window << nsShape::Triangle(nsGraphics::Vec2D(300, 420), nsGraphics::Vec2D(500, 420), nsGraphics::Vec2D(400, 220), nsGraphics::KYellow);

    // N'hésitez pas a lire la doc pour plus de détails.
   //window << nsShape::Circle(nsGraphics::Vec2D(250, 250), 200, nsGraphics::KBlack);
    //window << nsShape::Circle(nsGraphics::Vec2D(250, 250), 200, nsGraphics::KYellow);
    //window << nsShape::Triangle(nsGraphics::Vec2D(250, 250), nsGraphics::Vec2D(450, 350), nsGraphics::Vec2D(450, 150), nsGraphics::KBlack);
    //window << nsShape::Circle(nsGraphics::Vec2D(285, 160), 25, nsGraphics::KBlack);


    //Pac-Man
    window << nsShape::Circle(nsGraphics::Vec2D(300,300), 150, nsGraphics::KYellow);
    window << nsShape::Circle(nsGraphics::Vec2D(310,240), 20, nsGraphics::KBlack);
    window << nsShape::Triangle(nsGraphics::Vec2D(300,300), nsGraphics::Vec2D(421,210), nsGraphics::Vec2D(443,250), nsGraphics::KBlack);
    window << nsShape::Triangle(nsGraphics::Vec2D(300,300), nsGraphics::Vec2D(443,250), nsGraphics::Vec2D(450,300), nsGraphics::KBlack);
    window << nsShape::Triangle(nsGraphics::Vec2D(300,300), nsGraphics::Vec2D(443,350), nsGraphics::Vec2D(450,300), nsGraphics::KBlack);
    window << nsShape::Triangle(nsGraphics::Vec2D(300,300), nsGraphics::Vec2D(421,390), nsGraphics::Vec2D(443,350), nsGraphics::KBlack);

    //window << nsShape::Circle(nsGraphics::Vec2D(300,300), 75, nsGraphics::KYellow);
    //window << nsShape::Circle(nsGraphics::Vec2D(310,240), 10, nsGraphics::KBlack);
//
    //window << nsShape::Triangle(nsGraphics::Vec2D(300,300), nsGraphics::Vec2D(421,230), nsGraphics::Vec2D(371,250), nsGraphics::KBlack);
    //window << nsShape::Triangle(nsGraphics::Vec2D(300,300), nsGraphics::Vec2D(443,250), nsGraphics::Vec2D(450,300), nsGraphics::KBlack);
    //window << nsShape::Triangle(nsGraphics::Vec2D(300,300), nsGraphics::Vec2D(443,350), nsGraphics::Vec2D(450,300), nsGraphics::KBlack);
    //window << nsShape::Triangle(nsGraphics::Vec2D(300,300), nsGraphics::Vec2D(421,390), nsGraphics::Vec2D(443,350), nsGraphics::KBlack);

}

int main()
{
    // Initialise le système
    MinGL window("01 - Shapes", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
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

    return 0;
}
