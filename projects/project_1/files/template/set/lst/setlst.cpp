namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data>& container) {
  container.Traverse([this](const Data& data) {
    Insert(data);
  });
}

template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data>&& container) noexcept {
  container.Map([this](Data& data) {
    Insert(std::move(data));
  });
}

// Copy constructor
template <typename Data>
SetLst<Data>::SetLst(const SetLst<Data>& other) : List<Data>() {
  if (!other.Empty()) {
    other.Traverse([this](const Data& data) {
      Insert(data);
    });
  }
}

// Move constructor
template <typename Data>
SetLst<Data>::SetLst(SetLst<Data>&& other) noexcept : List<Data>(std::move(other)) {}

// Copy assignment
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& other) {
  if (this != &other) {
    Clear();
    other.Traverse([this](const Data& data) {
      Insert(data);
    });
  }
  return *this;
}

// Move assignment
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& other) noexcept {
  if (this != &other) {
    List<Data>::operator=(std::move(other));
  }
  return *this;
}

// Comparison operators
template <typename Data>
bool SetLst<Data>::operator==(const SetLst<Data>& other) const noexcept {
  if (size != other.size) {
    return false;
  }
  
  // For sets, we need to check both ways: 
  // all elements of this exist in other and vice versa
  bool allElementsExist = true;
  
  this->Traverse([&other, &allElementsExist](const Data& data) {
    if (!other.Exists(data)) {
      allElementsExist = false;
    }
  });
  
  return allElementsExist;
}

template <typename Data>
bool SetLst<Data>::operator!=(const SetLst<Data>& other) const noexcept {
  return !(*this == other);
}

// Specific member functions (inherited from OrderedDictionaryContainer)

template <typename Data>
const Data& SetLst<Data>::Min() const {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  return head->element;
}

template <typename Data>
Data SetLst<Data>::MinNRemove() {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  return List<Data>::FrontNRemove();
}

template <typename Data>
void SetLst<Data>::RemoveMin() {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  List<Data>::RemoveFromFront();
}

template <typename Data>
const Data& SetLst<Data>::Max() const {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  return tail->element;
}

template <typename Data>
Data SetLst<Data>::MaxNRemove() {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  return List<Data>::BackNRemove();
}

template <typename Data>
void SetLst<Data>::RemoveMax() {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  List<Data>::RemoveFromBack();
}

template <typename Data>
const Data& SetLst<Data>::Predecessor(const Data& data) const {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  Node* predNode = FindPredecessorNode(data);
  if (predNode == nullptr) {
    throw std::length_error("SetLst: Predecessor not found");
  }
  
  return predNode->element;
}

template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data& data) {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  Node* predNode = FindPredecessorNode(data);
  if (predNode == nullptr) {
    throw std::length_error("SetLst: Predecessor not found");
  }
  
  Data result = predNode->element;
  
  // Remove the predecessor
  if (predNode == head) {
    RemoveMin();
  } else {
    Node* current = head;
    while (current->next != predNode) {
      current = current->next;
    }
    
    current->next = predNode->next;
    
    if (predNode == tail) {
      tail = current;
    }
    
    delete predNode;
    size--;
  }
  
  return result;
}

template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data& data) {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  Node* predNode = FindPredecessorNode(data);
  if (predNode == nullptr) {
    throw std::length_error("SetLst: Predecessor not found");
  }
  
  // Remove the predecessor
  if (predNode == head) {
    RemoveMin();
  } else {
    Node* current = head;
    while (current->next != predNode) {
      current = current->next;
    }
    
    current->next = predNode->next;
    
    if (predNode == tail) {
      tail = current;
    }
    
    delete predNode;
    size--;
  }
}

template <typename Data>
const Data& SetLst<Data>::Successor(const Data& data) const {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  Node* succNode = FindSuccessorNode(data);
  if (succNode == nullptr) {
    throw std::length_error("SetLst: Successor not found");
  }
  
  return succNode->element;
}

template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& data) {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  Node* succNode = FindSuccessorNode(data);
  if (succNode == nullptr) {
    throw std::length_error("SetLst: Successor not found");
  }
  
  Data result = succNode->element;
  
  // Remove the successor
  if (succNode == head) {
    RemoveMin();
  } else {
    Node* current = head;
    while (current->next != succNode) {
      current = current->next;
    }
    
    current->next = succNode->next;
    
    if (succNode == tail) {
      tail = current;
    }
    
    delete succNode;
    size--;
  }
  
  return result;
}

template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data& data) {
  if (Empty()) {
    throw std::length_error("SetLst: Empty container");
  }
  
  Node* succNode = FindSuccessorNode(data);
  if (succNode == nullptr) {
    throw std::length_error("SetLst: Successor not found");
  }
  
  // Remove the successor
  if (succNode == head) {
    RemoveMin();
  } else {
    Node* current = head;
    while (current->next != succNode) {
      current = current->next;
    }
    
    current->next = succNode->next;
    
    if (succNode == tail) {
      tail = current;
    }
    
    delete succNode;
    size--;
  }
}

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
bool SetLst<Data>::Insert(const Data& data) {
  if (Empty()) {
    List<Data>::InsertAtFront(data);
    return true;
  }
  
  Node* node = FindNodeWithBinarySearch(data);
  
  // If the element already exists
  if (node != nullptr && node->element == data) {
    return false;
  }
  
  return InsertInOrder(node, data);
}

