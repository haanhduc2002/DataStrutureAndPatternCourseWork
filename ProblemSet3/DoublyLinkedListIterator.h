
// COS30008, Doubly-linked Node Iterator, 2021

#pragma once

#include "DoublyLinkedList.h"

template<typename T>
class DoublyLinkedListIterator
{
private:
	enum class States { BEFORE, DATA , AFTER };					// iterator states

	using Node = DoublyLinkedList<T>;

	const Node* fRoot;											// doubly-linked list

    States fState;												// iterator state
    const Node* fCurrent;										// iterator position
    
public:
    
	using Iterator = DoublyLinkedListIterator<T>;

	DoublyLinkedListIterator( const Node* aRoot )				// constructor
	{
		fRoot = aRoot;
		fCurrent = fRoot;
		if(fCurrent != nullptr)
		{
			fState = States::DATA;
		}
		else
		{
			fState = States::AFTER;
		}
	}
	const T& operator*() const	        						// dereference    
	{
		return **fCurrent;
	}
	Iterator& operator++()										// prefix increment
	{
		switch (fState)
		{
		case States::BEFORE:
			fCurrent = fRoot;
			if(fCurrent == nullptr)
			{
				fState = States::AFTER;
			}
			if(fCurrent != nullptr)
			{
				fState = States::DATA;
			}
			break;
		case States::DATA:
			if(fCurrent == &fRoot->getPrevious())
			{
				fCurrent = nullptr;
				fState = States::AFTER;
			}
			else
			{
				fCurrent = &fCurrent->getNext();
			}
		default:
			break;
		}
		return *this;
	}
	Iterator operator++(int)									// postfix increment
	{
		Iterator ltemp = *this;
		++(*this);
		return ltemp;
	}
	Iterator& operator--()										// prefix decrement
	{
		switch (fState)
		{
		case States::DATA:
			if(fCurrent == fRoot)
			{
				fCurrent = nullptr;
				fState = States::BEFORE;
			}
			else
			{
				fCurrent = &fCurrent->getPrevious();
			}
			break;
		case States::AFTER:
			fCurrent = fRoot;
			if (fCurrent == nullptr)
			{				
				fState = States::BEFORE;
			}
			else
			{
				fCurrent = &fCurrent->getPrevious();
				fState = States::DATA;
			}		
		default:
			break;
		}
		return *this;
	}
	Iterator operator--(int)									// postfix decrement
	{
		Iterator ltemp = *this;
		--(*this);
		return ltemp;
	}
	bool operator==( const Iterator& aOtherIter ) const			// equivalence
	{
		return fRoot==aOtherIter.fRoot && fState == aOtherIter.fState && fCurrent == aOtherIter.fCurrent;
	}
	bool operator!=( const Iterator& aOtherIter ) const		// not equal
	{
		return !(*this == aOtherIter);
	}
	Iterator begin() const										// first element forward
	{
		return ++(rend());
	}
	Iterator end() const										// after last element forward
	{
		Iterator lTemp = *this;
		lTemp.fCurrent = nullptr;
		lTemp.fState = States::AFTER;
		return lTemp;
	}
	Iterator rbegin() const									// first element backwards
	{
		return --(end());
	}
	Iterator rend() const										// before first element backwards
	{
		Iterator lTemp = *this;
		lTemp.fCurrent = nullptr;
		lTemp.fState = States::BEFORE;
		return lTemp;
	}
};
