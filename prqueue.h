#pragma once

#include <iostream>  // For debugging
#include <sstream>   // For as_string

using namespace std;

template <typename T>
class prqueue
{
   private:
    struct NODE {
        int priority;
        T value;
        NODE* parent;
        NODE* left;
        NODE* right;
        NODE* link;
    };

    NODE* root;
    size_t sz;
    NODE* curr;

   public:
    /// Creates an empty `prqueue`.
    ///
    /// Runs in O(1).
    prqueue()
    {
        root = nullptr;
        sz = 0;
    }

    //copy constructor helper
    void copyHelper(NODE* currNode)
    {
        if (currNode == nullptr)
            return;
        
        //copy current
        enqueue(currNode->value, currNode->priority);
        //copy left
        copyHelper(currNode->left);
        //copy right
        copyHelper(currNode->right);
        //link
        copyHelper(currNode->link);
        
    }

    /// Copy constructor.
    ///
    /// Copies the value-priority pairs from the provided `prqueue`.
    /// The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N), where N is the number of values in `other`.
    prqueue(const prqueue& other)
    {
        //makes sure youre copying a different node
        if (this == &other)
        {
            root = nullptr;
            sz = 0;
            return;
        }
        root = nullptr;
        sz = 0;
        copyHelper(other.root);
    }

    /// Assignment operator; `operator=`.
    ///
    /// Clears `this` tree, and copies the value-priority pairs from the
    /// provided `prqueue`. The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N + O), where N is the number of values in `this`, and O is
    /// the number of values in `other`.
    prqueue& operator=(const prqueue& other)
    {
        if (this == &other)
            return *this;
        clear();
        root = nullptr;
        sz = 0;
        copyHelper(other.root);
        return *this;
    }


    //clear helper function
    void _clearHelper(NODE* currNode)
    {
        if (currNode == nullptr)
            return;

        //clear left
        _clearHelper(currNode->left);

        //clear right
        _clearHelper(currNode->right);

        //Delete the linked nodes
        while (currNode->link != nullptr)
        {
            NODE* tmpCurr = currNode->link;
            delete currNode;
            currNode = tmpCurr;
        }

        //Delete the current node
        delete currNode;
    }


    /// Empties the `prqueue`, freeing all memory it controls.
    ///
    /// Runs in O(N), where N is the number of values.
    void clear()
    {
        _clearHelper(root);
        root = nullptr;
        sz = 0;
    }

    /// Destructor, cleans up all memory associated with `prqueue`.
    ///
    /// Runs in O(N), where N is the number of values.
    ~prqueue()
    {
        clear();
    }

    /// Adds `value` to the `prqueue` with the given `priority`.
    ///
    /// Uses the priority to determine the location in the underlying tree.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    void enqueue(T value, int priority)
    {
        //creating toQue
        NODE* toQue = new NODE;
        toQue->priority = priority;
        toQue->value = value;
        toQue->parent = nullptr;
        toQue->left = nullptr;
        toQue->right = nullptr;
        toQue->link = nullptr;
        sz++;
        //handles if the new node is the only node
        if (root == nullptr)
        {
            root = toQue;
            return;
        }
        //iterates through the tree
        NODE* tmpRoot = root;
        while (tmpRoot != nullptr)
        {
            if (toQue->priority < tmpRoot->priority)
            {
                //if the priority is lower insert if possible otherwise go left
                if (tmpRoot->left == nullptr)
                {
                    tmpRoot->left = toQue;
                    toQue->parent = tmpRoot;
                    return;
                }
                else
                    tmpRoot = tmpRoot->left;
            }
            else if (toQue->priority > tmpRoot->priority)
            {
                //if the priority is higher insert if possible otherwise go right
                if (tmpRoot->right == nullptr)
                {
                    tmpRoot->right = toQue;
                    toQue->parent = tmpRoot;
                    return;
                }
                else
                    tmpRoot = tmpRoot->right;
            }
            else
            {
                //if the priority is the same, link it to the end
                while (tmpRoot->link != nullptr)
                    tmpRoot = tmpRoot->link;
                tmpRoot->link = toQue;
                toQue->parent = tmpRoot;
                return;
            }
        }
    }

    /// Returns the value with the smallest priority in the `prqueue`, but does
    /// not modify the `prqueue`.
    ///
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T peek() const
    {
        //handles if there are no nodes
        if (sz == 0 || root == nullptr)
            return T();

        //goes to the leftmost node and returns the value
        NODE* tmpNode = root;
        while (tmpNode->left != nullptr)
            tmpNode = tmpNode->left;
        return tmpNode->value;
    }

