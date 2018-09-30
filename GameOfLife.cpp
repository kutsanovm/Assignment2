#include "GameOfLife.h"
#include <iostream>
#include <fstream>
using namespace std;
// all around helpful info about arrays found at https://www.cs.cmu.edu/~mrmiller/15-110/Handouts/arrays2D.pdf
GameOfLife::GameOfLife(string nameOfSFile)
{
  ifstream GOLFile(nameOfSFile);
  fileCtr = 0;
  if (GOLFile) // checks to see if we are testing the correct file for DNA strands
  {
  //   getLine(GOLFile, importedWIDTH) go through SPECIFICALLY the first 2 lines

  // helpful info for reading txt file into an array found at https://stackoverflow.com/questions/36708370/reading-from-txt-file-into-two-dimensional-array-in-c
  // got info for reading INDIVIDUAL lines of a file at https://stackoverflow.com/questions/13035674/how-to-read-line-by-line-or-a-whole-text-file-at-once
  // AND also at https://stackoverflow.com/questions/14867944/how-can-i-read-first-line-from-file (it was very confusing to me, but then i just added a counter)
    while (getline(GOLFile,line)) // runs through each line in the test file
    {
      if (fileCtr == 0) { // checks the first line (of the imported file) to get the height
        importedHEIGHT =stoi(line);
      }
      else if (fileCtr == 1) { // checks the second line (of the imported file) to get the width
        importedWIDTH =stoi(line);
        break;
      }
      fileCtr++;
    }

    arrayOne = new char*[importedHEIGHT];
    arrayTwo = new char*[importedHEIGHT];
    for (int i = 0; i <importedHEIGHT; i++) // begins to build the array based on the given info in the imported file
    {
      arrayOne[i] = new char[importedWIDTH]; // makes sure the arrays are identical
      arrayTwo[i] = new char[importedWIDTH];
    }

    fileCtr =0;
    while (getline(GOLFile,line)) // loops through the rest of the file and puts the contents of the file into the game arrays (all of the X's and -'s')
    {
      for (int i = 0; i < line.length(); i++) {
        arrayOne[fileCtr][i] =line[i];
      }
    }
  }
  else
  {
    cout << "bad file";
  }
}

GameOfLife::~GameOfLife() //destructor
{
  cout << "array deleted" << endl;
}


void GameOfLife::stdd()
{

}

char GameOfLife::getClassicSMode() //we should call this in main to print the several generations using classic mode
{
  return this->simulateClassic();
}

char GameOfLife::getMirrorSMode() //we should call this in main to print the several generations using mirror mode
{
  return this->simulateMirror();
}

char GameOfLife::getDonutSMode() //we should call this in main to print the several generations using donut mode
{
  return this->simulateDonut();
}
int GameOfLife::countNeighborsInClassicSMode() // ideally this counts the total X's around each individual array [i][j]
{
  neighborCount = 0;
  //arrayOne = arrayTwo;
  for (int i = 0; i < importedHEIGHT; i++)
  {
    for (int j = 0; j < importedWIDTH; j++) // checks the neighbors!!! hopefully
    {
      if ((arrayOne[i-1][j]) == 'X' || (arrayOne[i-1][j]) == 'x')
      {
        neighborCount++;
        arrayTwo[i-1][j] == arrayOne[i-1][j];
      }
      else if ((arrayOne[i-1][j-1]) == 'X' || (arrayOne[i-1][j-1]) == 'x')
      {
        neighborCount++;
        arrayTwo[i-1][j-1] == arrayOne[i-1][j-1];
      }
      else if ((arrayOne[i][j-1]) == 'X' || (arrayOne[i][j-1]) == 'x')
      {
        neighborCount++;
        arrayTwo[i][j-1] == arrayOne[i][j-1];
      }
      else if ((arrayOne[i+1][j-1]) == 'X' || (arrayOne[i+1][j-1]) == 'x')
      {
        neighborCount++;
        arrayTwo[i+1][j-1] == arrayOne[i+1][j-1];
      }
      else if ((arrayOne[i+1][j]) == 'X' || (arrayOne[i+1][j]) == 'x')
      {
        neighborCount++;
        arrayTwo[i+1][j] == arrayOne[i+1][j];
      }
      else if ((arrayOne[i-1][j+1]) == 'X' || (arrayOne[i-1][j+1]) == 'x')
      {
        neighborCount++;
        arrayTwo[i-1][j+1] == arrayOne[i-1][j+1];
      }
      else if ((arrayOne[i][j+1]) == 'X' || (arrayOne[i][j+1]) == 'x')
      {
        neighborCount++;
        arrayTwo[i][j+1] == arrayOne[i][j+1];
      }
      else if ((arrayOne[i+1][j+1]) == 'X' || (arrayOne[i+1][j+1]) == 'x')
      {
        neighborCount++;
        arrayTwo[i+1][j+1] == arrayOne[i+1][j+1];
      }
    }
  }

}

