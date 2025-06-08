#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class PQHeap : virtual public PQ<Data>,
                 private HeapVec<Data>
  {
    // Must extend PQ<Data>,
    // Could extend HeapVec<Data>

  private:
    // ...

  protected:
    using Container::size;

    // Import specific functions from HeapVec
    using HeapVec<Data>::HeapifyUp;
    using HeapVec<Data>::HeapifyDown;
    using HeapVec<Data>::elements;

    // ...

  public:
    // Default constructor
    PQHeap();

    /* ************************************************************************ */

    // Specific constructors
    PQHeap(const TraversableContainer<Data> &); // A priority queue obtained from a TraversableContainer
    PQHeap(MappableContainer<Data> &&);         // A priority queue obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    PQHeap(const PQHeap &);

    // Move constructor
    PQHeap(PQHeap &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    ~PQHeap() = default;

    /* ************************************************************************ */

    // Copy assignment
    PQHeap &operator=(const PQHeap &);

    // Move assignment
    PQHeap &operator=(PQHeap &&) noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    const Data &operator[](const ulong) const override; // Override LinearContainer member
    Data &operator[](const ulong) override;             // Override MutableLinearContainer member

    const Data &Front() const override; // Override LinearContainer member
    Data &Front() override;             // Override MutableLinearContainer member

    const Data &Back() const override; // Override LinearContainer member
    Data &Back() override;             // Override MutableLinearContainer member

    bool Empty() const noexcept override; // Override Container member
    ulong Size() const noexcept override; // Override Container member

    // Traversal and mapping functions
    void Traverse(typename TraversableContainer<Data>::TraverseFun) const override;
    void PreOrderTraverse(typename TraversableContainer<Data>::TraverseFun) const override;
    void PostOrderTraverse(typename TraversableContainer<Data>::TraverseFun) const override;

    void Map(typename MappableContainer<Data>::MapFun) override;
    void PreOrderMap(typename MappableContainer<Data>::MapFun) override;
    void PostOrderMap(typename MappableContainer<Data>::MapFun) override;

    bool Exists(const Data &) const noexcept override;

    /* ************************************************************************ */

    // Specific member functions (inherited from ClearableContainer)

    void Clear() override; // Override ClearableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PQ)

    const Data &Tip() const override; // Override PQ member (must throw std::length_error when empty)
    void RemoveTip() override;        // Override PQ member (must throw std::length_error when empty)
    Data TipNRemove() override;       // Override PQ member (must throw std::length_error when empty)

    void Insert(const Data &) override; // Override PQ member (Copy of the value)
    void Insert(Data &&) override;      // Override PQ member (Move of the value)

    void Change(ulong, const Data &) override; // Override PQ member (Copy of the value)
    void Change(ulong, Data &&) override;      // Override PQ member (Move of the value)

  protected:
    // Auxiliary functions, if necessary!
  };

  /* ************************************************************************** */

}

#include "pqheap.cpp"

#endif