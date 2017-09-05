/*
 *  LL.h
 *
 *  COSC 052 Summer 2017
 *  Project #3
 *
 *  Due on: August 1st, 2017
 *  Author: <shuyu shen>
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor,
 *  or any code taken from the class textbooks.
 */

#ifndef LL_hpp
#define LL_hpp

#include <stdio.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <exception>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cctype>
#include <new>
#include "Exceptions.h"
using namespace std;



void delayFor(float);


//***************************revised version ***************************************




/****************************************************************************
 **                                                                        **
 **                       class Node declaration                           **
 **                                                                        **
 ****************************************************************************/
template <typename T>
class Node
{
public:
    T info;
    Node<T> *next;
    Node<T> *previous;
    
    Node( T = T(), Node<T>* = NULL,Node<T>* = NULL);
};


/****************************************************************************
 **                                                                        **
 **                         class LL declaration                           **
 **                                                                        **
 ****************************************************************************/
template <typename T>
class LL
{
    template <typename F>
    friend ostream& operator<<(ostream& os, const LL<F> &rhsObj);
    
private:
    int count;
    Node<T> * head;
    Node<T> * trailer;
    void copyList(const LL<T>&);
    void initialize ();//initialize data member of a new list or list being clear for reuse.
    
    
public:
    LL();
    //copy constructor
    LL (const LL<T>&);
    ~LL();
    //overloaded assignment
    LL<T>& operator=(const LL<T>&);
    
    void push_back(T);
    void push_front(T);
    T& back() const;//return reference to the back of the list
    T& front() const;//return reference to the front of the list
    unsigned long size();//return the number of object in the linklist
    void clear();
    void remove(unsigned long ndx);// delete the object at specified index
   
    //insert the object passed immediately in fron to the specificed index
    //insert at index = 0 makes the object new first
    //insert at inex =count makes the object new last
    void insert(unsigned long ndx, T);
    T& at(unsigned long) const;
    
    void pop_back();
    void pop_front();
    void push_front();
    void push_back();
    
    bool empty() const;
    unsigned long size() const { return count; }
    
};



/****************************************************************************
 **                                                                        **
 **                      class Node implementation                         **
 **                                                                        **
 ****************************************************************************/


/****************************************************************************
 *                        default constructor                               *
 ****************************************************************************/
template <typename T>
Node<T>::Node( T i, Node<T> *nPtr1,Node<T> *nPtr2)
{
    info = i;
    previous = nPtr1;
    next = nPtr2;
    
}

/****************************************************************************
 **                                                                        **
 **                       class LL implementation                          **
 **                                                                        **
 ****************************************************************************/
/****************************************************************************
 *                        default constructor                               *
 ****************************************************************************/
template <typename T>
LL<T>::LL()
{
    cout << " in the constructor" << endl;
  try
    {
        //two sentinals for header and trailer
        head = new Node<T>();
        head->next = NULL;
        trailer = new Node<T>();
        trailer->previous = NULL;
    }
    catch (bad_alloc) {
        cout << " bad allocation memory " << endl;
    }
   
    count = 0;
    //create list
    this->initialize();
    
}//END of default constructor


/****************************************************************************
 *                          copy constructor                               *
 ****************************************************************************/
template <typename T>
LL<T>::LL (const LL&otherList)
{
//    cout << " in the constructor" << endl;
    try
    {
        //two sentinals for header and trailer
        head = new Node<T>();
        // head->info = "i am the head sentinal";
    
        head->next = trailer;
        trailer = new Node<T>();
        // trailer->info = "i am the trailer sential";
    
        trailer->previous = head;
        count = 0;
        //create list
        this->initialize();
   
        //cout << "complete initializing" << endl;
   
        copyList(otherList);
    }
    catch (bad_alloc) {
        cout << " bad allocation memory " << endl;
    }
    //call copyList to travers list to make copy
 
}//END copy constructor

