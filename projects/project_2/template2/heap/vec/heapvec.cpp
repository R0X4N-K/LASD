namespace lasd {

/* ************************************************************************** */

// Specific constructor with initial size
template <typename Data>
HeapVec<Data>::HeapVec(const ulong newsize) : Vector<Data>(newsize) {}

// Specific constructor from TraversableContainer
template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& con) : Vector<Data>(con) {
  Heapify();
}

// Specific constructor from MappableContainer (move)
template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>&& con) noexcept : Vector<Data>(std::move(con)) {
  Heapify();
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& heap) : Vector<Data>(heap) {}

// Move constructor
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& heap) noexcept : Vector<Data>(std::move(heap)) {}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& heap) {
  Vector<Data>::operator=(heap);
  return *this;
}

// Move assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& heap) noexcept {
  Vector<Data>::operator=(std::move(heap));
  return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data>& heap) const noexcept {
  return Vector<Data>::operator==(heap);
}

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data>& heap) const noexcept {
  return !(*this == heap);
}

/* ************************************************************************** */

// Specific member function (inherited from ClearableContainer)

template <typename Data>
void HeapVec<Data>::Clear() {
  Vector<Data>::Clear();
}

/* ************************************************************************** */

// Specific member functions (inherited from Heap)

// Check if the current structure maintains heap property
template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept {
  for (ulong i = 0; i < size; ++i) {
    ulong left = LeftChild(i);
    ulong right = RightChild(i);
    
    // Check left child
    if (left < size && elements[i] < elements[left]) {
      return false;
    }
    
    // Check right child
    if (right < size && elements[i] < elements[right]) {
      return false;
    }
  }
  return true;
}

// Transform the current structure into a valid heap
template <typename Data>
void HeapVec<Data>::Heapify() {
  // Start from the last non-leaf node and heapify down
  if (size > 1) {
    for (ulong i = (size / 2); i > 0; --i) {
      HeapifyDown(i - 1);
    }
  }
}

/* ************************************************************************** */

// Specific member function (inherited from SortableLinearContainer)

// Sort using heap sort algorithm
template <typename Data>
void HeapVec<Data>::Sort() {
  // First ensure we have a valid heap
  Heapify();
  
  // Extract elements one by one from heap
  for (ulong i = size; i > 1; --i) {
    // Move current root to end
    std::swap(elements[0], elements[i - 1]);
    
    // Temporarily reduce heap size and heapify down
    ulong originalSize = size;
    size = i - 1;
    HeapifyDown(0);
    size = originalSize;
  }
}

/* ************************************************************************** */

// Additional specific member functions for heap operations

// Insert element and maintain heap property
template <typename Data>
void HeapVec<Data>::Insert(const Data& value) {
  Vector<Data>::Resize(size + 1);
  elements[size - 1] = value;
  HeapifyUp(size - 1);
}

// Insert element with move semantics
template <typename Data>
void HeapVec<Data>::Insert(Data&& value) {
  Vector<Data>::Resize(size + 1);
  elements[size - 1] = std::move(value);
  HeapifyUp(size - 1);
}

// Remove root element and maintain heap property
template <typename Data>
void HeapVec<Data>::RemoveRoot() {
  if (size == 0) {
    throw std::length_error("Heap is empty");
  }
  
  if (size == 1) {
    Vector<Data>::Resize(0);
  } else {
    elements[0] = std::move(elements[size - 1]);
    Vector<Data>::Resize(size - 1);
    HeapifyDown(0);
  }
}

/* ************************************************************************** */

// Auxiliary functions

// Maintain heap property downward from given index
template <typename Data>
void HeapVec<Data>::HeapifyDown(ulong index) {
  ulong largest = index;
  ulong left = LeftChild(index);
  ulong right = RightChild(index);
  
  // Find largest among index, left child and right child
  if (left < size && elements[left] > elements[largest]) {
    largest = left;
  }
  
  if (right < size && elements[right] > elements[largest]) {
    largest = right;
  }
  
  // If largest is not the current index, swap and continue heapifying
  if (largest != index) {
    std::swap(elements[index], elements[largest]);
    HeapifyDown(largest);
  }
}

// Maintain heap property upward from given index
template <typename Data>
void HeapVec<Data>::HeapifyUp(ulong index) {
  if (index > 0) {
    ulong parent = Parent(index);
    
    // If current element is greater than parent, swap and continue
    if (elements[index] > elements[parent]) {
      std::swap(elements[index], elements[parent]);
      HeapifyUp(parent);
    }
  }
}

// Get left child index
template <typename Data>
ulong HeapVec<Data>::LeftChild(ulong index) const noexcept {
  return (2 * index) + 1;
}

// Get right child index
template <typename Data>
ulong HeapVec<Data>::RightChild(ulong index) const noexcept {
  return (2 * index) + 2;
}

// Get parent index
template <typename Data>
ulong HeapVec<Data>::Parent(ulong index) const noexcept {
  return (index - 1) / 2;
}

/* ************************************************************************** */

}