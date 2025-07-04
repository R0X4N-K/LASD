#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Heap : virtual public SortableLinearContainer<Data>,
               virtual public ClearableContainer
  {
    // Must extend SortableLinearContainer<Data>,
    //             ClearableContainer

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~Heap() = default;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    Heap &operator=(const Heap &) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    Heap &operator=(Heap &&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator==(const Heap &) const noexcept = delete;
    bool operator!=(const Heap &) const noexcept = delete;

    /* ************************************************************************ */

    // Specific member functions

    // type IsHeap(argument) specifiers;
    virtual bool IsHeap() const noexcept = 0;

    // type Heapify(argument) specifiers;
    virtual void Heapify() = 0;
  };

  /* ************************************************************************** */

}

#endif