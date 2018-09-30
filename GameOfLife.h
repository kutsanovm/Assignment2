#include <iostream>
using namespace std;

class GameOfLife
{
  public:
    GameOfLife(string file);
    ~GameOfLife();

    string typeOfConfig;
    int importedWIDTH;
    int importedHEIGHT;
    int width;
    double popDensity;
    string pause;
    string enter;
    int fileCtr;
    string line;
    string nameOfSMode;

  //  char arrayOne[][];
  //  char arrayTwo[][];

    char**arrayOne;
    char**arrayTwo;
    char**array1;
    char**array2;

    int neighborCount;
    int neighborCountDon;
    int neighborCountMir;

    char getClassicSMode(); //char array1[0][0]
    char getMirrorSMode(); //char array1[0][0]
    char getDonutSMode(); //char array1[0][0]

    void simulateDonut();
    void simulateMirror();
    void simulateClassic();

    void stdd();
    void countNeighborsInClassicSMode();
    void countNeighborsInMirrorSMode();
    void countNeighborsInDonutSMode();

};
