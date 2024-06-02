/*
 Program Name: main.cpp
 Programmer: Moris Gomez
 Date: Tuesday 05/29/2024
 Version Control: 10.0
 About: Week 15, CSCI 2, HW.
 Description:
 1. Write a member function for the IntBinaryTree 
 class that counts and returns the number of nodes
 in the tree. Demonstrate the function in a driver 
 program.
 
 2. Write a member function for the IntBinaryTree 
 class that counts and returns the number of leaf
 nodes in the tree. Demonstrate the function in a
 driver program.
 */

#include <iostream>
using namespace std;

class IntBinaryTree
{
private:
    struct TreeNode
    {
        int data;
        TreeNode* left;
        TreeNode* right;
    };
    TreeNode* root;
    int countTotalNodes;
    int countLeafNodes;
    
public:
    //default constructor for IntBinaryTree class:
    IntBinaryTree()
    {
        root = NULL;
        countTotalNodes = 0;
        countLeafNodes = 0;
    } //close constructor
    
    TreeNode* getRoot()
    {
        return root;
    }
    
//function 1: creates a TreeNode.
    void createNode(int num)
    {
        TreeNode* newNode = NULL;
        newNode = new TreeNode;
        newNode->data = num;
        newNode->left = NULL;
        newNode->right = NULL;
        insertNode(root, newNode); //passes new TreeNode into function 2.
    } //close createNode function.
    
//function 2: puts new TreeNode in proper place
    void insertNode(TreeNode*& nodeptr, TreeNode*& newNode) //&???????
    //(root, newNode)
    {
        if(nodeptr == NULL) //base case controlling recursion and located at end of branch, so insertion point found.
        { //also means root is not set in frist node creation.
            nodeptr = newNode; //insert data.
        }
        else if(newNode->data < nodeptr->data) //data is less than parent data, so go left.
            //3 < 7
            //10 < 7
        {
            insertNode(nodeptr->left, newNode); //recursion to go left.
            //nodeptr->left (null) becomes nodeptr in new call.
            //move to next node after each recursion call.
        }
        else //data is greater than parent data, so go right.
        {
            //3 > 7
            //10 > 7
            insertNode(nodeptr->right, newNode); //recursion to go right.
            //nodeptr->right (null) becomes nodeptr in new call.
            //move to next node after each recursion call.
        }
    } //close insertNode function.
    
//function 3:
    bool searchNode(int num)
    {
        TreeNode* nodeptr = root;
        while(nodeptr) //nodeptr is pointing to a Node.
        {
            if(nodeptr->data == num)
            {
                return true;
            }
            else if(num < nodeptr->data)
            {
                nodeptr = nodeptr->left;
            }
            else
            {
                nodeptr = nodeptr->right;
            }
        } //end while.
        return false; //?????????????
    } //close searchNode function.
    
//destructor: CANT WE SIMPLIFY DESTRUCTOR AND FUNCTION 4 TO JUST 1 FUNCTION?
    ~IntBinaryTree()
    {
        destroyTree(root);
    } //close destructor.
    
//function 4:
    void destroyTree(TreeNode* nodeptr)
    {
        if(nodeptr)
        {
            if(nodeptr->left)
            {
                destroyTree(nodeptr->left); //recursion.
            }
            if(nodeptr->right)
            {
                destroyTree(nodeptr->right);  //recursion.
            }
            delete nodeptr;
        } //end if.
    } //close destroyTree function.
    
//function 5: CANT WE COMBINE 5, 6 AND 7 INTO 1 FUNCTION?
    void remove(int num)
    {
        deleteNode(num, root);
    } //close remove function.
    
//function 6:
    void deleteNode(int num, TreeNode*& nodeptr)
    {
        if(num < nodeptr->data)
        {
            deleteNode(num, nodeptr->left); //recursion.
        }
        else if(num > nodeptr->data)
        {
            deleteNode(num, nodeptr->right); //recursion.
        }
        else
        {
            makeDeletion(nodeptr);
        }
    } //close deleteNode function.

//function 7:
    void makeDeletion(TreeNode*& nodeptr)
    {
        TreeNode* tempNodePtr = NULL;
        
        if(nodeptr == NULL)
        {
            cout << "cannot delete empty node." << endl;
        }
        else if(nodeptr->right == NULL)
        {
            tempNodePtr = nodeptr;
            nodeptr = nodeptr->left; //reattach left child.
            delete tempNodePtr;
        }
        else if(nodeptr->left == NULL)
        {
            tempNodePtr = nodeptr;
            nodeptr = nodeptr->right; //reattach right child.
            delete tempNodePtr;
        }
        else //if Node has 2 children.
        {
            //move 1 node on right.
            tempNodePtr = nodeptr->right;
            
            //go to end of left node.
            while(tempNodePtr->left)
            {
                tempNodePtr = tempNodePtr->left;
            }
            
            //reattach left subtree.
            tempNodePtr->left = nodeptr->left;
            tempNodePtr = nodeptr;
            
            //reattach right subtree.
            nodeptr = nodeptr->right;
            delete tempNodePtr;
        }
    } //close makeDeletion function.
    
//function 8:
    void displayInOrder(TreeNode* nodeptr) const //left-root-right.
    {
        if(nodeptr)
        {
            displayInOrder(nodeptr->left); //recursion.
            cout << nodeptr->data << endl; //root.
            displayInOrder(nodeptr->right); //recursion.
        } //end if.
    } //close displayInOrder function.
    
//function 9:
    void displayPreOrder(TreeNode* nodeptr) const //root-left-right.
    {
        if(nodeptr)
        {
            cout << nodeptr->data << endl; //root.
            displayPreOrder(nodeptr->left); //recursion.
            displayPreOrder(nodeptr->right); //recursion.
        } //end if.
    } //close displayPreOrder function.
    
//function 10:
    void displayPostOrder(TreeNode* nodeptr) const //left-right-root.
    {
        if(nodeptr)
        {
            displayPostOrder(nodeptr->left); //recursion.
            displayPostOrder(nodeptr->right); //recursion.
            cout << nodeptr->data << endl; //root.
        } //end if
    } //close displayInOrder function.
    
//function 11:
    int countTreeNodes(TreeNode *nodeptr) //pass root first.
    {
        if(nodeptr) //as long as pointing to a valid node address... not NULL
            //using preorder traversal.
        {
            countTotalNodes++; //global variable.
            countTreeNodes(nodeptr->left);
            countTreeNodes(nodeptr->right);
        }
        return countTotalNodes;
    } //close countTreeNodes function.
    
//function 12:
    int countTotalLeafNodes(TreeNode *nodeptr) //pass root first.
    {
        if(nodeptr) //as long as pointing to a valid node address... not NULL
            //using preorder traversal.
        {
            if(nodeptr->left == NULL && nodeptr->right == NULL)
            {
                countLeafNodes++; //global variable.
            }
            countTotalLeafNodes(nodeptr->left);
            countTotalLeafNodes(nodeptr->right);
        }
        return countLeafNodes;
    } //close countTotalLeafNodes function.
}; //end IntBinaryTree class.

