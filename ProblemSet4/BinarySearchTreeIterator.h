#pragma once
#include <stack>
#include "BNode.h"
template<typename T>
class BinarySearchTreeIterator
{
private:
    const BNode<T>* fBNodeTree; // binary search tree
    std::stack<const BNode<T>*> fStack; // DFS traversal stack
public:
    using Iterator = BinarySearchTreeIterator<T>;
    BinarySearchTreeIterator( const BNode<T>* aBNodeTree)   //Constructor
    {
        fBNodeTree = aBNodeTree;
        if(!fBNodeTree->empty())        //We cannot construct with an empty tree
        {
            const BNode<T>* lCurrNode  =  fBNodeTree;   //Create  a copy of the root node
            //Decend from the root  along the left to the left most node
            while (!lCurrNode->empty())
            {
                fStack.push(lCurrNode); //Push the nodes from the leaf to the left most node
                if (lCurrNode->left->empty())
                {
                    break;//Break the loop when reaches the left most node
                }
                lCurrNode = lCurrNode->left;  //Assign new left child node to the current node
            }
        }
    }
    //Dereference operator return the key value of the node
    const T& operator*() const
    {
        return fStack.top()->key;
    }
    //Prefix Increment
    Iterator& operator++()
    {
        const BNode<T>* lCurrNode = fStack.top(); //Create a copy of the top node in the stack
        fStack.pop();
        if(!lCurrNode->right->empty())//Inspect the right node
        {
            lCurrNode= lCurrNode ->right;//Decend to the right node
            while (!lCurrNode->empty())
            {
                fStack.push(lCurrNode);  //Push the right node to the current stack
                if (lCurrNode->left->empty()) //Inspect the left node of the current node
                {
                    break; //Breake the loope when it reaches the left most node of the current node
                }
                lCurrNode = lCurrNode->left; //Decend to the left node of the current node
            }
        }
        if (fStack.empty())
        {
            fStack.push(&BNode<T>::NIL); //In case the stack is empty push a empty node onto the stack
        }
        return *this; 
    }
    //Post-fix increment
    Iterator operator++(int)
    {
        Iterator lTemp = *this;
        ++(*this);
        return lTemp;
    }
    //Iterator equivalence by comparing the key of the node in the tree
    bool operator==( const Iterator& aOtherIter ) const
    {
        return **this == aOtherIter.fBNodeTree->key;
    }
    //Iterator inequality
    bool operator!=( const Iterator& aOtherIter ) const
    {
        return !(*this == aOtherIter);
    }
    //Auxilary methods
    Iterator begin() const
    {
        return Iterator(fBNodeTree);
    }
    Iterator end() const
    {
        return Iterator(&BNode<T>::NIL);
    }
};