/****************************************************************************
 *                             destructor                                   *
 ****************************************************************************/
template <typename T>
LL<T>::~LL()
{
    cout << "entered destructor LL::~LL()...\n";
    
    this->clear();
    cout << "exiting destructor LL::~LL()\n";
}//END destructor
/****************************************************************************
 *                                 copyList                                *
 ****************************************************************************/
template <typename T>
void LL<T>::copyList(const LL&obj2)
{
    //    cout << " in the copy list" << endl;
    
    try
    {   Node <T> *otherCurrent = obj2.head->next;//start from the next one to the head
        while (otherCurrent!=obj2.trailer)
        {
            //traver the other list
            //copy info and store info
            T otherInfo = otherCurrent->info;
            this->push_back(otherInfo);
            otherCurrent = otherCurrent->next;//need to move forward
        }
    }
    catch(bad_alloc &err)
    {
        cout << " bad memory allocation " << endl;
    }
    
}
/****************************************************************************
 *                             initializing                                 *
 ****************************************************************************/
template <typename T>
void LL<T>::initialize ()
{

    Node <T> *current = this->head;

    if (current->next!= trailer)
    {
        cout << " not an empty list" << endl;
        
        this->clear();
        
    }//END loop to delete all contents of LL being copied to
    
    //create empty new list
    head->next = trailer;
    trailer->previous = head;
    head->previous = head;
    trailer->next = trailer;
    count = 0;
    
}//END of initialize

/****************************************************************************
 *                       overload = operator                               *
 ****************************************************************************/
template <typename T>
LL<T>& LL<T>::operator=(const LL&rhs)
{
    //wipe the left hand side object
    //avoid self assignment
    try
    {
        if (&rhs != this)//compare address
        {
            //not self assignment initialize the list
            this->initialize();
            
            //call copyList to travers list to make copy
            copyList(rhs);
        }
    }
    catch (bad_alloc)
    {
       cout << " bad memory allocation " << endl;
    }
    
    return *this;//return the value  T& just show it pass by reference
    
}//END overloading assignment operator
/****************************************************************************
 *                          push_back method                                *
 ****************************************************************************/
template <typename T>
void LL<T>::push_back(T value)
{
    try
    {
        if ( head->next == trailer )
        {
            //list is empty add new node previous to head next to trailer
            Node<T> *myNode = new Node<T>(value, head, trailer);
            head -> next = myNode;
            trailer->previous = myNode;
            //   cout << " at empty list:"<< endl;
            //   cout << trailer->previous->info << endl;
        }
        else
        {
            //
            Node<T> *current  = head;
            while (current->next != trailer)
            {
                current = current->next;
            }
            current->next = new Node<T>(value, current, trailer);
            //update what trailer point to
            trailer->previous = current->next;
            
        }
        
        count++;
    }
    catch(bad_alloc &ba1)
    {
        cout << " bad memory allocation " << endl;
    }

}//END of pushback
/****************************************************************************
 *                            pop back                                    *
 ****************************************************************************/

template <typename T>
void LL<T>::pop_back()//project 3
{
    try
    {
        if (head->next == trailer)
        {
            throw logic_error("list is empty");
        }
        //start from after head
        Node<T> *current = head->next;
        if (current->next == trailer)
        {
            //only one object in the list, delete that one
            delete current;
            count --;
            head->next = trailer;//setting head to trailer is importantn
            trailer->previous = head;
        }
        else
        {
            //at least two objects in the list
            while (current -> next != trailer)//because you need to keep track the new last
            {
                current = current->next;
            }
            count --;
            Node<T> *temp = current->previous;
            delete current;
            //update the last node
            temp->next = trailer;
            trailer->previous = temp;
        }
    }
    catch(logic_error &erro)
    {
        cout <<"EORROR: " <<  erro.what() << endl;
    }
}//END pop back

/****************************************************************************
 *                             Back                                         *
 ****************************************************************************/