int main()
{
//A. Build a BST:
    //1. create an object IntBinaryTree:
    IntBinaryTree bst1; //root set to NULL bc of constructor.
    
    //2. create root TreeNode w/ data 7:
    bst1.createNode(7);
    
    //3. create TreeNode w/ data 3.
    //will become left child of root bc 3 is less than 7 & this is a BST.
    bst1.createNode(3);
    
    //4. create TreeNode w/ data 10.
    //will become right child of root bc 10 is greater than 7 & this is a BST.
    bst1.createNode(10);
    
    //5. create TreeNode w/ data 2.
    //will become left child of parent w/ data 3 bc 2 less than 3 & this is a BST.
    bst1.createNode(2);
    
    //6. create TreeNode w/ data 5.
    //will become right child of parent w/ data 3 bc 5 is greater than 3 & this is a BST.
    bst1.createNode(5);
    
    //7. create TreeNode w/ data 12.
    //will become right child of parent w/ data 10 bc 12 is greater than 10 & this is a BST.
    bst1.createNode(12);

//B. search for nodes:
    cout << bst1.searchNode(5) << endl; //1 true.
    cout << bst1.searchNode(11) << endl; //0 false.
    cout << bst1.searchNode(7) << endl; //1 true.

//C. use pre-order to display tree:
    cout << "-------preorder" << endl;
    bst1.displayPreOrder(bst1.getRoot());
    
//D. use in-order to display tree:
    cout << "-------inorder" << endl;
    bst1.displayInOrder(bst1.getRoot());
    
//E. use in-order to display tree:
    cout << "-------postorder" << endl;
    bst1.displayPostOrder(bst1.getRoot());
    
    /*
    cout << bst1.getRoot()->data << endl;
    cout << bst1.getRoot()->left->data << endl;
    cout << bst1.getRoot()->left->left->data << endl;
    cout << bst1.getRoot()->left->right->data << endl;
    
    cout << bst1.getRoot()->right->data << endl;
    cout << bst1.getRoot()->right->right->data << endl;
    */
    
    cout << "total Nodes: " << bst1.countTreeNodes(bst1.getRoot()) << endl;
    cout << "total Leaf Nodes: " << bst1.countTotalLeafNodes(bst1.getRoot()) << endl;
    return 0;
}
