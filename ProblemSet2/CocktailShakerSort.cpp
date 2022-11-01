#include "IntVector.h"
#include "IntVectorIterator.h"
#include "IntSorter.h"
#include "CocktailShakerSort.h"
// cocktail shaker sort define by IntSorter subclass
void CocktailShakerSort::operator() (IntVector& aContainer) const 
{
    int lStart = 0;                     // first index to check
    int  lEnd = aContainer.size() - 1;  // last index to check

    while(lStart <= lEnd)
    {
        int lNewStart = lEnd;
        int lNewEnd =lStart;
        // loop from left to right
        for(int i= lStart; i < lEnd; i++)
        {
            if(aContainer[i] > aContainer[i+1])
            {
                aContainer.swap(i, i+1);
                lNewEnd = i; // store the sorted element index closest to the right
            }
        }
        // as the index after the new end index has been sorted there is no need through all indices
        lEnd = lNewEnd; 
        // loop from right to left using the similar comparison step
        for(int i =lEnd -1 ; i >= lStart; --i)
        {
            if(aContainer[i] > aContainer[i+1])
            {
                aContainer.swap(i, i+1);
                lNewStart = i; //store the sorted element index closest to the left
            }
        }
        // the element before the new start index are sorted so no need to start from the first index
        lStart = lNewStart ;
    }    
}