void GameOfLife::simulateClassic(){ // starts changing the pointer array based on how many neighbors we counted previously
  // got the info for changing array contents from https://stackoverflow.com/questions/13295011/altering-the-values-of-array-elements-from-within-a-function
  // helpful info found at https://stackoverflow.com/questions/879603/remove-an-array-element-and-shift-the-remaining-ones and
  // https://codescracker.com/cpp/program/cpp-program-delete-element-from-array.htm
  for (int i = 0; i < importedHEIGHT; i++)
  {
    for (int j = 0; j < importedWIDTH; j++)
    {
      if (neighborCount <= 1) // if 1 or no neighbors, that position will have a '-'
      {
        arrayTwo[i][j] = '-';
      }
      else if (neighborCount == 2) // if 2 neighbors, that position will stay the same
      {
        arrayTwo[i][j]=arrayOne[i][j];
      }
      else if (neighborCount == 3) // if 3 neighbors, that position will have a 'X'
      {
        arrayTwo[i][j] == 'X';
      }
      else if (neighborCount == 4) // if 4 neighbors, that position will have a '-'
      {
        arrayTwo[i][j] = '-';
      }
    }
  }
  arrayTwo = arrayOne; // resets the second array to the cells that were just changed above
  // got infor for assigning arrays to one another at https://stackoverflow.com/questions/23850656/assigning-one-array-to-another-array-c
}

void GameOfLife::countNeighborsInMirrorSMode() // ideally this counts the total X's around each individual array [i][j], utilizing the mirrored function for bordered cells
{
  int neighborCountMir = 0;
  for (int i = 0; i < importedHEIGHT; i++)
  {
    for (int j = 0; j < importedWIDTH; j++)
    {
      if (arrayOne[i][importedWIDTH-1]== 'X'|| arrayOne[i][importedWIDTH-1]== 'x') // right side mirrored cells
      {
        neighborCountMir++;
        if (arrayOne[i+1][importedWIDTH-1] == 'X' || arrayOne[i+1][importedWIDTH-1] == 'x')
        {
          neighborCountMir+=2;
        }
        if (arrayOne[i-1][importedWIDTH-1] == 'X' || arrayOne[i-1][importedWIDTH-1] == 'x')
        {
          neighborCountMir+=2;
        }
      }
      if (arrayOne[i][0]== 'X'|| arrayOne[i][0]== 'x') // left side of mirrored cells
      {
        neighborCountMir++;
        if (arrayOne[i+1][0]== 'X'|| arrayOne[i+1][0]== 'x')
        {
          neighborCountMir+=2;
        }
        if (arrayOne[i-1][0]== 'X'|| arrayOne[i-1][0]== 'x')
        {
          neighborCountMir+=2;
        }
      }
      if (arrayOne[0][i]== 'X'|| arrayOne[0][i]== 'x') // top side of mirrored cells
      {
        neighborCountMir++;
        if (arrayOne[0][i+1]== 'X'|| arrayOne[0][i+1]== 'x')
        {
          neighborCountMir+=2;
        }
        if (arrayOne[0][i-1]== 'X'|| arrayOne[0][i-1]== 'x')
        {
          neighborCountMir+=2;
        }
      }
      if (arrayOne[importedHEIGHT-1][i]== 'X'|| arrayOne[importedHEIGHT-1][i]== 'x') // bottom side of mirrored cells
      {
        neighborCountMir++;
        if (arrayOne[importedHEIGHT-1][i+1]== 'X'|| arrayOne[importedHEIGHT-1][i+1]== 'x')
        {
          neighborCountMir+=2;
        }
        if (arrayOne[importedHEIGHT-1][i-1]== 'X'|| arrayOne[importedHEIGHT-1][i-1]== 'x')
        {
          neighborCountMir+=2;
        }
      }


      while (arrayOne[i][j] != arrayOne[importedHEIGHT-1][j] || arrayOne[i][j] != arrayOne[i][importedWIDTH-1] || arrayOne[i][j] != arrayOne[0][j] || arrayOne[i][j] != arrayOne[i][0])
      { // this counts the neighbors if the cells are NOT on the border (normal)
        if ((arrayOne[i-1][j]) == 'X' || (arrayOne[i-1][j]) == 'x')
        {
          neighborCountMir++;
          arrayTwo[i-1][j] == arrayOne[i-1][j];
        }
        else if ((arrayOne[i-1][j-1]) == 'X' || (arrayOne[i-1][j-1]) == 'x')
        {
          neighborCountMir++;
          arrayTwo[i-1][j-1] == arrayOne[i-1][j-1];
        }
        else if ((arrayOne[i][j-1]) == 'X' || (arrayOne[i][j-1]) == 'x')
        {
          neighborCountMir++;
          arrayTwo[i][j-1] == arrayOne[i][j-1];
        }
        else if ((arrayOne[i+1][j-1]) == 'X' || (arrayOne[i+1][j-1]) == 'x')
        {
          neighborCountMir++;
          arrayTwo[i+1][j-1] == arrayOne[i+1][j-1];
        }
        else if ((arrayOne[i+1][j]) == 'X' || (arrayOne[i+1][j]) == 'x')
        {
          neighborCountMir++;
          arrayTwo[i+1][j] == arrayOne[i+1][j];
        }
        else if ((arrayOne[i-1][j+1]) == 'X' || (arrayOne[i-1][j+1]) == 'x')
        {
          neighborCountMir++;
          arrayTwo[i-1][j+1] == arrayOne[i-1][j+1];
        }
        else if ((arrayOne[i][j+1]) == 'X' || (arrayOne[i][j+1]) == 'x')
        {
          neighborCountMir++;
          arrayTwo[i][j+1] == arrayOne[i][j+1];
        }
        else if ((arrayOne[i+1][j+1]) == 'X' || (arrayOne[i+1][j+1]) == 'x')
        {
          neighborCountMir++;
          arrayTwo[i+1][j+1] == arrayOne[i+1][j+1];
        }
      }
    }
  }
}

