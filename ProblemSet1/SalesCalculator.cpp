#include "SalesCalculator.h"

SalesCalculator::SalesCalculator(){}

void SalesCalculator::calculateResult()
{
     for(int i = 0; i < NUMBEROFMODEL; i++)                 //i for rows, for each row do
    {
      for(int j = 0; j < NUMBEROFBRANCH; j++)              //j for colums for each column do
      {
        fModelSold[i] += fUnitSold[i][j];                  //Number of a model sold = sum of cells in 1 row
        fGrossSale[j] += fUnitSold[i][j] * MODEL_PRICE[i]; //Gross sale of a branch = sum of cells in 1 columns
      }
    }
}

int SalesCalculator::getHighestValuePosition(int aArr[], const int& aSize)
{
  int temp = aArr[0];                                  //Store the first element in array in a temporary variable to compare
  int result = 0;                                      //Use to store the index of the highest value
  for(int x = 0; x < aSize ;x++)                       //Compare each element in array and store the highest value position in result
    {
      if(aArr[x]> temp)
        {
          temp = aArr[x];
          result = x;
        }
    }
  return result;
}
void SalesCalculator::displayResult()
{
  calculateResult();                                  //Calculate the input
  for(int j = 0; j < NUMBEROFBRANCH; j++)             // Print gross sale of each branch
  {
    cout<<"The gross sale for Branch "<< BRANCH_NAME[j]<<" is: RM "<< fGrossSale[j]<<endl;
  }
  cout<<endl;
  //Print the highest sale figure and most popular model
  int temp = getHighestValuePosition(fGrossSale, NUMBEROFBRANCH); //Use temporary variable to store the index of the highest value in fGrossSale
  cout<<"The highest sales figure is RM "<<fGrossSale[temp]<<" by Branch "<<BRANCH_NAME[temp]<<endl;
  temp = getHighestValuePosition(fModelSold, NUMBEROFMODEL);      //Use temporary variable to store the index of the highest value in fModelSold
  cout<<"The most popular dash cam model is "<<MODEL_NAME[temp]<<" with unit sold of "<<fModelSold[temp]<<" units."<<endl;
}
istream& operator>> (std::istream& aIStream, SalesCalculator& aSaleCalculator)
{
  for(int i = 0; i < NUMBEROFMODEL; i++)                              //For eacho rows
  {
      cout<<"Number of model" <<MODEL_NAME[i]<<" sold:"<<endl;
      for(int j = 0; j < NUMBEROFBRANCH; j++)                         //For each columns
      {
          cout<<"- In "<<BRANCH_NAME[j]<<":"<<endl;
          while (!(aIStream >> aSaleCalculator.fUnitSold[i][j])||(aSaleCalculator.fUnitSold[i][j] < 0)) //Validate for only positive integer
          {
            cout<<"Invalid input. Please enter the value again"<<endl;//Error message
            aIStream.clear();
            aIStream.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //extract and discord the invalid sequence
          }
      }
  }
  return aIStream;
}
