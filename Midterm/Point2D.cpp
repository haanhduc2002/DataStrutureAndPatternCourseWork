#include "Point2D.h"

static const Point2D gCoordinateOrigin;
//Private method
//Return direction of point to aOther
double Point2D::directionTo (const Point2D& aOther) const
{
    return (*this - aOther).direction();
}

//return the length of point to aOther
double Point2D::magnitudeTo (const Point2D& aOther) const
{
    return (*this -aOther).magnitude();
}

//Constructors
Point2D::Point2D()
{
    fId = "";
    fPosition = (0,0);
    fOrigin = &gCoordinateOrigin;
}

Point2D::Point2D(const std::string& aId, double aX, double aY)
{
    fId = aId;
    fPosition = (aX,aY);
    fOrigin = &gCoordinateOrigin;
}

Point2D::Point2D(std::istream& aIStream)
{
    aIStream>>fId>>fPosition;
    fOrigin = &gCoordinateOrigin;
}

//Getters and setters
const std::string& Point2D::getId() const {return fId;}         // Id getter 

void Point2D::setX(const double& aX){fPosition.setX(aX);}       // X setter
const double Point2D::getX() const {return fPosition.getX();}   // X getter

void Point2D::setY(const double& aY){fPosition.setY(aY);}       // Y setter
const double Point2D::getY() const {return fPosition.getY();}   // Y getter

void Point2D::setOrigin(const Point2D& aPoint)                  // Origin getter
{
   fOrigin = &aPoint;
}

const Point2D& Point2D::getOrigin() const                       // Origin setter
{
    return *fOrigin;
}

//Vector 2D this - aRHS
Vector2D Point2D::operator-(const Point2D& aPoint) const
{
    return fPosition - aPoint.fPosition; //reuse the code from Vector2D.h
}

//Direction of point to origin
double Point2D::direction() const
{
    return directionTo(*fOrigin);   
}

//Magnitude of point to origin
double Point2D::magnitude() const
{
    return magnitudeTo(*fOrigin);
}

//Check if this point and aOther are on the sameline
bool Point2D::isCollinear(const Point2D& aOther) const 
{
    double lTemp = (*this - *fOrigin).cross(aOther - *fOrigin); 
    if(( lTemp<0.0001) && (lTemp>-0.0001)) // The deviation is 10^-4
    {
        return true;
    }
    return false;
}

//Check if the line segment this-aP2 make a right turn at this point
bool Point2D::isClockwise(const Point2D& aP0, const Point2D& aP2) const //TODO: Can be improve
{
    if((*this - aP0).cross(aP2 - aP0) > 0)
    {
        return true;
    }
    return false;
}
//Compare 2 vectors
bool Point2D::operator<(const Point2D& aRHS) const
{
    if(fPosition.getY() - aRHS.fPosition.getY() < -0.0001)
    {
        return true;
    }
    else if (abs(fPosition.getY() - aRHS.fPosition.getY()) < 0.0001 && fPosition.getX() - aRHS.fPosition.getX()< -0.0001)
    {
        return true;
    }
    return false;
}
//Input output for 2 vector
std::ostream& operator<<(std::ostream& aOStream, const Point2D& aObject)
{
    aOStream<<aObject.getId()<<": ("<<aObject.getX()<<","<<aObject.getY()<<")";
    return aOStream;
}

std::istream& operator>>(std::istream& aISteam, Point2D& aObject) //TODO: Can be improve
{
    aObject = Point2D(aISteam);
    return aISteam;
}