void GameOfLife::simulateMirror(){ // starts changing the pointer array based on how many neighbors we counted previously (utilizing the Mirrored Cell Mode)
  for (int i = 0; i < importedHEIGHT; i++) //
  {
    for (int j = 0; j < importedWIDTH; j++)
    {
      if (neighborCountMir <= 1)
      {
        arrayTwo[i][j] == '-';
      }
      else if (neighborCountMir == 2)
      {
        if ((arrayOne[i][j]) != 'X')
        {
          arrayTwo[i][j] == '-'; // nothing will happen if its not empty (stay the same)
        }
        else if (!isEmpty(arrayOne[i][j])
        {
          arrayTwo[i][j] == 'X';
        }
      }
      else if (neighborCountMir == 3)
      {
        arrayTwo[i][j] == 'X';
      }
      else if (neighborCountMir == 4)
      {
        arrayTwo[i][j] == '-';
      }
    }
  }
  arrayTwo* == arrayOne; // resets the second array to the cells that were just changed above
}

void GameOfLife::countNeighborsInDonutSMode()
{
  int neighborCountDon = 0;
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      while (arrayOne[i][j] != arrayOne[importedHEIGHT-1][j] || arrayOne[i][j] != arrayOne[i][importedWIDTH-1] || arrayOne[i][j] != arrayOne[0][j] || arrayOne[i][j] != arrayOne[i][0])
      { // ideally this loop goes through and cheks all of the neighbors if they loop around like a donut
        // this first one checks the cells and counts the neighbors that are not located on the border
        if ((arrayOne[i-1][j]) == 'X' || (arrayOne[i-1][j]) == 'x')
        {
          neighborCountDon++;
          arrayTwo[i-1][j] == arrayOne[i-1][j];
        }
        else if ((arrayOne[i-1][j-1]) == 'X' || (arrayOne[i-1][j-1]) == 'x')
        {
          neighborCountDon++;
        arrayTwo[i-1][j-1] == arrayOne[i-1][j-1];
        }
        else if ((arrayOne[i][j-1]) == 'X' || (arrayOne[i][j-1]) == 'x')
        {
          neighborCountDon++;
          arrayTwo[i][j-1] == arrayOne[i][j-1];
        }
        else if ((arrayOne[i+1][j-1]) == 'X' || (arrayOne[i+1][j-1]) == 'x')
        {
          neighborCountDon++;
          arrayTwo[i+1][j-1] == arrayOne[i+1][j-1];
        }
        else if ((arrayOne[i+1][j]) == 'X' || (arrayOne[i+1][j]) == 'x')
        {
          neighborCountDon++;
          arrayTwo[i+1][j] == arrayOne[i+1][j];
        }
        else if ((arrayOne[i-1][j+1]) == 'X' || (arrayOne[i-1][j+1]) == 'x')
        {
          neighborCountDon++;
          arrayTwo[i-1][j+1] == arrayOne[i-1][j+1];
        }
        else if ((arrayOne[i][j+1]) == 'X' || (arrayOne[i][j+1]) == 'x')
        {
          neighborCountDon++;
          arrayTwo[i][j+1] == arrayOne[i][j+1];
        }
        else if ((arrayOne[i+1][j+1]) == 'X' || (arrayOne[i+1][j+1]) == 'x')
        {
          neighborCountDon++;
          arrayTwo[i+1][j+1] == arrayOne[i+1][j+1];
        }
      }
    }
  }
  for (int i = 0; i < importedHEIGHT; i++) // this loop checked for all right corner cells
  {
    for (int j = 0; j < importedWIDTH; j++)
    {
      if (arrayOne[i][importedWIDTH-1] == 'X' || arrayOne[i][importedWIDTH-1] == 'x')
      {
        if (arrayOne[i+1][0] == 'X' || arrayOne[i+1][0] == 'x')
        {
          neighborCountDon++;
        }
        else if (arrayOne[i][0] == 'X' || arrayOne[i][0] == 'x')
        {
          neighborCountDon++;
        }
        else if (arrayOne[i-1][0] == 'X' || arrayOne[i-1][0] == 'x')
        {
          neighborCountDon++;
        }
      }
    }
  }
  for (int i = 0; i < importedHEIGHT; i++) // this loop checked for all left corner cells
  {
    for (int j = 0; j < importedWIDTH; j++)
    {
      if (arrayOne[i][0] == 'X' || arrayOne[i][0] == 'x')
      {
        if (arrayOne[i-1][importedWIDTH-1] == 'X' || arrayOne[i-1][importedWIDTH-1] == 'x')
        {
          neighborCountDon++;
        }
        else if (arrayOne[i][importedWIDTH-1] == 'X' || arrayOne[i][importedWIDTH-1] == 'x')
        {
          neighborCountDon++;
        }
        else if (arrayOne[i+1][importedWIDTH-1] == 'X' || arrayOne[i+1][importedWIDTH-1] == 'x')
        {
          neighborCountDon++;
        }
      }
    }
  }
  for (int i = 0; i < importedHEIGHT; i++) // this loop checked for all top corner cells
  {
    for (int j = 0; j < importedWIDTH; j++)
    {
      if (arrayOne[0][i] == 'X' || arrayOne[0][i] == 'x')
      {
        if (arrayOne[importedHEIGHT-1][i] == 'X' || arrayOne[importedHEIGHT-1][i] == 'x')
        {
          neighborCountDon++;
        }
        else if (arrayOne[importedHEIGHT-1][i-1] == 'X' || arrayOne[importedHEIGHT-1][i-1] == 'x')
        {
          neighborCountDon++;
        }
        else if (arrayOne[importedHEIGHT-1][i+1] == 'X' || arrayOne[importedHEIGHT-1][i+1] == 'x')
        {
          neighborCountDon++;
        }
      }
    }
  }
  for (int i = 0; i < importedHEIGHT; i++) // this loop checked for all bottom corner cells
  {
    for (int j = 0; j < importedWIDTH; j++)
    {
      if (arrayOne[importedHEIGHT-1][i] == 'X' || arrayOne[importedHEIGHT-1][i] == 'x')
      {
        if (arrayOne[0][i] == 'X' || arrayOne[0][i] == 'x')
        {
          neighborCountDon++;
        }
        else if (arrayOne[0][i-1] == 'X' || arrayOne[0][i-1] == 'x')
        {
          neighborCountDon++;
        }
        else if (arrayOne[0][i+1] == 'X' || arrayOne[0
        ][i+1] == 'x')
        {
          neighborCountDon++;
        }
      }
    }
  }
}

void GameOfLife::simulateDonut(){ // starts changing the pointer array based on how many neighbors we counted previously
  for (int i = 0; i < importedHEIGHT; i++)
  {
    for (int j = 0; j < importedWIDTH; j++)
    {
      if (neighborCountDon <= 1)
      {
        arrayTwo[i][j] == '-';
      }
      else if (neighborCountDon == 2)
      {
        if (isEmpty(arrayOne[i][j])
        {
          arrayTwo[i][j] == '-'; // nothing will happen if its not empty (stay the same)
        }
        else if (!isEmpty(arrayOne[i][j])
        {
          arrayTwo[i][j] == 'X';
        }
      }
      else if (neighborCountDon == 3)
      {
        arrayTwo[i][j] == 'X';
      }
      else if (neighborCountDon == 4)
      {
        arrayTwo[i][j] == '-';
      }
    }
  }
  arrayTwo* == arrayOne; // resets the second array to the cells that were just changed above
  }
