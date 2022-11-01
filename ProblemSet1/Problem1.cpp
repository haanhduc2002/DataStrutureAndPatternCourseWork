#include <iostream>
#include "SalesCalculator.cpp"

using namespace std;

int main()
{
    SalesCalculator lSales;
    cout<<"Please enter the data"<<endl;
    cin>>lSales;
    lSales.displayResult();
    return 0;
}