#ifndef GRID_H
#define GRID_H
#include "constants.h"
#include <SFML/Graphics.hpp>

class Grid
{
public:
    Grid();

    void SetAlive (int i, int j);
    bool IsAlive (int i, int j);

    void Kill(int i, int j);

    void PopulateRandom ();

    int count_neighbors ( int i, int j);   //count the alive neighbors or cells

    void clear ();

    void copy_array(int dest[][MAX], int src[][MAX]);

    void show ();                  //print the grid with live and dead cells

    void step ();

    void circular (int g[MAX][MAX]);

    int random (int lo, int hi);                        //generate random numbers

    bool save_array (char file_name[]);   //save array
    bool load_array (char file_name[]);    //load array

    void Draw();
    void run();
    void processEvents();
    void update();
    void render();
    void Sidebar();



private:
    sf::RenderWindow window;
    sf::RectangleShape alive;
    sf::RectangleShape dead;

    sf::Text sb_text;
    sf::Font font;
    bool mouseIn;
    int grid [MAX][MAX];
};

#endif // GRID_H