template <typename T>
T& LL<T>:: back() const
{
    Node<T> *current =head->next;
    try{
        if(current == trailer)//empty list
        {
            throw no_such_object("no such object");
        }
       
    }
    catch (no_such_object &erro)
    {
        cout << "ERROR : "<< erro.what() << endl;
    }
    return trailer->previous->info;
}//END of back
/****************************************************************************
 *                             front                                          *
 ****************************************************************************/
template <typename T>
T& LL<T>:: front() const
{
    Node<T> *current =head->next;
    try{
        if(current == trailer)//empty list
        {
            throw no_such_object("no such object");
        }
        else
        {
            //find the first object and return info
            while(current->previous != head)
            {
                current = current -> previous;
            }
        }
        
    }
    catch (no_such_object &erro)
    {
        cout << "ERROR : "<< erro.what() << endl;
        
    }
   return current->info;
    
}//END of front
/****************************************************************************
 *                            push front                                    *
 ****************************************************************************/
template <typename T>
void LL<T>::push_front(T newValue)
{
    cout << "in the push front" << endl;
    try
    {
        if ( head->next == trailer )
        {
            //list is empty add new node previous to head next to trailer
            Node<T> *myNode = new Node<T>(newValue, head, trailer);
            //updates head and trailer pointers
            head -> next = myNode;
            trailer->previous = myNode;
            cout << "add one to empty list" << endl;
        }
        else
        {
            
            Node<T> *temp  = head->next;//finde first one
            Node<T> *mynode = new Node<T>(newValue, head, temp);//allocate memory
            head->next = mynode;//put it in the first
            temp->previous = mynode;//update previous first one
        }
        
        count++;
    }
    catch(bad_alloc &ba1)
    {
        cout << " bad memory allocation " << endl;
    }
    
}//END push front list

/****************************************************************************
 *                            clear method                                  *
 ****************************************************************************/
template <typename T>
void LL<T>::clear()
{
    cout << "entered function LL::clear()\n";
    int deleteCount = 0;
    
    Node<T> *current = head;
    if (current->next == trailer)//empty list delete head and trailer
    {
        delete head;
        delete trailer;
    }
    else
    {
        current = head->next;
        //traversing list
        while ((current != trailer) && (current != NULL))
        {
            //move forward
            current = current->next;
            delete current->previous;
            count--;
            deleteCount++;
            //updates
            head->next = current;
            current->previous = head;
        }
        //after delete all the nodes set list to empty
        head->next = trailer;
        trailer->previous = head;
    }
    
    cout << deleteCount << " objects deleted from the linked list\n";
    cout << "exiting function LL::clear()" << endl;
}//END of clear

/****************************************************************************
 *                             remove                                        *
 ****************************************************************************/
template <typename T>
void LL<T> ::remove(unsigned long ndx)
{
    try
    {
        if ( ndx < 0 || ndx >= count )
        {//out of range throw exception
            throw std::out_of_range("number is out of range");
        }
        else
        {
            if(ndx == 0)
            {
                //delete the first node in the list
                Node<T> *current = head->next;
                Node<T> *deleteme = current;
                //store the next node
                Node<T> *temp = current->next;
                delete deleteme;
                //update connections
                head->next = temp;
                temp->previous = head;
                //update conts
                count --;
            }
            else
            {
                Node<T> *current = head->next ;
                for ( int i = 0; i < ndx && current!= trailer; i++ )
                {//loop through the list if smaller than ndx and not at the end of list
                    current = current->next;
                }
                //store information before and after the delete one
                Node<T> *temp_front = current-> previous;
                Node<T> *temp_back = current -> next;
                delete current;
                //update connection
                temp_front -> next = temp_back;
                temp_back -> previous = temp_front;
                //update count
                count --;
                
                
            }
        }
        
    }
    catch (std::out_of_range &error) {
        cout << "ERROR : " <<error.what() <<endl;
    }
}//END of remove

