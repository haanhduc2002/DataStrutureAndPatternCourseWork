#pragma once
class Combination
{
private:
    unsigned int fN;
    unsigned int fK;
public:
    Combination(unsigned int aN, unsigned int aK)
    {
        fN = aN;
        fK = aK;
    };
    unsigned int getN() const
    {
        return fN;
    }
    unsigned int getK() const
    {
        return fK;
    }
    long long operator()() const
    {
        long long combination = 1.0;
        for(int i = 1; i <= fK; i++)
        {
            //Applying with n is fN and k i run from 0 -> k-1
            //  n    (n-0)  (n-1)           (n - (k - 1))
            // ( ) = ----- * ----- * ….... * -------------
            //  k       1       2                   k
            combination *= (fN - (i - 1.0)) / i;  
        }
        return combination;
    }
};
