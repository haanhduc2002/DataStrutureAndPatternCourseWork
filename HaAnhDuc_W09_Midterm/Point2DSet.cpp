#include "Point2DSet.h"
#include <algorithm>
#include <fstream>

using Iterator = std::vector<Point2D>::const_iterator;

//Comparator
bool orderByCoordinates( const Point2D& aLeft, const Point2D& aRight )
{
  return aLeft<aRight;          //Compare using operator < defined in Point2D
}

bool orderByPolarAngle( const Point2D& aLHS, const Point2D& aRHS )
{
  //In case 2 point are collinear with the orgin point we compare 
  //the lenght of the from both point to the orgin point
  if (aLHS.isCollinear(aRHS))                             
  {
    return aRHS.magnitude()- aLHS.magnitude() >= 0.0001;  //Deviation 10^-4
  }
  //else we compare the direction of the 2 point related to the orginal point
  return aRHS.direction() - aLHS.direction() >= 0.0001;   //Deviation 10^-4
}

// Add a 2D point to set
void Point2DSet::add(const Point2D& aPoint) //Pass in a reference into the parameter
{
  fPoints.push_back(aPoint);
}

void Point2DSet::add(Point2D&& aPoint) //Pass in a rvalue reference
{
  fPoints.push_back(aPoint);
}

//Remove the last point in the set
void Point2DSet::removeLast() 
{
  fPoints.pop_back();
}

//Check if aPoint make a left turn
bool Point2DSet::doesNotTurnLeft(const Point2D& aPoint) const 
{
  return aPoint.isClockwise(fPoints[size()-2],fPoints[size()-1]);
}
//Load points from file
void Point2DSet::populate(const std::string& aFileName)
{
  std::ifstream lInput(aFileName);    //Open file 
  if(lInput.is_open())                //Check if file is open
  {
    size_t lSetSize;
    lInput>>lSetSize;                 //Store the size of the set read from file for the loop 
    Point2D lPoint;                   //Temporary object to store the Point2D
    for(size_t i =0; i < lSetSize;i++)
    {
        lInput >> lPoint;             //Read the new point from file
        add(lPoint);                  //Add new point to point set
    }
    lInput.close();                  //Close file 
  }
}

//Build a convex hull
//fPoints is Q and aConvexHull is S
void Point2DSet::buildConvexHull(Point2DSet& aConvexHull) 
{
  //Sort Q by y-coordinate follow by x-coordinate
  sort(orderByCoordinates);
  //Set to orgin point to be p0-the point in Q with the minimum y-coordinate                            
  for(Point2D& lPoint : fPoints)
  {
    lPoint.setOrigin(fPoints[0]);
  }
  //Sort Q by polar angle in clockwise order around p0
  sort (orderByPolarAngle);
  //Push p0, p1, p2 onto S
  for (size_t i = 0; i < 3; i++)
  {
    //If |Q| <3 stop 
    if(fPoints.size() < 3)
    {
      break;
    }
    //Pusk point to the stack
    aConvexHull.add(fPoints[i]);
  }
  for(size_t i = 3; i < fPoints.size(); i++)
  {
    //the angle form by p[i] and Next-To-Top(S), Top(S) make a non-left turn
    while(aConvexHull.doesNotTurnLeft(fPoints[i]))
    {
      aConvexHull.removeLast(); //Pop(S)
    }
    aConvexHull.add(fPoints[i]); //Push p[i] to S
  }
}

//Return number of element in set
size_t Point2DSet::size() const
{
  return fPoints.size();
}

//Clear set
void Point2DSet::clear()
{
  fPoints.clear();
}

// Sort the set using stable_sort on vectors
void Point2DSet::sort(Comparator aComparator)
{
  std::stable_sort(fPoints.begin(), fPoints.end(),aComparator);
}

// indexer for set
const Point2D& Point2DSet::operator[] (size_t aIndex) const
{
  if(aIndex < fPoints.size()) //Check for invalid index
  {
    return fPoints[aIndex];
  }
  throw std::out_of_range("Invalid point index");
}

//Iterator methods
Iterator Point2DSet::begin() const
{
  return fPoints.begin();
}

Iterator Point2DSet::end() const
{
  return fPoints.end();
}
