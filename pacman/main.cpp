#include <iostream>
#include <cstring>

// Library Raoul code
#define FPS_LIMIT 60

#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

using namespace std;

//Variable d'environnement (taille et Ghosts)
const int ROW = 20;
const int COL = 30;
const int GHOST_COUNT = 4;

// Carte du jeu avec des murs et des points
char Pacmap[ROW][COL];

// Map
void generateRandomMap(char Pacmap[ROW][COL]) {

    srand(time(0));
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            // Générer un nombre aléatoire entre 0 et 100
            int r = rand() % 20;
            if (r < 3) {
                Pacmap[i][j] = '#';
            } else if (r > 4) {
                Pacmap[i][j] = ' ';
            } else {
                Pacmap[i][j] = ' ';
            }
        }
    }
}

void ClearScreen()
{
    cout << "\033[H\033[2J";
}// ClearScreen ()

//Propriété Pac-Man
struct PacMan {
    int x, y;
    char c;
};

//Génération d'un Pac-Man
PacMan pacman;


//Propriété d'un Ghost
struct Ghost {char carte;

              int x, y;
                        char c;
             };

//Génération de n Ghost (En fonction de la variable GHOST_COUNT)
Ghost ghosts[GHOST_COUNT];

int score = 0;

void setup() {
    pacman.x = 1;
    pacman.y = 1;
    pacman.c = 'P';

    for (int i = 0; i <= GHOST_COUNT; i++) {
        ghosts[i].x = rand()% ROW + 1;
        ghosts[i].y = rand() % COL + 1;
        ghosts[i].c = 'G';
    }
}

void moveGhosts(Ghost & ghost){
    //int dx = rand() % 3 - 1;
    //int dy = rand() % 3 - 1;
    //
    //int x = ghost.x + dx;
    //int y = ghost.y + dy;

    int x = 0;
    int y = 0;

    if ((ghost.x >= pacman.x)and(ghost.x -1 != '#')) {
        x = ghost.x - 1;
    } else if ((ghost.x <= pacman.x)and(ghost.x +1 != '#')){
        x = ghost.x + 1;
    }

    if ((ghost.y >= pacman.y)and(ghost.y -1 != '#')) {
        y = ghost.y - 1;
    } else if ((ghost.y <= pacman.y)and(ghost.y +1 != '#')){
        y = ghost.y + 1;
    }

    if (Pacmap[x][y] != '#'){
        if (Pacmap[x][y] != 'G'){
            Pacmap[ghost.y][ghost.x] = ' ';
            ghost.x = x;
            ghost.y = y;
        }
    }
}

//Affiche les Ghost sur la map
void drawGhosts(char Pacmap[ROW][COL]) {
    for (int i = 0; i < GHOST_COUNT; i++) {
        Ghost ghost = ghosts[i];
        // Vérifier que le fantôme ne se trouve pas sur un mur
        if (Pacmap[ghost.y][ghost.x] != '#') {
            Pacmap[ghost.y][ghost.x] = ghost.c;
        }
    }
}

void placeGhostsRandomly(char Pacmap[ROW][COL]) {
    for (int i = 0; i <= GHOST_COUNT; i++) {
        Ghost ghost = ghosts[i];
        while (true) {
            // Générer des coordonnées aléatoires
            ghost.x = rand() % COL;
            ghost.y = rand() % ROW;
            // Vérifier que la case n'est pas un mur
            if (Pacmap[ghost.y][ghost.x] != '#') {
                break;
            }
        }
    }
}


void draw() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i == pacman.y && j == pacman.x) {
                cout << pacman.c;
            } else {
                cout << Pacmap[i][j];
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

// ----------------
// Part Raoul

void spriteRight(MinGL & window,int posXPacMan,int posYPacMan)
{
    //Corps du Pacman coté droite
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan, posYPacMan), 50, nsGraphics::KYellow);
    //Oeil de Pacman
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan+15, posYPacMan-20), 8, nsGraphics::KBlack);
    // Bouche de Pacman.
    window << nsShape::Triangle(nsGraphics::Vec2D(posXPacMan, posYPacMan), nsGraphics::Vec2D(posXPacMan+52, posYPacMan-15), nsGraphics::Vec2D(posXPacMan+45, posYPacMan+35), nsGraphics::KBlack);

}