template <typename Data>
bool SetLst<Data>::Insert(Data&& data) {
  if (Empty()) {
    List<Data>::InsertAtFront(std::move(data));
    return true;
  }
  
  Node* node = FindNodeWithBinarySearch(data);
  
  // If the element already exists
  if (node != nullptr && node->element == data) {
    return false;
  }
  
  return InsertInOrder(node, std::move(data));
}

template <typename Data>
bool SetLst<Data>::Remove(const Data& data) {
  if (Empty()) {
    return false;
  }
  
  // If the element is the head
  if (head->element == data) {
    RemoveMin();
    return true;
  }
  
  // If the element is the tail
  if (tail->element == data) {
    RemoveMax();
    return true;
  }
  
  // Find the node
  Node* current = head;
  while (current->next != nullptr && current->next->element != data) {
    current = current->next;
  }
  
  // If the element was found
  if (current->next != nullptr) {
    Node* toDelete = current->next;
    current->next = toDelete->next;
    delete toDelete;
    size--;
    return true;
  }
  
  return false;
}

// Specific member function (inherited from TestableContainer)

template <typename Data>
bool SetLst<Data>::Exists(const Data& data) const noexcept {
  if (Empty()) {
    return false;
  }
  
  Node* node = FindNodeWithBinarySearch(data);
  return (node != nullptr && node->element == data);
}

// Auxiliary functions

template <typename Data>
typename SetLst<Data>::Node* SetLst<Data>::FindNodeWithBinarySearch(const Data& data) const {
  if (Empty()) {
    return nullptr;
  }
  
  // Casi speciali per efficienza
  if (data <= head->element) {
    return (data == head->element) ? head : nullptr;
  }
  
  if (data > tail->element) {
    return tail;
  }
  
  // Ricerca binaria usando la dimensione nota
  ulong left = 0;
  ulong right = size - 1;
  
  while (left <= right) {
    ulong mid = left + (right - left) / 2;
    
    // Ottieni il nodo alla posizione mid
    Node* midNode = GetNodeAt(mid);
    
    if (midNode->element == data) {
      return midNode; // Trovato l'elemento
    } else if (midNode->element < data) {
      left = mid + 1; // Cerca nella metà destra
    } else {
      if (mid == 0) break; // Evita underflow
      right = mid - 1; // Cerca nella metà sinistra
    }
  }
  
  // Trova il nodo immediatamente prima del punto di inserimento
  return GetNodeAt(left > 0 ? left - 1 : 0);
}

template <typename Data>
typename SetLst<Data>::Node* SetLst<Data>::FindSuccessorNode(const Data& data) const {
  if (Empty()) {
    return nullptr;
  }
  
  // If data is less than the minimum, the successor is the minimum
  if (data < head->element) {
    return head;
  }
  
  // If data is greater than or equal to the maximum, there is no successor
  if (data >= tail->element) {
    return nullptr;
  }
  
  // Find the first element greater than data\
  //TODO: da fare con la ricerca binaria
  Node* current = head;
  while (current != nullptr && current->element <= data) {
    current = current->next;
  }
  
  return current;
}

template <typename Data>
typename SetLst<Data>::Node* SetLst<Data>::FindPredecessorNode(const Data& data) const {
  if (Empty()) {
    return nullptr;
  }
  
  // If data is less than or equal to the minimum, there is no predecessor
  if (data <= head->element) {
    return nullptr;
  }
  
  // If data is greater than the maximum, the predecessor is the maximum
  if (data > tail->element) {
    return tail;
  }
  
  // Find the last element less than data
  Node* current = head;
  Node* predecessor = nullptr;

  //TODO: da fare con la ricerca binaria
  while (current != nullptr && current->element < data) {
    predecessor = current;
    current = current->next;
  }
  
  return predecessor;
}

template <typename Data>
bool SetLst<Data>::InsertInOrder(Node* node, const Data& data) {
  if (node == nullptr) {
    // Insert at the beginning
    List<Data>::InsertAtFront(data);
    return true;
  }
  
  if (node == tail && node->element < data) {
    // Insert at the end
    List<Data>::InsertAtBack(data);
    return true;
  }
  
  // Insert in the middle
  Node* newNode = new Node(data);
  if (node->next != nullptr) {
    newNode->next = node->next;
  }
  node->next = newNode;
  
  size++;
  return true;
}

template <typename Data>
bool SetLst<Data>::InsertInOrder(Node* node, Data&& data) {
  if (node == nullptr) {
    // Insert at the beginning
    List<Data>::InsertAtFront(std::move(data));
    return true;
  }
  
  if (node == tail && node->element < data) {
    // Insert at the end
    List<Data>::InsertAtBack(std::move(data));
    return true;
  }
  
  // Insert in the middle
  Node* newNode = new Node(std::move(data));
  if (node->next != nullptr) {
    newNode->next = node->next;
  }
  node->next = newNode;
  
  size++;
  return true;
}

/* ************************************************************************** */

}