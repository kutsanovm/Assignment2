#include "GameOfLife.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string nameOfSMode;
ifstream nameOfSFile;
string pause;
string enter;
string outputToFile;

int main(int argc, char** argv)
{

  srand (time(NULL)); // this was the beginning of Random

  GameOfLife test;
  ofstream endfile; // this is if they want to print their results
  endfile.open("generations.txt",ios_base::app); // this is the file that we will print to if they select that they want to print their results

  test.countNeighborsInClassicSMode();
  test.countNeighborsInMirrorSMode();
  test.countNeighborsInDoughnutSMode();

  cout << "What type of configuration would you like to run? Enter 'R' for a random configuration or 'S' for a special configuration." << endl;
  cin >> typeOfConfig >> endl;

  if (typeOfConfig == "S")
  {
    cout << "Enter the name of the file you are imputting." << endl;
    cin >> nameOfSFile >> endl;

    cout << "Enter the name of the mode you are running the game in. 'C' for Classic, 'M' for Mirror, or 'D' for Doughnut." << endl;
    cin >> nameOfSMode >> endl;
    if (nameOfSMode == "C")
    {
      cout << "Do you want to pause in between generations? 'Y' or 'N'" << endl;
      cin >> pause >> endl;

      if (pause == "Y")
      {
        int ctrSC = 0;
        while (true)
        {
          ctrSC ++;
          cout << "Generation: " << ctrSC << endl;
          test.getClassicSMode(); // will print the arrays in classic mode by generation
        }
      }
    }
  }
}
/*

      cout << "Do you want to press enter between generations? 'Y' or 'N' " << endl;
      cin >> enter >> endl;

      cout << "Do you want to output everything to a txt file? 'Y' or 'N'" << endl;
      cin >> outputToFile >> endl;
    }




  }
}
  if (typeOfConfig == "R")
  {
    cout << "What is the height of your array?" << endl;
    cin >> height >> endl;

    cout << "What is the width of your array?" << endl;
    cin >> width >> endl;

    cout << "What is the population density (0 < d < 1) of your array?" << endl;
    cin >> popDensity >> endl;

    cout << "Do you want to 'pause' between generations? 'Y/N'" << endl;
    cin >> pause >> endl;

    cout << "Do you want to have to press 'enter' to display each generation? 'Y/N'" << endl;
    cin >> enter >> endl;

    cout << "Do you want to output your results to a txt file? 'Y/N'" << endl;
    cin >> outputToFile >> endl;

    while (!isEmpty(arrayOne))
    {
      cout << "Which boundary mode would you like to play in? Classic ('C'), Mirror ('M'), or Doughnut ('D')" << endl;
      cin >> boundaryMode >> endl;

      if (boundaryMode == "C")
      {

      }

*/









//  }
//  else if (typeOfConfig == "S")
//  {

//  }