void spriteLeft(MinGL & window,int posXPacMan,int posYPacMan)
{
    //Corps du Pacman coté gauche
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan, posYPacMan), 50, nsGraphics::KYellow);
    //Oeil de Pacman
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan-15, posYPacMan-20), 8, nsGraphics::KBlack);
    // Bouche de Pacman.
    window << nsShape::Triangle(nsGraphics::Vec2D(posXPacMan, posYPacMan), nsGraphics::Vec2D(posXPacMan-52, posYPacMan-15), nsGraphics::Vec2D(posXPacMan-45, posYPacMan+35), nsGraphics::KBlack);


}
void spriteDown(MinGL & window,int posXPacMan,int posYPacMan)
{
    //Corps du Pacman coté bas
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan, posYPacMan), 50, nsGraphics::KYellow);
    //Oeil de Pacman
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan-20, posYPacMan+15), 8, nsGraphics::KBlack);
    // Bouche de Pacman.
    window << nsShape::Triangle(nsGraphics::Vec2D(posXPacMan, posYPacMan), nsGraphics::Vec2D(posXPacMan-15, posYPacMan+52), nsGraphics::Vec2D(posXPacMan+35, posYPacMan+45), nsGraphics::KBlack);

}
void spriteUp(MinGL & window,int posXPacMan,int posYPacMan)
{
    //Corps du Pacman coté droite
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan, posYPacMan), 50, nsGraphics::KYellow);
    //Oeil de Pacman
    window << nsShape::Circle(nsGraphics::Vec2D(posXPacMan+30, posYPacMan-10), 8, nsGraphics::KBlack);
    // Bouche de Pacman.
    window << nsShape::Triangle(nsGraphics::Vec2D(posXPacMan, posYPacMan), nsGraphics::Vec2D(posXPacMan-15, posYPacMan-52), nsGraphics::Vec2D(posXPacMan+35, posYPacMan-45), nsGraphics::KBlack);

}
void dessiner(MinGL &window) {

    // Contours de la fenêtre
    window << nsShape::Line(nsGraphics::Vec2D(0, 3),nsGraphics::Vec2D(1680, 3),nsGraphics::KRed, 3);
    window << nsShape::Line(nsGraphics::Vec2D(3, 3),nsGraphics::Vec2D(3, 1050),nsGraphics::KGreen, 5);
    window << nsShape::Line(nsGraphics::Vec2D(1680, 3),nsGraphics::Vec2D(1680, 1050),nsGraphics::KYellow, 5);
    window << nsShape::Line(nsGraphics::Vec2D(0, 980),nsGraphics::Vec2D(1680, 980),nsGraphics::KWhite, 5);
}

nsGraphics::Vec2D rectPos;


//void clavier(MinGL &window,  int x, int y)
//{
//    char touch;
//    cin>>touch;
//    // On vérifie si ZQSD est pressé, et met a jour la position
//    if (window.isPressed({'z', false}))
//    {
//        y = y -30;
//        spriteUp(window,x,y);
//    }
//    if (window.isPressed({'s', false}))
//    {
//        y = y +30;
//        spriteDown(window,x,y);
//    }
//    if (window.isPressed({'q', false}))
//    {
//        x = x -30;
//        spriteLeft(window,x,y);
//    }
//    if (window.isPressed({'d', false}))
//    {
//        x = x +30;
//        spriteRight(window,x,y);
//    }
//}

void clavier(MinGL &window)
{
    int x = 100;
    int y = 100;

    // On vérifie si ZQSD est pressé, et met a jour la position

        if (window.isPressed({'z', false})){
            y-=50;
            spriteUp(window,x,y);
        }

        else if (window.isPressed({'s', false})){
            y+=100;
            spriteDown(window,x,y);
        }
        else if (window.isPressed({'q', false}))
            rectPos.setX(rectPos.getX() - 1);
       else if (window.isPressed({'d', false}))
            rectPos.setX(rectPos.getX() + 1);}



int main() {
    //generateRandomMap(Pacmap);
    //placeGhostsRandomly(Pacmap);
    //setup();
    //while (true) {
    //    for (int i = 0; i < GHOST_COUNT; i++){
    //        moveGhosts(ghosts[i]);
    //    }
    //
    //    drawGhosts(Pacmap);
    //    ClearScreen();
    //    draw();
    //
    //    string verif;
    //    cin >> verif;
    //    char input = verif[0];
    //    if (input == 'z') {
    //        pacman.y--;
    //    } else if (input == 'q') {
    //        pacman.x--;
    //    } else if (input == 's') {
    //        pacman.y++;
    //    } else if (input == 'd') {
    //        pacman.x++;
    //    }
    //
    //    if (Pacmap[pacman.y][pacman.x] == '#') {
    //        // Annuler le mouvement
    //        if (input == 'z') {
    //            pacman.y++;
    //        } else if (input == 'q') {
    //            pacman.x++;
    //        } else if (input == 's') {
    //            pacman.y--;
    //        } else if (input == 'd') {
    //            pacman.x--;
    //        }
    //    }
    //
    //    for (int i = 0; i < GHOST_COUNT; i++) {
    //        Ghost ghost = ghosts[i];
    //        if (ghost.x == pacman.x && ghost.y == pacman.y) {
    //            cout << "Game Over" << endl;
    //            return 0;
    //        }
    //    }
    //}
    //
    //Code raoul

    // Initialise le système
    MinGL window("01 - Shapes", nsGraphics::Vec2D(1680, 1050), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    //int x = 100;
    //int y = 100;
    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On dessine les formes géométriques
        //clavier(window);
        clavier(window);
        dessiner(window);
        //test

        //char touch;
        //cin>>touch;
        //for (unsigned i(0);i<1;++i){
        //    if (window.isPressed({'d', false})){
        //        x = x +30;
        //        spriteRight(window,x,y);
        //    }
        //    else if (window.isPressed({'q', false})){
        //        x = x -30;
        //        spriteLeft(window,x,y);
        //    }
        //    else if (window.isPressed({'s', false})){
        //        y = y +30;
        //        spriteDown(window,x,y);
        //    }
        //    else if (window.isPressed({'z', false})){
        //        y = y -30;
        //        spriteUp(window,x,y);
        //    }
        //}


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