    /// Returns the value with the smallest priority in the `prqueue` and
    /// removes it from the `prqueue`.
    ///
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T dequeue()
    {
        T retVal;
        //checks if tree is empty
        if (sz == 0)
            return T();
        sz--;
        //if the left side is empty delete root and change pointers
        if (root->left == nullptr)
        {
            retVal = root->value;
            //if there IS a linked list to the node
            if (root->link != nullptr)
            {
                NODE* chainedNode = root->link;
                //copy the nodes attributes
                chainedNode->right = root->right;
                //change the childrens parents to the correct node
                if (chainedNode->right != nullptr)
                    chainedNode->right->parent = chainedNode;
                //replace the node with the chainedNode
                delete root;
                root = chainedNode;
                chainedNode->parent = nullptr;
                return retVal;
            }
            if (root->right != nullptr) // if there are nodes on the right, rewire pointers
            {
                NODE* tmpNode = root->right;
                tmpNode->parent = nullptr;
                delete root;
                root = tmpNode;
            }
            else // if the right side is ALSO empty just delete root
            {
                delete root;
                root = nullptr;
            }
            return retVal;
        }
        NODE* tmpNode = root;
        //stops at the second to last leftmost node
        while (tmpNode->left->left != nullptr)
            tmpNode = tmpNode->left;
        retVal = tmpNode->left->value;
        //once again if this node has a linked list
        if (tmpNode->left->link != nullptr)
        {
            NODE* chainedNode = tmpNode->left->link;
            //copy the nodes attributes
            chainedNode->left = tmpNode->left->left;
            chainedNode->right = tmpNode->left->right;
            chainedNode->parent = tmpNode;
            //change the childrens parents to the correct node
            if (chainedNode->left != nullptr)
                chainedNode->left->parent = chainedNode;
            if (chainedNode->right != nullptr)
                chainedNode->right->parent = chainedNode;
            //replace the node with the chainedNode
            delete tmpNode->left;
            tmpNode->left = chainedNode;
            return retVal;
        }

        //if there is a right child rewire that node
        if (tmpNode->left->right != nullptr)
        {
            NODE* tmpRight = tmpNode->left->right;
            delete tmpNode->left;
            tmpNode->left = tmpRight;
            tmpRight->parent = tmpNode;
            //replace the right nodes parent pointer if its a list
            while (tmpRight->link != nullptr)
            {
                tmpRight = tmpRight->link;
                tmpRight->parent = tmpNode;
            }
        }
        else // if there is no right child just delete
        {
            delete tmpNode->left;
            tmpNode->left = nullptr;
        }
        return retVal;
    }

    /// Returns the number of elements in the `prqueue`.
    ///
    /// Runs in O(1).
    size_t size() const
    {
        return sz;
    }

    /// Resets internal state for an iterative inorder traversal.
    ///
    /// See `next` for usage details.
    ///
    /// O(H), where H is the maximum height of the tree.
    void begin()
    {
        //locates the leftmost node
        curr = root;
        if (curr != nullptr)
            while (curr->left != nullptr)
                curr = curr->left;
        
    }

    /// Uses the internal state to return the next in-order value and priority
    /// by reference, and advances the internal state. Returns true if the
    /// reference parameters were set, and false otherwise.
    /// Runs in worst-case O(H + M) or O(H), depending on implementation, where
    /// H is the height of the tree, and M is the number of duplicate
    /// priorities.
    bool next(T& value, int& priority)
    {
        //checks if reference parameteres were set
        if (curr == nullptr)
            return false;

        //updates value and priority
        value = curr->value;
        priority = curr->priority;
        //moves to the next link if possible
        if (curr->link != nullptr)
        {
            curr = curr->link;
            return true;
        }

        // if we need to start moving back
        if (curr->link == nullptr && curr->parent != nullptr && curr->parent->priority == curr->priority)
            while (curr->parent != nullptr && curr->parent->priority == curr->priority)
                curr = curr->parent;
        

        if (curr->right != nullptr)//checks the right child
        {
            //moves to the right branch and finds the leftmost node
            curr = curr->right;
            while (curr->left != nullptr)
                curr = curr->left;
        }
        else //checks the left child
        {
            //traverse up the tree until a parent with greater priority is reached or is nullptr
            while(curr->parent != nullptr && curr->priority > curr->parent->priority)
                curr = curr->parent;
            //move up one more node
            curr = curr->parent;
        }
        return true;
    }


    //as_string helper function
    void _recursiveHelper(NODE* node, ostream& output) const
    {
        if (node == nullptr)
            return;

        //Go left
        _recursiveHelper(node->left, output);
        //Add to the output
        output << node->priority << " value: " << node->value << endl;
        //if the node has links then add those too
        NODE* tmpNode = node->link;
        while(tmpNode != nullptr)
        {
            output << tmpNode->priority << " value: " << tmpNode->value << endl;
            tmpNode = tmpNode->link;
        }
        //Go right
        _recursiveHelper(node->right, output);
    }

    /// Converts the `prqueue` to a string representation, with the values
    /// in-order by priority.
    ///
    /// Runs in O(N), where N is the number of values.
    string as_string() const
    {
        ostringstream output;
        _recursiveHelper(root, output);
        return output.str();
    }

    /// Checks if the contents of `this` and `other` are equivalent.
    ///
    /// Two `prqueues` are equivalent if they have the same priorities and
    /// values, as well as the same internal tree structure.
    /// Runs in O(N) time, where N is the maximum number of nodes in
    /// either `prqueue`.
    ///
    //copy constructor helper
    bool compareHelper(const NODE* thisCurrNode, const NODE* otherCurrNode) const
    {
        //base cases
        if (thisCurrNode == nullptr && otherCurrNode == nullptr)
            return true;
        if (thisCurrNode == nullptr || otherCurrNode == nullptr)
            return false;

        //compare left
        bool left = compareHelper(thisCurrNode->left, otherCurrNode->left);
        //compare right
        bool right = compareHelper(thisCurrNode->right, otherCurrNode->right);
        //compare the linked list linked list
        bool list = compareHelper(thisCurrNode->link, otherCurrNode->link);

        //comparing current
        if (thisCurrNode->value != otherCurrNode->value || thisCurrNode->priority != otherCurrNode->priority)
            return false;
        
        return left && right && list;
    }

    bool operator==(const prqueue& other) const
    {
        return compareHelper(root, other.root);
    }

    /// Returns a pointer to the root node of the BST.
    ///
    /// Used for testing the internal structure of the BST. Do not edit or
    /// change.
    ///
    /// Runs in O(1).
    void* getRoot() {
        return root;
    }
};
