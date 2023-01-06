#include <iostream>
#include <cstring>


using namespace std;

//Variable d'environnement (taille et Ghosts)
const int ROW = 20;
const int COL = 30;
const int GHOST_COUNT = 4;

// Carte du jeu avec des murs et des points
char map[ROW][COL];

// Map
void generateRandomMap(char map[ROW][COL]) {

    srand(time(0));
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            // Générer un nombre aléatoire entre 0 et 100
            int r = rand() % 20;
            if (r < 3) {
                map[i][j] = '#';
            } else if (r > 4) {
                map[i][j] = ' ';
            } else {
                map[i][j] = ' ';
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

    if (map[x][y] != '#'){
        if (map[x][y] != 'G'){
            map[ghost.y][ghost.x] = ' ';
            ghost.x = x;
            ghost.y = y;
        }
    }
}

//Affiche les Ghost sur la map
void drawGhosts(char map[ROW][COL]) {
    for (int i = 0; i < GHOST_COUNT; i++) {
        Ghost ghost = ghosts[i];
        // Vérifier que le fantôme ne se trouve pas sur un mur
        if (map[ghost.y][ghost.x] != '#') {
            map[ghost.y][ghost.x] = ghost.c;
        }
    }
}

void placeGhostsRandomly(char map[ROW][COL]) {
    for (int i = 0; i <= GHOST_COUNT; i++) {
        Ghost ghost = ghosts[i];
        while (true) {
            // Générer des coordonnées aléatoires
            ghost.x = rand() % COL;
            ghost.y = rand() % ROW;
            // Vérifier que la case n'est pas un mur
            if (map[ghost.y][ghost.x] != '#') {
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
                cout << map[i][j];
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

int main() {
    generateRandomMap(map);
    placeGhostsRandomly(map);
    setup();
    while (true) {
        for (int i = 0; i < GHOST_COUNT; i++){
            moveGhosts(ghosts[i]);
        }

        drawGhosts(map);
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

        if (map[pacman.y][pacman.x] == '#') {
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

