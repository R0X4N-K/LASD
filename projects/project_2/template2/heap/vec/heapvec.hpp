#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : virtual public Heap<Data>, 
                virtual public Vector<Data> {
  // Must extend Heap<Data>,
  // Could extend Vector<Data>

private:

  // ...

protected:

  using Container::size;
  using Vector<Data>::elements;  // Import elements from Vector

  // ...

public:

  // Default constructor
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  HeapVec(const ulong); // A heap obtained from a TraversableContainer
  HeapVec(const TraversableContainer<Data>&); // A heap obtained from a TraversableContainer
  HeapVec(MappableContainer<Data>&&) noexcept; // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HeapVec(const HeapVec&);

  // Move constructor
  HeapVec(HeapVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  HeapVec& operator=(const HeapVec&);

  // Move assignment
  HeapVec& operator=(HeapVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HeapVec&) const noexcept;
  bool operator!=(const HeapVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)
  
  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  bool IsHeap() const noexcept override; // Override Heap member

  void Heapify() override; // Override Heap member

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() override; // Override SortableLinearContainer member

  /* ************************************************************************ */

  // Additional specific member functions for heap operations

  void Insert(const Data&); // Insert element and maintain heap property
  void Insert(Data&&); // Insert element with move semantics
  void RemoveRoot(); // Remove root element and maintain heap property

protected:

  // Auxiliary functions, if necessary!

  void HeapifyDown(ulong); // Helper function for maintaining heap property downward
  void HeapifyUp(ulong); // Helper function for maintaining heap property upward

  ulong LeftChild(ulong) const noexcept; // Get left child index
  ulong RightChild(ulong) const noexcept; // Get right child index
  ulong Parent(ulong) const noexcept; // Get parent index

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif