#include "Vector2D.h"
#include <math.h>

// Constructor
Vector2D::Vector2D(double aX, double aY)
{
    fX = aX;
    fY = aY;
}

//getter and setter for y and y
void Vector2D::setX(double aX){fX = aX;}    // X setter
double Vector2D::getX() const{return fX;}   // X getter
void Vector2D::setY(double aY) {fY = aY;}   // Y setter
double Vector2D::getY() const {return fY;}  // Y getter

//Vector addition
Vector2D Vector2D::operator+(const Vector2D& aRHS) const
{
    Vector2D lResult(fX + aRHS.getX(),fY + aRHS.getY());
    return lResult;
}

//Vector substraction
Vector2D Vector2D::operator-(const Vector2D& aRHS) const
{
    Vector2D lResult(fX - aRHS.getX(),fY - aRHS.getY());
    return lResult;
}

//Return the magnitude of the vector
double Vector2D::magnitude() const {return sqrt(pow(fX,2) + pow(fY,2));}

//Return the angle of 2D vector
double Vector2D::direction() const {return atan2(fY,fX);}

//return inner product of 2 2D vectors
double Vector2D::dot(const Vector2D& aRHS) const
{
    return (fX *aRHS.getX()) + (fY * aRHS.getY());
}

//Return cross product of 2 2D vectors
double Vector2D::cross(const Vector2D& aRHS) const
{
    return (fX * aRHS.getY()) - (fY * aRHS.getX());
}

//Return angle between 2 2D vectors
double Vector2D::angleBetween(const Vector2D& aRHS) const
{
    //Handle null vectors
    if(this->magnitude()==0 || aRHS.magnitude()==0)
    {
        return 0;
    }
    double lResult = acos(this->dot(aRHS)/(this->magnitude() * aRHS.magnitude()));
    return lResult;
}

// Vector2D output
std::ostream& operator<< (std::ostream& aOutStream, const Vector2D& aObject)
{
    aOutStream<<"["<<aObject.getX()<<","<<aObject.getY()<<"]"<<std::endl;
    return aOutStream;
}

//Vector2D input
std::istream& operator>> (std::istream& aInStream, Vector2D& aObject) // TODO: can be improve
{
    aInStream>>aObject.fX>>aObject.fY;
    return aInStream;
}
