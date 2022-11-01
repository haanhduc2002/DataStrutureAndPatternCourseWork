#include "IntVector.h"
#include "IntVectorIterator.h"

#include <iostream>

using namespace std;
// foward iterator constructor
IntVectorIterator::IntVectorIterator(const IntVector& aContainer, size_t aStart):fContainer(aContainer)
{
    fPosition = aStart;
}
// dereference operator
const int IntVectorIterator::operator*() const
{
    return fContainer[fPosition];
}
// prefix increment
IntVectorIterator& IntVectorIterator::operator++()
{
    fPosition++;
    return *this;
}
// Postfix increment
IntVectorIterator IntVectorIterator::operator++(int)
{
    IntVectorIterator temp = *this;
    ++(*this);
    return temp;
}
// iterator equivalence
bool IntVectorIterator::operator==(const IntVectorIterator& aRHS) const
{
    return (fPosition== aRHS.fPosition)&&(&fContainer == &aRHS.fContainer);
}
// iterator inequality
bool  IntVectorIterator::operator!=(const IntVectorIterator& aRHS) const
{
    return !(*this == aRHS); //reuse the iterator equivalence
}
// auxiliary methods
IntVectorIterator IntVectorIterator::begin() const
{
    return IntVectorIterator(fContainer);
}

IntVectorIterator IntVectorIterator::end() const
{
    return IntVectorIterator(fContainer, fContainer.size());
}