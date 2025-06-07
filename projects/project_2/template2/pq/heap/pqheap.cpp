namespace lasd
{

  /* ************************************************************************** */

  // Default constructor
  template <typename Data>
  PQHeap<Data>::PQHeap() : Vector<Data>(), HeapVec<Data>()
  {
    // Default construction - creates empty PQ using HeapVec
  }

  /* ************************************************************************** */

  // Specific constructors
  template <typename Data>
  PQHeap<Data>::PQHeap(const TraversableContainer<Data> &container)
      : Vector<Data>(container), HeapVec<Data>(container)
  {
    // Initialize from TraversableContainer - call both Vector and HeapVec constructors explicitly
  }

  template <typename Data>
  PQHeap<Data>::PQHeap(MappableContainer<Data> &&container)
      : Vector<Data>(std::move(container)), HeapVec<Data>(std::move(container))
  {
    // Initialize from MappableContainer - call both Vector and HeapVec constructors explicitly
  }

  /* ************************************************************************** */

  // Copy constructor
  template <typename Data>
  PQHeap<Data>::PQHeap(const PQHeap<Data> &other)
      : Vector<Data>(other), HeapVec<Data>(other)
  {
    // Copy construction - call both Vector and HeapVec copy constructors explicitly
  }

  // Move constructor
  template <typename Data>
  PQHeap<Data>::PQHeap(PQHeap<Data> &&other) noexcept
      : Vector<Data>(std::move(other)), HeapVec<Data>(std::move(other))
  {
    // Move construction - call both Vector and HeapVec move constructors explicitly
  }

  /* ************************************************************************** */

  // Copy assignment
  template <typename Data>
  PQHeap<Data> &PQHeap<Data>::operator=(const PQHeap<Data> &other)
  {
    if (this != &other)
    {
      HeapVec<Data>::operator=(other);
    }
    return *this;
  }

  // Move assignment
  template <typename Data>
  PQHeap<Data> &PQHeap<Data>::operator=(PQHeap<Data> &&other) noexcept
  {
    if (this != &other)
    {
      HeapVec<Data>::operator=(std::move(other));
    }
    return *this;
  }

  /* ************************************************************************** */

  // Specific member functions (inherited from LinearContainer)
  // PQHeap implementa PQ che eredita da LinearContainer, quindi deve implementare questi metodi

  template <typename Data>
  const Data &PQHeap<Data>::operator[](const ulong index) const
  {
    return HeapVec<Data>::operator[](index); // Delega a HeapVec
  }

  template <typename Data>
  Data &PQHeap<Data>::operator[](const ulong index)
  {
    return HeapVec<Data>::operator[](index); // Delega a HeapVec
  }

  template <typename Data>
  const Data &PQHeap<Data>::Front() const
  {
    return HeapVec<Data>::Front(); // Delega a HeapVec
  }

  template <typename Data>
  Data &PQHeap<Data>::Front()
  {
    return HeapVec<Data>::Front(); // Delega a HeapVec
  }

  template <typename Data>
  const Data &PQHeap<Data>::Back() const
  {
    return HeapVec<Data>::Back(); // Delega a HeapVec
  }

  template <typename Data>
  Data &PQHeap<Data>::Back()
  {
    return HeapVec<Data>::Back(); // Delega a HeapVec
  }

  template <typename Data>
  bool PQHeap<Data>::Empty() const noexcept
  {
    return HeapVec<Data>::Empty(); // Delega a HeapVec
  }

  template <typename Data>
  ulong PQHeap<Data>::Size() const noexcept
  {
    return HeapVec<Data>::Size(); // Delega a HeapVec
  }

  // Traversal and mapping functions (da TraversableContainer/MappableContainer)
  template <typename Data>
  void PQHeap<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun fun) const
  {
    HeapVec<Data>::Traverse(fun); // Delega a HeapVec
  }

  template <typename Data>
  void PQHeap<Data>::PreOrderTraverse(typename TraversableContainer<Data>::TraverseFun fun) const
  {
    HeapVec<Data>::PreOrderTraverse(fun); // Delega a HeapVec
  }

  template <typename Data>
  void PQHeap<Data>::PostOrderTraverse(typename TraversableContainer<Data>::TraverseFun fun) const
  {
    HeapVec<Data>::PostOrderTraverse(fun); // Delega a HeapVec
  }

  template <typename Data>
  void PQHeap<Data>::Map(typename MappableContainer<Data>::MapFun fun)
  {
    HeapVec<Data>::Map(fun); // Delega a HeapVec
    // HeapVec dovrebbe già gestire il ripristino della proprietà heap se necessario
  }

  template <typename Data>
  void PQHeap<Data>::PreOrderMap(typename MappableContainer<Data>::MapFun fun)
  {
    HeapVec<Data>::PreOrderMap(fun); // Delega a HeapVec
    // HeapVec dovrebbe già gestire il ripristino della proprietà heap se necessario
  }

  template <typename Data>
  void PQHeap<Data>::PostOrderMap(typename MappableContainer<Data>::MapFun fun)
  {
    HeapVec<Data>::PostOrderMap(fun); // Delega a HeapVec
    // HeapVec dovrebbe già gestire il ripristino della proprietà heap se necessario
  }

  template <typename Data>
  bool PQHeap<Data>::Exists(const Data &data) const noexcept
  {
    return HeapVec<Data>::Exists(data); // Delega a HeapVec
  }

  /* ************************************************************************** */

  // Specific member functions (inherited from ClearableContainer)
  template <typename Data>
  void PQHeap<Data>::Clear()
  {
    HeapVec<Data>::Clear(); // Delega a HeapVec
  }

  /* ************************************************************************** */

  // Specific member functions (inherited from PQ)
  // Questi sono i metodi specifici che PQ richiede

  // Tip function - returns the maximum element (root of max heap)
  template <typename Data>
  const Data &PQHeap<Data>::Tip() const
  {
    if (HeapVec<Data>::Empty())
    {
      throw std::length_error("Priority queue is empty");
    }
    return HeapVec<Data>::operator[](0); // Root is at index 0
  }

  // RemoveTip function - removes the maximum element
  template <typename Data>
  void PQHeap<Data>::RemoveTip()
  {
    if (HeapVec<Data>::Empty())
    {
      throw std::length_error("Priority queue is empty");
    }
    HeapVec<Data>::RemoveRoot(); // Use HeapVec's RemoveRoot function
  }

  // TipNRemove function - returns and removes the maximum element
  template <typename Data>
  Data PQHeap<Data>::TipNRemove()
  {
    if (HeapVec<Data>::Empty())
    {
      throw std::length_error("Priority queue is empty");
    }
    Data tip = HeapVec<Data>::operator[](0); // Save the root element
    HeapVec<Data>::RemoveRoot();             // Remove the root
    return tip;
  }

  // Insert function - copy version
  template <typename Data>
  void PQHeap<Data>::Insert(const Data &value)
  {
    HeapVec<Data>::Insert(value); // Use HeapVec's Insert function
  }

  // Insert function - move version
  template <typename Data>
  void PQHeap<Data>::Insert(Data &&value)
  {
    HeapVec<Data>::Insert(std::move(value)); // Use HeapVec's Insert function with move
  }

  // Change function - copy version
  template <typename Data>
  void PQHeap<Data>::Change(ulong index, const Data &value)
  {
    if (index >= HeapVec<Data>::Size())
    {
      throw std::out_of_range("Vector: Index out of range");
    }
    HeapVec<Data>::operator[](index) = value; // Change the value

    // Restore heap property by trying both directions
    HeapVec<Data>::HeapifyUp(index);   // Check if we need to bubble up
    HeapVec<Data>::HeapifyDown(index); // Check if we need to bubble down
  }

  // Change function - move version
  template <typename Data>
  void PQHeap<Data>::Change(ulong index, Data &&value)
  {
    if (index >= HeapVec<Data>::Size())
    {
      throw std::out_of_range("Vector: Index out of range");
    }
    HeapVec<Data>::operator[](index) = std::move(value); // Change the value with move

    // Restore heap property by trying both directions
    HeapVec<Data>::HeapifyUp(index);   // Check if we need to bubble up
    HeapVec<Data>::HeapifyDown(index); // Check if we need to bubble down
  }

  /* ************************************************************************** */

}