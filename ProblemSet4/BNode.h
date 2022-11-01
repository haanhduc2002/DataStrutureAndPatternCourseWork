#pragma once
#include <stdexcept>
template<typename S>
struct BNode
{
    S key;
    BNode<S>* left;
    BNode<S>* right;

    static BNode<S> NIL;    //Empty node

    // The three pre-implemented function 
    const S& findMax() const
    {
        S lMax = key;
        if (!left->empty()) // search left subtree
        { 
            lMax = std::max(lMax, left->findMax());
        }
        if (!right->empty())   // search right subtree
        {
            lMax = std::max(lMax, right->findMax());
        }
        return lMax;
    }
    const S& findMin() const
    {
        S lMin = key;
        if (!left->empty()) // search left subtree
        { 
            lMin = std::min(lMin, left->findMin());
        }
        if (!right->empty())   // search right subtree
        {
            lMin = std::min(lMin, right->findMin());
        }
        return lMin;
    }
    bool remove( const S& aKey, BNode<S>* aParent )
    {
        BNode<S>* t = this;  // t: target subtree where t.key = aKey
        BNode<S>* y = aParent;

        while (!t->empty()) {
            if (aKey == t->key) { // (found it) aKey is in this
            break;
            }

            y = t;  // new parent
            t = (aKey < t->key) ? t->left : t->right;
        }

        if (t->empty()) return false;    // delete failed

        /* assert: 
        aKey = t.key /\ y = t.parent
        */
        if (!t->left->empty()) {  // t is not leaf
        const S& lKey = t->left->findMax(); // find max to left
        t->key = lKey;          // replace t->key by lKey (effectively removing aKey)
        t->left->remove(lKey, t); // remove lKey (recursively)
        } else {  // t is leaf -> remove t
        if (y->left == t) { // y.left = t
            y->left = &NIL;
        } else {  // y.right = t
            y->right = &NIL;
        }
        delete t;
        }
        return true; //delete succeed
    }
    //BNode Constructor
    BNode():key(S()),
            left(&NIL),
            right(&NIL){}
    //BNode L-Value Constructor        
    BNode( const S& aKey ):key(aKey),
                            left(&NIL),
                            right(&NIL){}
    //BNode R-Value Constructor                        
    BNode( S&& aKey ):key(std::move(aKey)),
                        left(&NIL),
                        right(&NIL){}
    //BNode Deconstructor
    ~BNode()
    {
        if (left != &NIL)
        {
            delete left;
        }
        if (right != &NIL)
        {
            delete right;
        }
        
    }
    //Check if node is empty
    bool empty() const
    {
        return this == &NIL;
    }
    // Check for leaf node
    bool leaf() const
    {
        if (left->empty() && right->empty())
        {
            return true;
        }
        return false;
    }
    //Calculate height of the tree
    size_t height() const
    {
        //Stop condition: when the tree is empty
        if (this->empty())
        {
            return -1;
        }
        else
        {
            //Recursion function: continue calculate the height at the node on the left and on the right
            size_t lLeftHeight = left->height();    
            size_t lRightHeight = right->height();
            size_t lResult = std::max(lLeftHeight, lRightHeight) +1 ;
            return lResult;
        }
    }
    //Insert a new node
    bool insert( const S& aKey )
    {
        //We cannot insert a  new node to an empty tree
        if (empty())
        {
            return false;
        }
        BNode<S>* lCurrentNode = this;
        BNode<S>* lTargetNode = &BNode<S>::NIL;
        //if the current node is empty
        
        while (!lCurrentNode->empty())
        {
            lTargetNode = lCurrentNode;
            if (aKey == lCurrentNode->key)
            {
                return  false; //the  current tree already have this value so it can not  be inserted
            }
            //choose a child node by comparing the insert value with current node
            if (aKey< lCurrentNode->key)
            {
               lCurrentNode  =  lCurrentNode->left;
            }
            else
            {
                lCurrentNode  = lCurrentNode->right;
            }
        }
        BNode<S>* lKeyNode = new BNode<S>(aKey);
        //Choose where to insert new node base on its value
        if (aKey < lTargetNode->key)
        {
            lTargetNode->left = lKeyNode;
        }
        else
        {
            lTargetNode->right = lKeyNode;
        }
        return true;
    }
};

template<typename S>
BNode<S>
BNode<S>::NIL;