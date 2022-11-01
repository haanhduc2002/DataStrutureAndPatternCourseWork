#pragma once

#include <iostream>
#include <limits>

using namespace std;

#define NUMBEROFBRANCH  3   //Number of coloums
#define NUMBEROFMODEL  4    //Number of rows

//String for output
string BRANCH_NAME[3] =  {"SJ","PJ", "KL"};
string MODEL_NAME[4] ={"RS Pro with GPS","Transcend Drive Pro", "H203 1080P","Pioneer"};

//For calculating sales figure
int MODEL_PRICE[4] = {730, 850, 150, 350};

class SalesCalculator
{
private:
    int fUnitSold[NUMBEROFMODEL][NUMBEROFBRANCH] = {};
    int fGrossSale[NUMBEROFBRANCH] = {};
    int fModelSold[NUMBEROFMODEL] = {};
public:
    SalesCalculator();                                   //Constructor

    void calculateResult();                                //Calculate branches sale figure by RM and model sold by unit

    int getHighestValuePosition(int aArr[], const int& aSize);

    void displayResult();                                  //Display program output

    //Create item from input stream
    friend istream& operator>> (istream& aIStream, SalesCalculator& aSaleCalculator);
};
