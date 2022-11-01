#include "IntVector.h"
#include "IntSorter.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// constructor provide in the document
IntVector::IntVector( const int aArrayOfIntegers[], size_t aNumberOfElements )
{
fNumberOfElements = aNumberOfElements;
fElements = new int[fNumberOfElements];
for ( size_t i = 0; i < fNumberOfElements; i++ )
{
    fElements[i] = aArrayOfIntegers[i];
}
}
// deconstructor
IntVector::~IntVector()
{
    delete[] fElements;
}
// return the size of the int vector
size_t IntVector::size() const
{
    return fNumberOfElements;
}
// swap between two element in different index
void IntVector::swap(size_t aSourceIndex, size_t aTargetIndex)
{
if ((aSourceIndex < fNumberOfElements)&&(aTargetIndex < fNumberOfElements))
{
    int temp  = fElements[aSourceIndex];   // store the copy of the element a the source index
    fElements[aSourceIndex] =fElements[aTargetIndex];
    fElements[aTargetIndex] = temp;
}
throw out_of_range("Invalid indices"); // exception handling   
}
// take a callable object of type IntSort and perform in-place sorting define by the object
void IntVector::sort(const IntSorter& aSorter)
{
    aSorter(*this);
}
// return the element in the given index
const int IntVector::operator[] (size_t aIndex) const
{
    if((aIndex < fNumberOfElements))
    {
      return fElements[aIndex]; 
    }   
    throw out_of_range("Invalid index"); // exception handling
}
//auxiliary methods
IntVectorIterator IntVector::begin() const
{
    return IntVectorIterator(*this);
}

IntVectorIterator IntVector::end() const
{
    return IntVectorIterator(*this, fNumberOfElements);
}
