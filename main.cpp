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
            if (r <= 1) {

                Pacmap[i][j] = '#';
            } else if (r >= 2) {
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
        else
        {

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
    cout <<  string (COL+2,'_')<< endl;
    for (int i = 0; i < ROW; i++) {
        cout <<'|';
        for (int j = 0; j < COL; j++) {
            if (i == pacman.y && j == pacman.x) {
                cout << pacman.c;
            } else {
                cout << Pacmap[i][j];
            }
        }
        cout <<'|';
        cout << endl;
    }
    cout <<  string(COL+2,'_')<< COL << endl;
    cout << "Score: " << score << endl;
}

// ----------------

int main() {
    generateRandomMap(Pacmap);
    placeGhostsRandomly(Pacmap);
    setup();
    while (true) {

        drawGhosts(Pacmap);
        ClearScreen();
        draw();

        string verif;
        cin >> verif;
        char input = verif[0];
        if (input == 'z') {
            pacman.y--;
        } else if (input == 'q') {
            pacman.x--;
        } else if (input == 's') {
            pacman.y++;
        } else if (input == 'd') {
            pacman.x++;
        }

        if (Pacmap[pacman.y][pacman.x] == '#' || pacman.x == -1 || pacman.y == COL || pacman.y == -1 || pacman.x == ROW) {
            // Annuler le mouvement
            if (input == 'z') {
                pacman.y++;
            } else if (input == 'q') {
                pacman.x++;
            } else if (input == 's') {
                pacman.y--;
            } else if (input == 'd') {
                pacman.x--;
            }
        }

        for (int i = 0; i < GHOST_COUNT; i++){
            moveGhosts(ghosts[i]);
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            Ghost ghost = ghosts[i];
            if (ghost.x == pacman.x && ghost.y == pacman.y) {
                cout << "Game Over" << endl;
                return 0;
            }
        }
    }
    return 0;
}
