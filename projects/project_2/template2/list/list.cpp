#include <stdexcept>

namespace lasd
{

  /* ************************************************************************** */

  // Specific constructors

  template <typename Data>
  List<Data>::List(const TraversableContainer<Data> &container)
  {
    container.Traverse([this](const Data &data)
                       {
                         InsertAtBack(data); // Copy each element from container to the end of this list
                       });
  }

  template <typename Data>
  List<Data>::List(MappableContainer<Data> &&container) noexcept
  {
    container.Map([this](Data &data)
                  {
                    InsertAtBack(std::move(data)); // Move each element from container to the end of this list
                  });
  }

  // Copy constructor
  template <typename Data>
  List<Data>::List(const List<Data> &other)
  {
    if (!other.Empty())
    {
      Node *otherCurrent = other.head;

      head = new Node(otherCurrent->element); // Create first node with copy of first element
      Node *thisCurrent = head;
      otherCurrent = otherCurrent->next;

      while (otherCurrent != nullptr)
      {
        thisCurrent->next = new Node(otherCurrent->element); // Copy remaining nodes
        thisCurrent = thisCurrent->next;
        otherCurrent = otherCurrent->next;
      }

      tail = thisCurrent; // Set tail to last created node
      size = other.size;
    }
  }

  // Move constructor
  template <typename Data>
  List<Data>::List(List<Data> &&other) noexcept
  {
    std::swap(head, other.head); // Swap pointers and size with other list
    std::swap(tail, other.tail);
    std::swap(size, other.size);
  }

  // Destructor
  template <typename Data>
  List<Data>::~List()
  {
    Clear(); // Free all dynamically allocated nodes
  }

  // Copy assignment
  template <typename Data>
  List<Data> &List<Data>::operator=(const List<Data> &other)
  {
    if (this != &other)
    {
      if (size <= other.size)
      {
        if (tail == nullptr)
        {
          // If this list is empty, create a new list and swap
          List<Data> *tmpList = new List<Data>(other);
          std::swap(*tmpList, *this);
          delete tmpList;
        }
        else
        {
          // Reuse existing nodes for efficiency
          Node *ocur = other.head;
          for (Node *ncur = head; ncur != nullptr; ncur = ncur->next, ocur = ocur->next)
          {
            ncur->element = ocur->element; // Copy data to existing nodes
          }

          if (ocur != nullptr)
          {
            // If other list has more elements, clone remaining nodes
            tail->next = ocur->Clone();

            // Find new tail after appending nodes
            Node *newTail = tail->next;
            while (newTail->next != nullptr)
            {
              newTail = newTail->next;
            }

            tail = newTail;
          }
        }
      }
      else
      {
        if (other.tail == nullptr)
        {
          // If other list is empty, clear this list
          delete head;
          head = tail = nullptr;
        }
        else
        {
          // This list has more elements than other list
          Node *ncur = head;
          for (Node *ocur = other.head; ocur != nullptr; ocur = ocur->next, tail = ncur, ncur = ncur->next)
          {
            ncur->element = ocur->element; // Copy data to existing nodes
          }

          // Delete excess nodes
          Node *temp = ncur;
          tail->next = nullptr;

          while (temp != nullptr)
          {
            Node *toDelete = temp;
            temp = temp->next;
            delete toDelete;
          }
        }
      }

      size = other.size;
    }
    return *this;
  }

  // Move assignment
  template <typename Data>
  List<Data> &List<Data>::operator=(List<Data> &&other) noexcept
  {
    if (this != &other)
    {
      std::swap(head, other.head);
      std::swap(tail, other.tail);
      std::swap(size, other.size);
    }
    return *this;
  }

  // Comparison operators
  template <typename Data>
  bool List<Data>::operator==(const List<Data> &other) const noexcept
  {
    if (size != other.size)
    {
      return false; // Lists of different sizes cannot be equal
    }

    Node *thisCurrent = head;
    Node *otherCurrent = other.head;

    while (thisCurrent != nullptr)
    {
      if (thisCurrent->element != otherCurrent->element)
      {
        return false; // Elements differ, lists are not equal
      }
      thisCurrent = thisCurrent->next;
      otherCurrent = otherCurrent->next;
    }

    return true; // All elements match
  }

  template <typename Data>
  bool List<Data>::operator!=(const List<Data> &other) const noexcept
  {
    return !(*this == other); // Use equality operator for inverse check
  }

  // Specific member functions

  template <typename Data>
  void List<Data>::InsertAtFront(const Data &data)
  {
    Node *newNode = new Node(data); // Create new node with copy of data

    if (head == nullptr)
    {
      // If list is empty, set both head and tail
      head = newNode;
      tail = newNode;
    }
    else
    {
      // Connect new node to current head
      newNode->next = head;
      head = newNode;
    }

    size++;
  }

  template <typename Data>
  void List<Data>::InsertAtFront(Data &&data) noexcept
  {
    Node *newNode = new Node(std::move(data)); // Create new node with moved data

    if (head == nullptr)
    {
      // If list is empty, set both head and tail
      head = newNode;
      tail = newNode;
    }
    else
    {
      // Connect new node to current head
      newNode->next = head;
      head = newNode;
    }

    size++;
  }

  template <typename Data>
  void List<Data>::RemoveFromFront()
  {
    if (Empty())
    {
      throw std::length_error("List: Empty container");
    }

    Node *temp = head;
    head = head->next; // Update head to point to second node
    delete temp;       // Free memory of removed node

    size--;
    if (head == nullptr)
    {
      tail = nullptr; // If list becomes empty, also update tail
    }
  }

