/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/Tree.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:13:04 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/Tree.h                 Modified on : 8th March, 2002
 **  $ Author  : Ankur Gupta
 **  
 **  This file is a template code for tree generation.
 **  The tree that is generated through this code is a general tree with any numbers of
 **  childrens for a given node at any level.
 ** 
 **
 *****************************************************************************/

#ifndef TREE_H
#define TREE_H

/*********************************************************
 ** This class is a template class for the node that will 
 ** hold informations such as the information and the 
 ** links to its child,sibling and parent
 **
 ** The information can be in turn any object that the user
 ** wants to store
 *********************************************************/

template <class T>

class Node
  {
  public:
    T* info;
    Node* child;
    Node* sibling;
    Node* parent;
    Node(); //constructor
    ~Node(); // destructor
  };

/********************************************************************
 **This is the template for the Tree itself and it holds funtions such as
 ** adding childrens to the tree, searching a children in the tree, 
 ** deleting the childrens from the tree
 **
 **
 *********************************************************************/
template <class T>

class Tree
  {
  private:
    /** @associates <{Node<T>}>
     * @link association 
     * @supplierCardinality 0..1*/
    Node<T>* head; // declares the head of the tree

    void addChildren(T* children, T* parent); // this method is used to add the childrens to the tree

  public :

    Tree(); // constructor...
    ~Tree(); //destructor...
    Node<T>* getRoot(); // returns the root of the tree
    void addRoot(T* parent); // adds the root of the tree
    void addSibling(T* sibling, T* parent); // adds new sibling to the node
    Node<T>* search(T* info, Node<T>* next); // search the info in the tree
    void display(Node<T>* next); // displays the given tree in in-order traversal..
    void display(); // displays the tree from the root..
    int deleteNode(T* node); // delete's the node...
  };

// Node: implementation of the Node class.
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
template <class T>
Node<T>::Node()
{
  info = NULL;
  child = NULL;
  sibling = NULL;
  parent = NULL;
}

template <class T>
Node<T>::~Node(){}

// Tree.cpp: implementation of the Tree class.
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

/********************************
 ** Returns :- Node<T>* The pointer to the node
 ** Parameter:- Void
 ** 
 ** This method is used to get the root of the tree
 ***************************************************/
template <class T>
Node<T>* Tree<T>::getRoot()
{
  return head;
}

/********************************
 ** This the constructor of the Tree class
 ***************************************************/
template <class T>
Tree<T>::Tree()
{
  head = NULL;
}

/********************************
 ** This the destructor of the class Tree
 ***************************************************/
template <class T>
Tree<T>::~Tree()
{
  delete head;
}

/*******************************
 ** Returns:- Void
 ** Parameter:- T* The pointer to the infomation to be stored in the tree
 ** This method is used to add the root of the tree
 *********************************/
template <class T>
void Tree<T>::addRoot(T* parent)
{
  Node<T>* newNode = new Node<T>;
  newNode->info = parent;
  newNode->parent = head;
  head = newNode;
}

/*************************************************************************
 ** Returns:- Void
 ** Parameter:- 1. T* info The pointer to the infomation to be stored in the tree
 **             2. T* parent The pointer to the info..parent  
 ** This method is used to add the child to the given parent
 ***************************************************************************/
template <class T>
void Tree<T>::addChildren(T* info, T* parent)
{
  Node<T>* newNode = new Node<T>;
  newNode->info = info;
  Node<T>* parentNode = NULL;

  parentNode = search(parent, head);   // get the poiter to the parent

  if (parentNode) //if the Node exist than
    {
      newNode->parent = parentNode;
      parentNode->child = newNode;
    }
  else
    {
      newNode->parent = head;
      head = newNode;
    }
}

/*************************************************************************
 ** Returns:- Void
 ** Parameter:- 1. T* info The pointer to the infomation to be stored in the tree
 **             2. T* parent The pointer to the info..parent  
 ** This method is used to add the sibling/child to the given parent
 ***************************************************************************/
template <class T>
void Tree<T>::addSibling(T* info, T* parent)
{
  Node<T> *parentNode = NULL, *myParent = NULL;

  parentNode = search(parent, head); // get the poiter to the parent
  myParent = parentNode;

  if (parentNode)
    parentNode = parentNode->child;

  //if the child is  present than add this as the next sibling
  if (parentNode)
    {
      while (parentNode->sibling != NULL)
        parentNode = parentNode->sibling;

      Node<T>* newNode = new Node<T>;

      newNode->info = info;

      newNode->parent = myParent;

      parentNode->sibling = newNode;
    }
  else
    addChildren(info, parent);
}

/*************************************************************************
 ** Returns:- Node<T>* The node found
 ** Parameter:- 1. T* info The pointer to the infomation to be stored in the tree
 **             2. Node<T>*  The pointer to the node from where the search should begin  
 ** This method is used to search the given information in the tree and returns the node
 ** or NULL if no node is found as the return argument
 ***************************************************************************/
template <class T>
Node<T>* Tree<T>::search(T* info, Node<T>* next)
{
  Node<T>* ret;

  if (next)
    {
      if (next->info == info)
      {return next;}
      else
        {
          if (ret = search(info, next->sibling))
            return ret;
          else if (ret = search(info, next->child))
            return ret;
          else
            return NULL;
        }
    }
  else
    return NULL;
}

/*************************************************************************
 ** Returns:- void
 ** Parameter:- 1. T*  The pointer to the infomation to be deleted
 **             
 ** This method is used to delete the information from the tree
 ***************************************************************************/
template <class T>
int Tree<T>::deleteNode(T* node)
{
  Node<T>*deleteNode; // a node to be deleted
  deleteNode = search(node, head); // gets the node to be deleted...

  if (deleteNode)
    {
      if (deleteNode == head) //I AM THE HEAD NODE...
        head = NULL;
      else
        {
          if (deleteNode->parent->child == deleteNode) // i.e. I am the first child of the parent
            deleteNode->parent->child = deleteNode->sibling;
          else //i am not the first child i am some sibling than..
            {
              Node<T>*nextNode;
              nextNode = deleteNode->parent->child;

              while (nextNode->sibling != deleteNode)
                nextNode = nextNode->sibling;

              nextNode->sibling = deleteNode->sibling;
            }
        }

      // call the routine to delete all the siblings and child of the node...
      delete deleteNode;

      // free node...
      return 1;
    }
  else
    return 0;
}

/*************************************************************************
 ** Returns:- Void
 ** Parameter:- 1. Node<T>*  The pointer to the node to be displayed
 **             
 ** This method is used to display the node 
 ***************************************************************************/

//This function displays the tree from the particular Node..
template <class T>
void Tree<T>::display(Node<T>* next)
{
  if (next != NULL)
    {
      display(next->sibling);
      display(next->child);
    }
}

//This is no argument method that displays the entier tree
template <class T>
void Tree<T>::display()
{
  display(head);
}

#endif
