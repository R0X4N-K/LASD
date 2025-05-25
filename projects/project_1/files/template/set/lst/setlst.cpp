namespace lasd
{
  /* ************************************************************************** */

  // Specific constructors

  template <typename Data>
  SetLst<Data>::SetLst(const TraversableContainer<Data>& container)
  {
    container.Traverse([this](const Data& data)
      { Insert(data); });  // Insert each element from container into the set
  }

  template <typename Data>
  SetLst<Data>::SetLst(MappableContainer<Data>&& container) noexcept
  {
    container.Map([this](Data& data)
      { Insert(std::move(data)); });  // Move each element from container into the set
  }

  // Copy constructor
  template <typename Data>
  SetLst<Data>::SetLst(const SetLst<Data>& other) : List<Data>()
  {
    if (!other.Empty())
    {
      other.Traverse([this](const Data& data)
        { Insert(data); });  // Insert elements one by one to maintain set properties
    }
  }

  // Move constructor
  template <typename Data>
  SetLst<Data>::SetLst(SetLst<Data>&& other) noexcept : List<Data>(std::move(other)) {}  // Use List's move constructor

  // Copy assignment
  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& other)
  {
    if (this != &other)
    {
      Clear();  // Remove all existing elements
      other.Traverse([this](const Data& data)
        { Insert(data); });  // Insert elements one by one to maintain set properties
    }
    return *this;
  }

  // Move assignment
  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& other) noexcept
  {
    if (this != &other)
    {
      List<Data>::operator=(std::move(other));  // Use List's move assignment
    }
    return *this;
  }

  // Comparison operators
  template <typename Data>
  bool SetLst<Data>::operator==(const SetLst<Data>& other) const noexcept
  {
    if (size != other.size)
    {
      return false;  // Sets of different sizes cannot be equal
    }

    // For sets, we need to check both ways:
    // all elements of this exist in other and vice versa
    bool allElementsExist = true;

    this->Traverse([&other, &allElementsExist](const Data& data)
      {
        if (!other.Exists(data)) {
          allElementsExist = false;  // Element not found in other set
        } });

        return allElementsExist;  // All elements match
  }

  template <typename Data>
  bool SetLst<Data>::operator!=(const SetLst<Data>& other) const noexcept
  {
    return !(*this == other);  // Use equality operator for inverse check
  }

  // Specific member functions (inherited from OrderedDictionaryContainer)

  template <typename Data>
  const Data& SetLst<Data>::Min() const
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    return head->element;  // In a sorted set, head element is the minimum
  }

  template <typename Data>
  Data SetLst<Data>::MinNRemove()
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    return List<Data>::FrontNRemove();  // Remove and return first element
  }

  template <typename Data>
  void SetLst<Data>::RemoveMin()
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    List<Data>::RemoveFromFront();  // Remove first element
  }

  template <typename Data>
  const Data& SetLst<Data>::Max() const
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    return tail->element;  // In a sorted set, tail element is the maximum
  }

  template <typename Data>
  Data SetLst<Data>::MaxNRemove()
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    return List<Data>::BackNRemove();  // Remove and return last element
  }

  template <typename Data>
  void SetLst<Data>::RemoveMax()
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    List<Data>::RemoveFromBack();  // Remove last element
  }

  template <typename Data>
  const Data& SetLst<Data>::Predecessor(const Data& data) const
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    Node* predNode = FindPredecessorNode(data);  // Find predecessor node
    if (predNode == nullptr)
    {
      throw std::length_error("SetLst: Predecessor not found");
    }

    return predNode->element;  // Return predecessor element
  }

  template <typename Data>
  Data SetLst<Data>::PredecessorNRemove(const Data& data)
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    Node* predNode = FindPredecessorNode(data);  // Find predecessor node
    if (predNode == nullptr)
    {
      throw std::length_error("SetLst: Predecessor not found");
    }

    Data result = predNode->element;  // Save predecessor value

    // Remove the predecessor
    if (predNode == head)
    {
      RemoveMin();  // Use RemoveMin if predecessor is the first element
    }
    else
    {
      // Find the node before the predecessor
      Node* current = head;
      while (current->next != predNode)
      {
        current = current->next;
      }

      // Remove predecessor from the list
      current->next = predNode->next;

      if (predNode == tail)
      {
        tail = current;  // Update tail if predecessor was the last element
      }

      delete predNode;  // Free memory
      size--;  // Update size
    }

    return result;  // Return saved value
  }

  template <typename Data>
  void SetLst<Data>::RemovePredecessor(const Data& data)
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    Node* predNode = FindPredecessorNode(data);  // Find predecessor node
    if (predNode == nullptr)
    {
      throw std::length_error("SetLst: Predecessor not found");
    }

    // Remove the predecessor
    if (predNode == head)
    {
      RemoveMin();  // Use RemoveMin if predecessor is the first element
    }
    else
    {
      // Find the node before the predecessor
      Node* current = head;
      while (current->next != predNode)
      {
        current = current->next;
      }

      // Remove predecessor from the list
      current->next = predNode->next;

      if (predNode == tail)
      {
        tail = current;  // Update tail if predecessor was the last element
      }

      delete predNode;  // Free memory
      size--;  // Update size
    }
  }

  template <typename Data>
  const Data& SetLst<Data>::Successor(const Data& data) const
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    Node* succNode = FindSuccessorNode(data);  // Find successor node
    if (succNode == nullptr)
    {
      throw std::length_error("SetLst: Successor not found");
    }

    return succNode->element;  // Return successor element
  }

  template <typename Data>
  Data SetLst<Data>::SuccessorNRemove(const Data& data)
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    Node* succNode = FindSuccessorNode(data);  // Find successor node
    if (succNode == nullptr)
    {
      throw std::length_error("SetLst: Successor not found");
    }

    Data result = succNode->element;  // Save successor value

    // Remove the successor
    if (succNode == head)
    {
      RemoveMin();  // Use RemoveMin if successor is the first element
    }
    else
    {
      // Find the node before the successor
      Node* current = head;
      while (current->next != succNode)
      {
        current = current->next;
      }

      // Remove successor from the list
      current->next = succNode->next;

      if (succNode == tail)
      {
        tail = current;  // Update tail if successor was the last element
      }

      delete succNode;  // Free memory
      size--;  // Update size
    }

    return result;  // Return saved value
  }

  template <typename Data>
  void SetLst<Data>::RemoveSuccessor(const Data& data)
  {
    if (this->Empty())
    {
      throw std::length_error("SetLst: Empty container");
    }

    Node* succNode = FindSuccessorNode(data);  // Find successor node
    if (succNode == nullptr)
    {
      throw std::length_error("SetLst: Successor not found");
    }

    // Remove the successor
    if (succNode == head)
    {
      RemoveMin();  // Use RemoveMin if successor is the first element
    }
    else
    {
      // Find the node before the successor
      Node* current = head;
      while (current->next != succNode)
      {
        current = current->next;
      }

      // Remove successor from the list
      current->next = succNode->next;

      if (succNode == tail)
      {
        tail = current;  // Update tail if successor was the last element
      }

      delete succNode;  // Free memory
      size--;  // Update size
    }
  }

  // Specific member functions (inherited from DictionaryContainer)

  template <typename Data>
  bool SetLst<Data>::Insert(const Data& data)
  {
    if (this->Empty())
    {
      List<Data>::InsertAtFront(data);  // Insert into empty list
      return true;
    }

    Node* predNode = FindNodeWithBinarySearch(data);  // Find insertion point

    // Check if element already exists
    if (predNode != nullptr && predNode->next != nullptr && predNode->next->element == data)
    {
      return false;  // Element already exists
    }

    if (predNode == nullptr)
    {
      if (head->element == data)
      {
        return false;  // Element already exists at head
      }

      List<Data>::InsertAtFront(data);  // Insert at front if smaller than head
      return true;
    }

    return InsertInOrder(predNode, data);  // Insert at correct position to maintain order
  }

  template <typename Data>
  bool SetLst<Data>::Insert(Data&& data)
  {
    if (this->Empty())
    {
      List<Data>::InsertAtFront(std::move(data));  // Insert into empty list
      return true;
    }

    Node* predNode = FindNodeWithBinarySearch(data);  // Find insertion point

    // Check if element already exists
    if (predNode != nullptr && predNode->next != nullptr && predNode->next->element == data)
    {
      return false;  // Element already exists
    }

    if (predNode == nullptr)
    {
      if (head->element == data)
      {
        return false;  // Element already exists at head
      }

      List<Data>::InsertAtFront(std::move(data));  // Insert at front if smaller than head
      return true;
    }

    return InsertInOrder(predNode, std::move(data));  // Insert at correct position to maintain order
  }

  template <typename Data>
  bool SetLst<Data>::Remove(const Data& data)
  {
    if (this->Empty())
    {
      return false;  // Cannot remove from empty set
    }

    // If the element is the head
    if (head->element == data)
    {
      RemoveMin();  // Use RemoveMin for head element
      return true;
    }

    // If the element is the tail
    if (tail->element == data)
    {
      RemoveMax();  // Use RemoveMax for tail element
      return true;
    }

    Node* predNode = FindNodeWithBinarySearch(data);  // Find node before target

    // Check if element exists
    if (predNode != nullptr && predNode->next != nullptr && predNode->next->element == data)
    {
      Node* toDelete = predNode->next;  // Node to remove
      predNode->next = toDelete->next;  // Remove from list
      delete toDelete;  // Free memory
      size--;  // Update size
      return true;
    }

    return false;  // Element not found
  }

  // Specific member function (inherited from TestableContainer)

  template <typename Data>
  bool SetLst<Data>::Exists(const Data& data) const noexcept
  {
    if (this->Empty())
    {
      return false;  // Empty set contains no elements
    }

    if (head->element == data)
    {
      return true;  // Check head element first
    }

    Node* predNode = FindNodeWithBinarySearch(data);  // Find node before target
    return (predNode != nullptr && predNode->next != nullptr && predNode->next->element == data);  // Check if element exists
  }

  // Auxiliary functions

  template <typename Data>
  typename SetLst<Data>::Node* SetLst<Data>::FindNodeWithBinarySearch(const Data& data) const
  {
    if (this->Empty())
    {
      return nullptr;  // Empty list
    }

    if (data < head->element)
    {
      return nullptr;  // Data is smaller than minimum
    }

    if (data == head->element)
    {
      return nullptr;  // Data equals head element
    }

    if (data > tail->element)
    {
      return tail;  // Data is larger than maximum
    }

    ulong left = 0;
    ulong right = size - 1;

    Node* result = nullptr;

    // Binary search implementation
    while (left <= right)
    {
      ulong mid = left + (right - left) / 2;  // Calculate middle index (avoids overflow)

      Node* midNode = this->GetNodeAt(mid);  // Get node at middle index

      if (midNode->element == data)
      {
        if (mid == 0)
        {
          return nullptr;  // If first element, no predecessor
        }
        else
        {
          return this->GetNodeAt(mid - 1);  // Return node before the match
        }
      }
      else if (midNode->element < data)
      {
        result = midNode;  // Update result with potential predecessor
        left = mid + 1;  // Search right half
      }
      else
      {
        if (mid == 0)
          break;  // Avoid underflow
        right = mid - 1;  // Search left half
      }
    }

    return result;  // Return predecessor node or nullptr
  }

  template <typename Data>
  typename SetLst<Data>::Node* SetLst<Data>::FindSuccessorNode(const Data& data) const
  {
    if (this->Empty())
    {
      return nullptr;  // Empty list
    }

    // If data is greater than or equal to the maximum, there is no successor
    if (data >= tail->element)
    {
      return nullptr;  // No successor if data >= maximum
    }

    if (data < head->element)
    {
      return head;  // Head is successor if data < minimum
    }

    Node* predNode = FindNodeWithBinarySearch(data);  // Find predecessor node

    if (predNode == nullptr)
    {
      if (data == head->element && head->next != nullptr)
      {
        return head->next;  // If data equals head, successor is next node
      }
      return head;  // Otherwise head is successor
    }

    if (predNode->next != nullptr && predNode->next->element == data)
    {
      return predNode->next->next;  // If found exact match, successor is next node
    }

    return predNode->next;  // Otherwise successor is next node after predecessor
  }

  template <typename Data>
  typename SetLst<Data>::Node* SetLst<Data>::FindPredecessorNode(const Data& data) const
  {
    if (this->Empty())
    {
      return nullptr;  // Empty list
    }

    // If data is less than or equal to the minimum, there is no predecessor
    if (data <= head->element)
    {
      return nullptr;  // No predecessor if data <= minimum
    }

    // If data is greater than the maximum, the predecessor is the maximum
    if (data > tail->element)
    {
      return tail;  // Tail is predecessor if data > maximum
    }

    Node* predNode = FindNodeWithBinarySearch(data);  // Find predecessor node

    if (predNode != nullptr && predNode->next != nullptr && predNode->next->element == data)
    {
      return predNode;  // If found exact match, predecessor is previous node
    }

    return predNode;  // Otherwise return found predecessor
  }

  template <typename Data>
  bool SetLst<Data>::InsertInOrder(Node* predNode, const Data& data)
  {
    if (predNode == nullptr)
    {
      List<Data>::InsertAtFront(data);  // Insert at front if no predecessor
      return true;
    }

    if (predNode == tail && predNode->element < data)
    {
      List<Data>::InsertAtBack(data);  // Insert at back if larger than maximum
      return true;
    }

    // Insert between predecessor and its next node
    Node* newNode = new Node(data);  // Create new node
    newNode->next = predNode->next;  // Link to next node
    predNode->next = newNode;  // Link from predecessor

    size++;  // Update size
    return true;
  }

  template <typename Data>
  bool SetLst<Data>::InsertInOrder(Node* predNode, Data&& data)
  {
    if (predNode == nullptr)
    {
      List<Data>::InsertAtFront(std::move(data));  // Insert at front if no predecessor
      return true;
    }

    if (predNode == tail && predNode->element < data)
    {
      List<Data>::InsertAtBack(std::move(data));  // Insert at back if larger than maximum
      return true;
    }

    // Insert between predecessor and its next node
    Node* newNode = new Node(std::move(data));  // Create new node with moved data
    newNode->next = predNode->next;  // Link to next node
    predNode->next = newNode;  // Link from predecessor

    size++;  // Update size
    return true;
  }

  /* ************************************************************************** */

}