namespace lasd {

  /* ************************************************************************** */

  // Specific constructors

  template <typename Data>
  List<Data>::List(const TraversableContainer<Data>& container) {
    container.Traverse([this](const Data& data) {
      InsertAtBack(data);
      });
  }

  template <typename Data>
  List<Data>::List(MappableContainer<Data>&& container) noexcept {
    container.Map([this](Data& data) {
      InsertAtBack(std::move(data));
      });
  }

  // Copy constructor
  template <typename Data>
  List<Data>::List(const List<Data>& other) {
    if (!other.Empty()) {
      Node* otherCurrent = other.head;

      head = new Node(otherCurrent->element);
      Node* thisCurrent = head;
      otherCurrent = otherCurrent->next;

      while (otherCurrent != nullptr) {
        thisCurrent->next = new Node(otherCurrent->element);
        thisCurrent = thisCurrent->next;
        otherCurrent = otherCurrent->next;
      }

      tail = thisCurrent;
      size = other.size;
    }
  }

  // Move constructor
  template <typename Data>
  List<Data>::List(List<Data>&& other) noexcept {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
  }

  // Destructor
  template <typename Data>
  List<Data>::~List() {
    Clear();
  }

  // Copy assignment
  template <typename Data>
  List<Data>& List<Data>::operator=(const List<Data>& other) {
    if (this != &other) {
      if (size <= other.size) {
        if (tail == nullptr) {
          List<Data>* tmpList = new List<Data>(other);
          std::swap(*tmpList, *this);
          delete tmpList;
        }
        else {
          Node* ocur = other.head;
          for (Node* ncur = head; ncur != nullptr; ncur = ncur->next, ocur = ocur->next) {
            ncur->element = ocur->element;
          }

          if (ocur != nullptr) {
            tail->next = ocur->Clone();

            Node* newTail = tail->next;
            while (newTail->next != nullptr) {
              newTail = newTail->next;
            }

            tail = newTail;
          }
        }
      }
      else {
        if (other.tail == nullptr) {
          delete head;
          head = tail = nullptr;
        }
        else {
          Node* ncur = head;
          for (Node* ocur = other.head; ocur != nullptr; ocur = ocur->next, tail = ncur, ncur = ncur->next) {
            ncur->element = ocur->element;
          }

          Node* temp = ncur;
          tail->next = nullptr;

          while (temp != nullptr) {
            Node* toDelete = temp;
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
  List<Data>& List<Data>::operator=(List<Data>&& other) noexcept {
    if (this != &other) {
      // Non chiamare Clear()! Fai solo lo swap
      std::swap(head, other.head);
      std::swap(tail, other.tail);
      std::swap(size, other.size);
    }
    return *this;
  }

  // Comparison operators
  template <typename Data>
  bool List<Data>::operator==(const List<Data>& other) const noexcept {
    if (size != other.size) {
      return false;
    }

    Node* thisCurrent = head;
    Node* otherCurrent = other.head;

    while (thisCurrent != nullptr) {
      if (thisCurrent->element != otherCurrent->element) {
        return false;
      }
      thisCurrent = thisCurrent->next;
      otherCurrent = otherCurrent->next;
    }

    return true;
  }

  template <typename Data>
  bool List<Data>::operator!=(const List<Data>& other) const noexcept {
    return !(*this == other);
  }

  // Specific member functions

  template <typename Data>
  void List<Data>::InsertAtFront(const Data& data) {
    Node* newNode = new Node(data);

    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    }
    else {
      newNode->next = head;
      head = newNode;
    }

    size++;
  }

  template <typename Data>
  void List<Data>::InsertAtFront(Data&& data) noexcept {
    Node* newNode = new Node(std::move(data));

    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    }
    else {
      newNode->next = head;
      head = newNode;
    }

    size++;
  }

  template <typename Data>
  void List<Data>::RemoveFromFront() {
    if (Empty()) {
      throw std::length_error("List: Empty container");
    }

    Node* temp = head;
    head = head->next;
    delete temp;

    size--;
    if (head == nullptr) {
      tail = nullptr;
    }
  }

  template <typename Data>
  Data List<Data>::FrontNRemove() {
    if (Empty()) {
      throw std::length_error("List: Empty container");
    }

    Data value = head->element;
    RemoveFromFront();
    return value;
  }

  template <typename Data>
  void List<Data>::InsertAtBack(const Data& data) {
    Node* newNode = new Node(data);

    if (tail == nullptr) {
      head = newNode;
      tail = newNode;
    }
    else {
      tail->next = newNode;
      tail = newNode;
    }

    size++;
  }

  template <typename Data>
  void List<Data>::InsertAtBack(Data&& data) noexcept {
    Node* newNode = new Node(std::move(data));

    if (tail == nullptr) {
      head = newNode;
      tail = newNode;
    }
    else {
      tail->next = newNode;
      tail = newNode;
    }

    size++;
  }

  template <typename Data>
  void List<Data>::RemoveFromBack() {
    if (Empty()) {
      throw std::length_error("List: Empty container");
    }

    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
    }
    else {
      Node* current = head;
      while (current->next != tail) {
        current = current->next;
      }

      delete tail;
      tail = current;
      tail->next = nullptr;
    }

    size--;
  }

  template <typename Data>
  Data List<Data>::BackNRemove() {
    if (Empty()) {
      throw std::length_error("List: Empty container");
    }

    Data value = tail->element;
    RemoveFromBack();
    return value;
  }

  // Specific member functions (inherited from MutableLinearContainer)

  template <typename Data>
  Data& List<Data>::operator[](const ulong index) {
    if (index >= size) {
      throw std::out_of_range("List: Index out of range");
    }

    return GetNodeAt(index)->element;
  }

  template <typename Data>
  Data& List<Data>::Front() {
    if (Empty()) {
      throw std::length_error("List: Empty container");
    }

    return head->element;
  }

  template <typename Data>
  Data& List<Data>::Back() {
    if (Empty()) {
      throw std::length_error("List: Empty container");
    }

    return tail->element;
  }

  // Specific member functions (inherited from LinearContainer)

  template <typename Data>
  const Data& List<Data>::operator[](const ulong index) const {
    if (index >= size) {
      throw std::out_of_range("List: Index out of range");
    }

    return GetNodeAt(index)->element;
  }

  template <typename Data>
  const Data& List<Data>::Front() const {
    if (Empty()) {
      throw std::length_error("List: Empty container");
    }

    return head->element;
  }

  template <typename Data>
  const Data& List<Data>::Back() const {
    if (Empty()) {
      throw std::length_error("List: Empty container");
    }

    return tail->element;
  }

  // Specific member function (inherited from MappableContainer, PreOrderMappableContainer, PostOrderMappableContainer)

  template <typename Data>
  void List<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
  }

  template <typename Data>
  void List<Data>::PreOrderMap(MapFun fun) {
    Node* current = head;
    while (current != nullptr) {
      fun(current->element);
      current = current->next;
    }
  }

  template <typename Data>
  void List<Data>::PostOrderMap(MapFun fun) {
    std::function<void(Node*)> recursiveMap = [&recursiveMap, &fun](Node* currentNode) {
      if (currentNode != nullptr) {
        recursiveMap(currentNode->next);
        fun(currentNode->element);
      }
      };
    recursiveMap(head);
  }

  // Specific member function (inherited from TraversableContainer, PreOrderTraversableContainer, PostOrderTraversableContainer)

  template <typename Data>
  void List<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
  }

  template <typename Data>
  void List<Data>::PreOrderTraverse(TraverseFun fun) const {
    Node* current = head;
    while (current != nullptr) {
      fun(current->element);
      current = current->next;
    }
  }

  template <typename Data>
  void List<Data>::PostOrderTraverse(TraverseFun fun) const {
    std::function<void(Node*)> recursiveTraverse = [&recursiveTraverse, &fun](Node* currentNode) {
      if (currentNode != nullptr) {
        recursiveTraverse(currentNode->next);
        fun(currentNode->element);
      }
      };
    recursiveTraverse(head);
  }

  // Specific member function (inherited from ClearableContainer)

  template <typename Data>
  void List<Data>::Clear() {
    Node* current = head;
    while (current != nullptr) {
      Node* temp = current;
      current = current->next;
      delete temp;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
  }

  // Protected auxiliary function

  template <typename Data>
  typename List<Data>::Node* List<Data>::GetNodeAt(ulong index) const {
    Node* current = head;
    for (ulong i = 0; i < index && current != nullptr; ++i) {
      current = current->next;
    }
    return current;
  }

  /* ************************************************************************** */

}