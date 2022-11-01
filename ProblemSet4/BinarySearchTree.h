#pragma once
#include "BNode.h"
template<typename T>
class BinarySearchTreeIterator;
template<typename T>
class BinarySearchTree
{
private:
    BNode<T>* fRoot;
public:
    using Iterator = BinarySearchTreeIterator<T>;

    BinarySearchTree():fRoot(&BNode<T>::NIL){}  //Constructor
    ~BinarySearchTree(){delete fRoot;}          //Deconstructor

    bool empty() const{return fRoot->empty();}  //Check for empty tree

    bool insert( const T& aKey )
    {
        //Assign value for empty tree
        if (fRoot->empty())
        {
            fRoot = new BNode<T> (aKey);
            return true;
        }
        //Make use  of the  insert function in BNode
        return fRoot->insert(aKey);
    }
    //Remove the node contain the aKey
    bool remove( const T& aKey )
    {
        if(empty())
        {
            throw std::underflow_error("Empty tree");
        }
        //Reuse the code from BNode
        return this->fRoot->remove(aKey);
    }
    //Calculate the height of the tree
    size_t height() const
    {
        if (empty())
        {
            throw std::domain_error("Empty tree");
        }
        else
        {
            return fRoot->height();
        }
    }
    //Auxilary methods
    Iterator begin() const
    {
        return Iterator(fRoot).begin();
    }
    Iterator end() const
    {
        return Iterator(fRoot).end();
    }
};