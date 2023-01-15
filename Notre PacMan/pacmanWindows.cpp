#include <iostream>
#include <cstring>

/**
 * \file   main.cpp
 * \authors Thibault AMETTLER, Enzo BEDOS, Enzo COMBELONGE, Francesco LIMOSANI, Raoul MAOULIDA
 * \date Janvier 13 2023
 * \brief   Projet C++ "Voleur/Policier" sur le modele de PacMan
 */

using namespace std;

/**
 * @brief ROW
 * @return Variable definissant la dimention sur l'axe X (le nombre de caractère sur une ligne)
 */
const int ROW = 20;
/**
 * @brief COL
 * @return Variable definissant la dimention sur l'axe Y (le nombre de caractère sur une colonne)
 */
const int COL = 30;

/**
 * @brief GHOST_COUNT
 * @return Variable definissant le nombre de fantome sur la carte
 */
const int GHOST_COUNT = 4;

char Pacmap[ROW][COL];

/**
 * @brief generateRandomMap
 * @return Génère une carte de façon aléatoire qui a pour paramètre les dimentions de la carte Map[ROW][COL], où ROW et COL variable int defini au préalable.
 * Elle replace 20% de la map par des murs afin de creer un "labyrithe".
 */

/**
 * @brief ClearScreen
 * @return Fonction utilisée afin d'effacer l'écran
 */
void ClearScreen()
{
    system("cls");
}

/**
 * @brief Struct PacMan
 * @return declaration d'un structure PacMan qui definis le caractere utilisé pour représenté PacMan et la position x, y de PacMan
 */
struct PacMan
{
    char carte;
    int x, y;
    char c;
};

PacMan pacman;

/**
 * @brief Struct Ghost
 * @return declaration d'un structure Ghost qui definis le caractere utilisé pour représenté un fantome et la position x, y des fantomes
 */
struct Ghost
{
    char carte;
    int x, y;
    char c;
};

/**
 * @brief Ghost
 * @return Génération des fantomes
 */
Ghost ghosts[GHOST_COUNT];

int score = 0;

/**
 * @brief Setup
 * @return Fonction initialisant la map et les fantomes
 */
void setup()
{
    pacman.x = 1;
    pacman.y = 1;
    pacman.c = 'P';

    for (int i = 0; i <= GHOST_COUNT; i++)
    {
        ghosts[i].x = rand() % ROW + 1;
        ghosts[i].y = rand() % COL + 1;
        ghosts[i].c = 'G';
    }
}

void generateRandomMap(char Pacmap[ROW][COL])
{

    srand(time(0));

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            int nbrRand = rand() % 20;
            if (nbrRand <= 1)
            {

                Pacmap[i][j] = '#';
            }
            else if (nbrRand >= 2)
            {
                Pacmap[i][j] = ' ';
            }
        }
    }
}
/**
 * @brief moveGhosts
 * @return Fonction permettant aux fantomes de se depolacer vers PacMan (cette foncction ne permet pas d'afficher les fantomes)
 */

void moveGhosts(Ghost &ghost)
{
    int x = 0;
    int y = 0;

    if ((ghost.x >= pacman.x) and (ghost.x - 1 != '#'))
    {
        x = ghost.x - 1;
    }
    else if ((ghost.x <= pacman.x) and (ghost.x + 1 != '#'))
    {
        x = ghost.x + 1;
    }

    if ((ghost.y >= pacman.y) and (ghost.y - 1 != '#'))
    {
        y = ghost.y - 1;
    }
    else if ((ghost.y <= pacman.y) and (ghost.y + 1 != '#'))
    {
        y = ghost.y + 1;
    }

    if (Pacmap[x][y] != '#')
    {
        if (Pacmap[x][y] != 'G')
        {
            Pacmap[ghost.y][ghost.x] = ' ';
            ghost.x = x;
            ghost.y = y;
        }
    }
}

/**
 * @brief drawGhosts
 * @return Fonction permettant de dessiner les fantomes sur la map
 */
void drawGhosts(char Pacmap[ROW][COL])
{
    for (int i = 0; i < GHOST_COUNT; i++)
    {
        Ghost ghost = ghosts[i];
        if (Pacmap[ghost.y][ghost.x] != '#')
        {
            Pacmap[ghost.y][ghost.x] = ghost.c;
        }
    }
}

/**
 * @brief placeGhostsRandomly
 * @return Fonction permettant de placer les fantomes aléatoirement sur la map au début de la partie
 */
void placeGhostsRandomly(char Pacmap[ROW][COL])
{
    for (int i = 0; i <= GHOST_COUNT; i++)
    {
        Ghost ghost = ghosts[i];
        while (true)
        {
            ghost.x = rand() % COL;
            ghost.y = rand() % ROW;
            if (Pacmap[ghost.y][ghost.x] != '#')
            {
                break;
            }
        }
    }
}

/**
 * @brief draw
 * @return Fonction permettant de dessiner la map afin d'actualiser les position de PacMan et des fantomes
 */
void draw()
{
    cout << string(COL + 2, '_') << endl;
    for (int i = 0; i < ROW; i++)
    {
        cout << '|';
        for (int j = 0; j < COL; j++)
        {
            if (i == pacman.y && j == pacman.x)
            {
                cout << pacman.c;
            }
            else
            {
                cout << Pacmap[i][j];
            }
        }
        cout << '|';
        cout << endl;
    }
    cout << string(COL + 2, '_') << endl
         << "Score: " << score << endl;
}
void deplacerPacMan()
{
    string verif;
    cin >> verif;
    char input = verif[0];
    if (input == 'Z' || input == 'z')
    {
        pacman.y--;
    }
    else if (input == 'Q' || input == 'q')
    {
        pacman.x--;
    }
    else if (input == 'S' || input == 's')
    {
        pacman.y++;
    }
    else if (input == 'D' || input == 'd')
    {
        pacman.x++;
    }

    if (Pacmap[pacman.y][pacman.x] == '#' || pacman.x == -1 || pacman.y == COL || pacman.y == -1 || pacman.x == ROW)
    {
        // Annuler le mouvement
        if (input == 'Z' || input == 'Z')
        {
            pacman.y++;
        }
        else if (input == 'Q' || input == 'q')
        {
            pacman.x++;
        }
        else if (input == 'S' || input == 's')
        {
            pacman.y--;
        }
        else if (input == 'D' || input == 'd')
        {
            pacman.x--;
        }
    }
}
/**
 * @brief main
 * @return main du coup
 */
int main()
{
    generateRandomMap(Pacmap);
    placeGhostsRandomly(Pacmap);
    setup();
    while (true)
    {
        drawGhosts(Pacmap);
        ClearScreen();
        draw();
        cout << "ghost 0 x= " << ghosts[0].x << " y= " << ghosts[0].y << endl;
        cout << "ghost 1 x= " << ghosts[1].x << " y= " << ghosts[1].y << endl;
        cout << "ghost 2 x= " << ghosts[2].x << " y= " << ghosts[2].y << endl;
        cout << "ghost 3 x= " << ghosts[3].x << " y= " << ghosts[3].y << endl;
        cout << "ghost 4 x= " << ghosts[4].x << " y= " << ghosts[4].y << endl;
        cout << "pacman x= " << pacman.x << " y= " << pacman.y << endl;

        deplacerPacMan();
        for (int i = 0; i < GHOST_COUNT; i++)
        {
            moveGhosts(ghosts[i]);
        }
        for (int i = 0; i < GHOST_COUNT; i++)
        {
            if (ghosts[i].x == pacman.x && ghosts[i].y == pacman.y)
            {
                cout << "Game Over" << endl;
            }
        }
    }
}