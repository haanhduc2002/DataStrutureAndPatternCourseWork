
// COS30008, Doubly-linked Nodes, 2021

#pragma once

template<typename T>
class DoublyLinkedList
{
private:
    
    T fPayload;													// payload
    DoublyLinkedList* fNext;									// next element
    DoublyLinkedList* fPrevious;								// previous element
    
public:
    
	explicit DoublyLinkedList( const T& aPayload ) 			// l-value constructor
	{
		fPayload = aPayload;
		fNext = this;
		fPrevious = this;
	}
	explicit DoublyLinkedList( T&& aPayload ) 					// r-value constructor
    {
		fPayload = std::move(aPayload);
		fNext = this;
		fPrevious = this;
	}
	DoublyLinkedList& push_front( DoublyLinkedList& aNode )		// aNode becomes previous of this
	{
		aNode.fNext = this;
		aNode.fPrevious = fPrevious;
		fPrevious->fNext = &aNode;
		fPrevious = &aNode;
		return aNode;
	}
	DoublyLinkedList& push_back( DoublyLinkedList& aNode )		// aNode becomes next of this    
	{
		aNode.fPrevious = this;
		aNode.fNext = fNext;
		fNext->fPrevious = &aNode;
		fNext = &aNode;
		return aNode;
	}
	void isolate()												// removes this node
	{
		//link fPrevious with fNext
		fNext->fPrevious = fPrevious;
		fPrevious->fNext = fNext;
		//Link the current item to itself
		fNext = this;
		fPrevious = this;
	}
	void swap( DoublyLinkedList& aNode ) 						// exchange payloads
	{
		T ltemp = aNode.fPayload;
		aNode.fPayload = fPayload;
		fPayload = ltemp;
	}

	const T& operator*() const { return getPayload();}                  							// dereference operator, payload
	const T& getPayload() const {return fPayload;}								// returns constant reference to payload

	const DoublyLinkedList& getNext() const {return *fNext;}					// returns constant reference to next
	
	const DoublyLinkedList& getPrevious() const	{return *fPrevious;}			// returns constant reference to previous
};
