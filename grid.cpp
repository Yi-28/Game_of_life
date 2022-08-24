#include "constants.h"
#include "grid.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

Grid::Grid()
{
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML !");
    window.setFramerateLimit (5);

    dead.setFillColor(sf::Color(45,255,255,210));
    alive.setFillColor(sf::Color::Cyan);


    for (int i = 1; i < MAX; i++){
        for (int j = 1; j < MAX; j++){
            //if (j == random (i + 1, MAX)){
            if (grid[i][j] = ALIVE){
                SetAlive ( i,  j);
                //alive.setPosition(i,j);

            }
            else {
                Kill( i,  j);
                //dead.setPosition(i,j);

            }
        }
    }
}

void Grid::SetAlive(int i, int j){
    grid [i][j] = ALIVE;
}

void Grid::Kill(int i, int j){
    grid [i][j] = DEAD;
}

bool Grid::IsAlive ( int i, int j){
    if (grid [i][j] == DEAD)
        return false;

    return true;
}

void Grid::PopulateRandom (){

    int row = 0;
    int col = 0;

    for(int i = 0; i < RANDOM; i++){
         row = (random (1, MAX-1));
         col = (random (1, MAX-1));
         if (grid[row][col] == ALIVE) {
             i-=1;
         }
         grid[row][col] = ALIVE;
    }
}

void Grid::step (){
    int count = 0;
    int auxiliar[MAX][MAX];

    //circular (grid);
    copy_array(auxiliar, grid);

    for (int i = 1; i < MAX - 1 ; i++){
        for (int j = 1; j < MAX -1 ; j++){
            count = count_neighbors( i, j);
            if (count == 3){
                auxiliar[i][j] = ALIVE;
            }
            else if (count == 2){
                auxiliar[i][j] = grid [i][j];
            }
            else {
                auxiliar[i][j] = DEAD;
            }
        }
    }
    copy_array (grid, auxiliar);

}

int Grid::count_neighbors (int i, int j){

    int row = i;
    int col = j;
    int count = 0;

    if (grid[i][j] == ALIVE){
        count -= 1;
    }
    for (int i = row - 1; i <= row + 1; i++){
        for (int j = col - 1; j <= col + 1; j++){
            if (grid[i][j] == ALIVE){
                count += 1;
            }
        }
    }
    return count;
}

void Grid::clear (){

    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            grid[i][j] = DEAD;
        }
    }
}

void Grid::copy_array(int dest[][MAX], int src[][MAX]){

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            dest[i][j] = src [i][j];     //destination array = source array
        }
    }
}

void Grid::show (){

    for (int i = 1; i < MAX - 1; i++){
        for (int j = 1; j < MAX - 1; j++){
            if (grid [i][j] == ALIVE){
                 cout << setw (WIDTH) << "*";

            }
            else{
                 cout << setw (WIDTH) << " ";
            }
        }cout << endl;
    }
}

bool Grid::save_array (char file_name[]){
    ofstream f;

    f.open("save.txt");

    if (f.fail()){
            //cout <<" FAIL"<<endl;
            return false;
        }

    for (int i = 1; i < MAX - 1; i++){
        for (int j = 1; j < MAX - 1; j++){
            f << grid [i][j] << " ";
        }
    }

    f.close();
    return true;
}

bool Grid::load_array (char file_name[]){
    ifstream f;

    f.open("save.txt");

    if (f.fail()){
            //cout <<" File failed to open..."<<endl;
            return false;
        }

    for (int i = 1; i < MAX - 1; i++){
        for (int j = 1; j < MAX - 1; j++){
            f >> grid [i][j];
        }
    }

    f.close();
    return true;
}

void Grid::circular (int grid[MAX][MAX]){
    for (int i = 0 ; i < MAX - 1; i++) {
        for (int j = 0 ;j < MAX - 1; j++) {
            //first column will have neighbors on the last column.
            grid [i][MAX - 1] = grid [i][1];
            //last column will have neighbors on the first column.
            grid [i][0] = grid [i][MAX - 2];
            //first row will have neighbors on the last row.
            grid [MAX - 1][j] = grid [1][j];
            //last row will have neighbors on the first row.
            grid [0][j] = grid [MAX - 2][j];
        }
    }
    //top-left corner will have neighbors with the bottom-right corner
    grid [0][0] = grid [MAX - 2][MAX - 2];
    grid [MAX -1] [MAX - 1] = grid [1][1];
    //top-right corner will have neighbors with the bottom-left corner
    grid [0][MAX -1] = grid [MAX - 2][1];
    grid [MAX -1] [0] = grid [1][MAX -2];
}

int Grid::random(int lo, int hi){

    return rand() % (hi-lo+1) + lo;
}

void Grid::Sidebar(){

    if (!font.loadFromFile("arial.ttf")){
        cout<<"animate() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }

    sb_text = sf::Text("Stop", font);
    sb_text.setCharacterSize(30);
    sb_text.setStyle(sf::Text::Bold);
    sb_text.setColor(sf::Color::White);
    sb_text.setPosition(sf::Vector2f (1300, 50 ));

}

void Grid::Draw(){
    //Look at the data and based on the data, draw shapes on window object.
    int vectorY = 0;
    int vectorX = 0;
    //show();
    Sidebar();

    for (int i = 1; i < MAX - 1; i++){
        for (int j = 1; j < MAX - 1; j++){
            vectorY = i* (CELL_SIZE+1);
            vectorX = j* (CELL_SIZE+1);
            if (IsAlive(i,j)){

                 alive.setPosition (sf::Vector2f(vectorX,vectorY));
                 alive.setSize (sf::Vector2f(CELL_SIZE,CELL_SIZE));

                 window.draw (alive);
            }
            else{
                 dead.setPosition (sf::Vector2f(vectorX,vectorY));
                 dead.setSize (sf::Vector2f(CELL_SIZE,CELL_SIZE));

                 window.draw (dead);
            }
        }
    }

    window.draw(sb_text);
}

void Grid::render(){
       window.clear();
       Draw();
       window.display();
}

void Grid::processEvents()
{
   sf::Event event;
   while (window.pollEvent(event))//or waitEvent
       {
        // check the type of the event...
           switch (event.type)
           {
               // window closed
               // "close requested" event: we close the window
               case sf::Event::Closed:
                   window.close();
                   break;

               // key pressed
               case sf::Event::KeyPressed:
                   //...
                   break;
               case sf::Event::MouseButtonReleased:
                       if (event.mouseButton.button == sf::Mouse::Right)
                       {
                           std::cout << "the right button was pressed" << std::endl;
                           std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                           std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                       }
                       else
                           std::cout<<"left button?"<<std::endl;
                           alive.setPosition(event.mouseButton.x,event.mouseButton.y);

                       break;

                   default:
                       break;
           }
       }
}

void Grid::run()
{
   while (window.isOpen())
   {
       processEvents();

       step();

       render(); //clear/draw/display
   }
}