  template <typename Data>
  Data List<Data>::FrontNRemove()
  {
    if (Empty())
    {
      throw std::length_error("List: Empty container");
    }

    Data value = head->element; // Save value before removing
    RemoveFromFront();
    return value;
  }

  template <typename Data>
  void List<Data>::InsertAtBack(const Data &data)
  {
    Node *newNode = new Node(data); // Create new node with copy of data

    if (tail == nullptr)
    {
      // If list is empty, set both head and tail
      head = newNode;
      tail = newNode;
    }
    else
    {
      // Add to end and update tail
      tail->next = newNode;
      tail = newNode;
    }

    size++;
  }

  template <typename Data>
  void List<Data>::InsertAtBack(Data &&data) noexcept
  {
    Node *newNode = new Node(std::move(data)); // Create new node with moved data

    if (tail == nullptr)
    {
      // If list is empty, set both head and tail
      head = newNode;
      tail = newNode;
    }
    else
    {
      // Add to end and update tail
      tail->next = newNode;
      tail = newNode;
    }

    size++;
  }

  template <typename Data>
  void List<Data>::RemoveFromBack()
  {
    if (Empty())
    {
      throw std::length_error("List: Empty container");
    }

    if (head == tail)
    {
      // If only one element, clear the list
      delete head;
      head = nullptr;
      tail = nullptr;
    }
    else
    {
      // Find the node right before tail
      Node *current = head;
      while (current->next != tail)
      {
        current = current->next;
      }

      delete tail;
      tail = current; // Update tail to the new last node
      tail->next = nullptr;
    }

    size--;
  }

  template <typename Data>
  Data List<Data>::BackNRemove()
  {
    if (Empty())
    {
      throw std::length_error("List: Empty container");
    }

    Data value = tail->element; // Save value before removing
    RemoveFromBack();
    return value;
  }

  // Specific member functions (inherited from MutableLinearContainer)

  template <typename Data>
  Data &List<Data>::operator[](const ulong index)
  {
    if (index >= size)
    {
      throw std::out_of_range("List: Index out of range");
    }

    return GetNodeAt(index)->element; // Return mutable reference to element
  }

  template <typename Data>
  Data &List<Data>::Front()
  {
    if (Empty())
    {
      throw std::length_error("List: Empty container");
    }

    return head->element; // Return mutable reference to first element
  }

  template <typename Data>
  Data &List<Data>::Back()
  {
    if (Empty())
    {
      throw std::length_error("List: Empty container");
    }

    return tail->element; // Return mutable reference to last element
  }

  // Specific member functions (inherited from LinearContainer)

  template <typename Data>
  const Data &List<Data>::operator[](const ulong index) const
  {
    if (index >= size)
    {
      throw std::out_of_range("List: Index out of range");
    }

    return GetNodeAt(index)->element; // Return const reference to element
  }

  template <typename Data>
  const Data &List<Data>::Front() const
  {
    if (Empty())
    {
      throw std::length_error("List: Empty container");
    }

    return head->element; // Return const reference to first element
  }

  template <typename Data>
  const Data &List<Data>::Back() const
  {
    if (Empty())
    {
      throw std::length_error("List: Empty container");
    }

    return tail->element; // Return const reference to last element
  }

  // Specific member function (inherited from MappableContainer, PreOrderMappableContainer, PostOrderMappableContainer)

  template <typename Data>
  void List<Data>::Map(MapFun fun)
  {
    PreOrderMap(fun); // Default Map implementation uses PreOrderMap
  }

  template <typename Data>
  void List<Data>::PreOrderMap(MapFun fun)
  {
    Node *current = head;
    while (current != nullptr)
    {
      fun(current->element); // Apply function to each element from front to back
      current = current->next;
    }
  }

  template <typename Data>
  void List<Data>::PostOrderMap(MapFun fun)
  {
    std::function<void(Node *)> recursiveMap = [&recursiveMap, &fun](Node *currentNode)
    {
      if (currentNode != nullptr)
      {
        recursiveMap(currentNode->next); // Process next nodes first (recursively)
        fun(currentNode->element);       // Then process current node (back to front)
      }
    };
    recursiveMap(head);
  }

  // Specific member function (inherited from TraversableContainer, PreOrderTraversableContainer, PostOrderTraversableContainer)

  template <typename Data>
  void List<Data>::Traverse(TraverseFun fun) const
  {
    PreOrderTraverse(fun); // Default Traverse implementation uses PreOrderTraverse
  }

  template <typename Data>
  void List<Data>::PreOrderTraverse(TraverseFun fun) const
  {
    Node *current = head;
    while (current != nullptr)
    {
      fun(current->element); // Apply function to each element from front to back
      current = current->next;
    }
  }

  template <typename Data>
  void List<Data>::PostOrderTraverse(TraverseFun fun) const
  {
    std::function<void(Node *)> recursiveTraverse = [&recursiveTraverse, &fun](Node *currentNode)
    {
      if (currentNode != nullptr)
      {
        recursiveTraverse(currentNode->next); // Process next nodes first (recursively)
        fun(currentNode->element);            // Then process current node (back to front)
      }
    };
    recursiveTraverse(head);
  }

  // Specific member function (inherited from ClearableContainer)

  template <typename Data>
  void List<Data>::Clear()
  {
    Node *current = head;
    while (current != nullptr)
    {
      Node *temp = current;
      current = current->next; // Move to next node before deleting current
      delete temp;             // Free memory of current node
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  // Protected auxiliary function

  template <typename Data>
  typename List<Data>::Node *List<Data>::GetNodeAt(ulong index) const
  {
    Node *current = head;
    for (ulong i = 0; i < index && current != nullptr; ++i)
    {
      current = current->next; // Traverse the list to find node at given index
    }
    return current;
  }

  /* ************************************************************************** */

}