/****************************************************************************
 *                            empty method                                  *
 ****************************************************************************/
template <typename T>
bool LL<T>::empty() const
{
    // if head pointer points to trailer, then the list must be empty
    return (head->next == trailer);
}//END of empty

/****************************************************************************
 *                             size                                           *
 ****************************************************************************/
template <typename T>
unsigned long LL<T>:: size()
{
    return count;
    
}//END of size

/****************************************************************************
 *                            insert                                         *
 ****************************************************************************/

//implies push_back(value)same as insert(size, value)
template <typename T>
void LL<T>::insert(unsigned long ndx, T value)
{
    try
    {
        //test out of range
        if ( ndx < 0 || ndx > count )
        {//out of range
            throw std::out_of_range("number is out of range");
        }
        else
        {
            //if ndx = 0 add as the first in the list
            if(ndx == 0)
            {
                //store the previous first node info and connections
                Node<T> *temp = head->next;
                Node<T> *addme = new Node<T>(value, head, temp);
                head->next = addme;
                temp->previous = addme;
                count ++;
            }
            //if ndx = count add to the end of the list
            else if(ndx == count)
            {
                Node<T> *temp = trailer->previous;
                Node<T> *addme = new Node<T>(value, temp, trailer);
                //updates temp and trailer connection
                temp->next = addme;
                trailer -> previous = addme;
                //updates the count
                count ++;
            }
            else
            {  //find the nodes before and at this ndx
                Node<T> *current = head -> next;
                for ( int i = 0; i < ndx && current!= trailer; i++ )
                {//loop through the list if smaller than ndx and not at the end of list
                    current = current->next;
                }
                //store the node before and after the new node
                Node<T> *temp_back = current;
                Node<T> *temp_front = current ->previous;
                Node<T> *addme = new Node<T>(value, temp_front,temp_back);
                //update connection
                temp_front->next = addme;
                temp_back->previous = addme;
                //updates front
                count++;
            }

        }
        
    } catch (std::out_of_range &error)
    {
        cout << "ERROR : " <<error.what() <<endl;
    }
}//END of insert
/****************************************************************************
 *                             at method                                    *
 ****************************************************************************/
template <typename T>
T& LL<T>::at( unsigned long ndx ) const
{
    Node<T> *current = head->next;
  
    //valid ndx from 0 to size-
    try
    {
        if ( ndx < 0 || ndx >= count )
        {//out of range
       
            throw std::out_of_range("number is out of range");
        }
      
        for ( int i = 0; i < ndx && current!= trailer; i++ )
        {
            //loop through the list if smaller than ndx and not at the end of list
                current = current->next;
        }
        if (!current )
        {
            throw std::out_of_range("can't find number");
        }
        return current->info;
    }
    catch (std::out_of_range &error )
    {
        cout << "ERROR :"<< error.what() << endl;
        throw;
    }
    return current->info;
}


/****************************************************************************
 *                            pop front                                    *
 ****************************************************************************/

template <typename T>
void LL<T>::pop_front()//project 3
{
    try
    {
        if (empty())
        {//if list is empty throw logic error
            throw no_such_object("list is empty, nothing to pop");
        }
        else
        {//found the first node and delete it
            Node<T> *current = head;
            head = head->next;
            delete current;
            count --;
        }
    }
    catch (no_such_object &error)
    {
        cout << error.what() << endl;
    }
}


/****************************************************************************
 *                       overload << operator                               *
 ****************************************************************************/

template <typename F>
ostream& operator<<(ostream& os, const LL<F> &rhsObj)
{
    Node<F> *current = rhsObj.head->next;

    while (( current != rhsObj.trailer )&&(current!=NULL))//into the copy list
        //it will be copyList (rhsObj)
    {
        os << current->info << " ";

        current = current->next;
    }
    os << endl;

    return os;
}




#endif /* LL_hpp */
