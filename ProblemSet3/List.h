
// COS30008, List, Problem Set 3, 2021

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

#include <stdexcept>
using namespace std;
template<typename T>
class List
{
private:
	// auxiliary definition to simplify node usage
	using Node = DoublyLinkedList<T>;

	Node* fRoot;	// the first element in the list
	size_t fCount;	// number of elements in the list

public:
	// auxiliary definition to simplify iterator usage
    using Iterator = DoublyLinkedListIterator<T>;

	~List()                                                             // destructor - frees all nodes
    {
        while ( fRoot != nullptr )
        {
            if ( fRoot != &fRoot->getPrevious() )                       // more than one element
            {
                Node* lTemp = const_cast<Node*>(&fRoot->getPrevious()); // select last
                
                lTemp->isolate();                                       // remove from list
                delete lTemp;                                           // free
            }
            else
            {
                delete fRoot;                                           // free last
                break;                                                  // stop loop
            }
        }
    }

    void remove( const T& aElement )	                                // remove first match from list
    {
        Node* lNode = fRoot;                                            // start at first
        
        while ( lNode != nullptr )                                      // Are there still nodes available?
        {
            if ( **lNode == aElement )                                  // Have we found the node?
            {
                break;                                                  // stop the search
            }

            if ( lNode != &fRoot->getPrevious() )                       // not reached last
            {
                lNode = const_cast<Node*>(&lNode->getNext());           // go to next
            }
            else
            {
                lNode = nullptr;                                        // stop search
            }
        }
        
        // At this point we have either reached the end or found the node.
        if ( lNode != nullptr )                                         // We have found the node.
        {
            if ( fCount != 1 )                                          // not the last element
            {
                if ( lNode == fRoot )
                {
                    fRoot = const_cast<Node*>(&fRoot->getNext());       // make next root
                }
            }
            else
            {
                fRoot = nullptr;                                        // list becomes empty
            }
            
            lNode->isolate();                                           // isolate node
            delete lNode;                                               // release node's memory
            fCount--;                                                   // decrement count
        }
    }

	// PS3 starts here
    
	// P1

	List()                                   							// default constructor
    {
        fRoot = nullptr;
        fCount = 0;
    }

	bool isEmpty() const	                    						// Is list empty?
	{
        return fRoot == nullptr;
    }

    size_t size() const                								// list size
    {
        return fCount;
    }

	void push_front( const T& aElement )	    						// adds aElement at front
    {
        Node* lNewElement = new Node(aElement);
        if (this->isEmpty())                                        //Check for empty list
        {
            fRoot = lNewElement;                                    //The new element will be the first element
        }
        else 
        {
            fRoot = &fRoot->push_front(*lNewElement);               //Reuse the push_front function
        }
        fCount++; //Increase the size of the list  
    }

	Iterator begin() const {return Iterator(fRoot).begin();}                // return a forward iterator	
    Iterator end() const    {return Iterator(fRoot).end();}                 // return a forward end iterator
	Iterator rbegin() const {return Iterator(fRoot).rbegin();}              // return a backwards iterator
	Iterator rend() const   {return Iterator(fRoot).rend();}                // return a backwards end iterator

	// P2

	void push_back( const T& aElement )        						        // adds aElement at back
    {
        Node* lNewElement = new Node(aElement);
        if(this->isEmpty()) //Check for empty list
        {
            fRoot == lNewElement;   //The new element will be the first element
        }
        else
        {
            //The new element will be push_back at the previous element of the root element
            Node& lBackElement = const_cast<Node&>(fRoot->getPrevious());
            lBackElement.push_back(*lNewElement);
        }
        fCount++;  //Increase the size of the list 
    }
	// P3

	const T& operator[]( size_t aIndex ) const							// list indexer
    {
        if( aIndex < this->size())
        {
            Node* lResult = fRoot;
            for(size_t i = 0; i < aIndex; i++)
            {
                lResult = const_cast<Node*>(&lResult->getNext());
            }
            return lResult->getPayload();
        }
        else
        {
            throw std::out_of_range("Invalid index");
        }
    }
	// P4
	
	List( const List& aOtherList )             						// copy constructor
	{
        *this=(aOtherList);                                         //Reuse the code from operator=
    }
    List& operator=( const List& aOtherList )  						// assignment operator
    {
        if(this->isEmpty()) //if the current list is emtpy delete the fRoot and reset count
        {
            this->~List();
            fRoot = nullptr;
            fCount = 0;
        }
        fRoot = aOtherList.fRoot;
        for ( const auto& i : aOtherList)
        {
            push_back(i);
        }
        
        return *this;
    }

	// P5X

	// move features
	List( List&& aOtherList )                 							// move constructor
	{
        *this = aOtherList;
    }
    List& operator=( List&& aOtherList )           						// move assignment operator
	{
        if(this->isEmpty()) //if the current list is emtpy delete the fRoot and reset count
        {
            this->~List();
            fRoot = nullptr;
            fCount = 0;
        }
        fRoot = std::move(aOtherList.fRoot);
        for ( const auto& i : aOtherList)
        {
            push_back(i);
        }
        
        return *this;
    }
    void push_front( T&& aElement )            						// adds aElement at front
	{
        T lNewElement = std::move(aElement);
        this->push_front(lNewElement);
    }
    void push_back( T&& aElement )             						// adds aElement at back
    {
        T lNewElement = std::move(aElement);
        this->push_back(lNewElement);
    }
};
