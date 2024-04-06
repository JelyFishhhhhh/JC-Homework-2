// list standard header

#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
   ListNode *next;  // successor node, or first element if head
   ListNode *prev;  // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
        mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = node *;
   using const_iterator = const node *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      for(size_type i= 0; i< count; i++){

         nodePtr temp= new node;
         
         // newNode assign
         temp->myVal= Ty();
         temp->prev= myData.myHead->prev;
         temp->next= myData.myHead;
         
         // linked to myData
         myData.myHead->prev->next= temp;
         myData.myHead->prev= temp;
         
      }
      
      myData.mySize= count;
   }

   // List destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the list container.
   ~list()
   {
      clear();
      delete myData.myHead;
   }

   // Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
list& operator=(const list &right) {
    if (this != &right) { // Avoid self-assignment
        // Clear the current list if the right list is empty
        if (right.myData.mySize == 0) {
            if (myData.mySize != 0) clear(); // Assumes clear() properly deletes nodes and sets mySize to 0
        } else { // The right list is not empty
            // Resize current list to match the size of the right list
            while (myData.mySize < right.myData.mySize) {
                // Add nodes to the end
                nodePtr newNode = new node;
                newNode->myVal = Ty(); // Default initialize
                newNode->next = myData.myHead; // Assumes circular list with sentinel node
                newNode->prev = myData.myHead->prev;
                myData.myHead->prev->next = newNode;
                myData.myHead->prev = newNode;
                myData.mySize++;
            }
            while (myData.mySize > right.myData.mySize) {
                // Remove nodes from the end
                nodePtr toDelete = myData.myHead->prev;
                toDelete->prev->next = myData.myHead;
                myData.myHead->prev = toDelete->prev;
                delete toDelete;
                myData.mySize--;
            }

            // Correctly copy elements from right to this list
            nodePtr rightPtr = right.myData.myHead->next; // Start from the first real element of right
            nodePtr thisPtr = myData.myHead->next; // Start from the first real element of this
            while (rightPtr != right.myData.myHead) { // Ensure not to iterate past the sentinel node of right
                thisPtr->myVal = rightPtr->myVal; // Copy value
                thisPtr = thisPtr->next; // Move to next node in this list
                rightPtr = rightPtr->next; // Move to next node in right list
            }
        }
    }

    return *this;
}


   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myHead->next );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   iterator end()
   {
      return iterator( myData.myHead );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myHead );
   }

   // Returns the number of elements in the list container.
   size_type size() const
   {
      return myData.mySize;
   }

   // Returns whether the list container is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // Removes all elements from the list container (which are destroyed),
   // and leaving the container with a size of 0.
   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
         while( myData.myHead->next != myData.myHead )
         {
            myData.myHead->next = myData.myHead->next->next;
            delete myData.myHead->next->prev;
         }

         myData.myHead->prev = myData.myHead;
         myData.mySize = 0;
      }
   }

private:
   ScaryVal myData;
};

#endif // LIST