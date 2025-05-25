#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class LinearContainer : virtual public PreOrderTraversableContainer<Data>,
    virtual public PostOrderTraversableContainer<Data> {
    // Must extend PreOrderTraversableContainer<Data>,
    //             PostOrderTraversableContainer<Data>
    // Represents a container where elements are arranged in a linear sequence

  private:

    // ...

  protected:

    // ...

  public:

    // Destructor
    virtual ~LinearContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    LinearContainer& operator=(const LinearContainer&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    LinearContainer& operator=(LinearContainer&&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is possible.
    bool operator==(const LinearContainer&) const noexcept;

    // type operator!=(argument) specifiers; // Comparison of abstract types is possible.
    bool operator!=(const LinearContainer&) const noexcept;

    /* ************************************************************************ */

    // Specific member functions

    // type operator[](argument) specifiers; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
    virtual const Data& operator[](const ulong) const = 0;  // Access element at specific index (read-only)

    // type Front() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
    virtual const Data& Front() const = 0;  // Access the first element (read-only)

    // type Back() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
    virtual const Data& Back() const = 0;  // Access the last element (read-only)

    /* ************************************************************************ */

    // Specific member function (inherited from TraversableContainer)

    using typename TraversableContainer<Data>::TraverseFun;

    void Traverse(TraverseFun) const override;  // Generic traversal implementation

    /* ************************************************************************ */

    // Specific member function (inherited from PreOrderTraversableContainer)

    void PreOrderTraverse(TraverseFun) const override;  // Pre-order traversal for linear structures

    /* ************************************************************************ */

    // Specific member function (inherited from PostOrderTraversableContainer)

    void PostOrderTraverse(TraverseFun) const override;  // Post-order traversal for linear structures

  };

  /* ************************************************************************** */

  template <typename Data>
  class MutableLinearContainer : virtual public LinearContainer<Data>,
    virtual public PreOrderMappableContainer<Data>,
    virtual public PostOrderMappableContainer<Data> {
    // Must extend LinearContainer<Data>,
    //             PreOrderMappableContainer<Data>,
    //             PostOrderMappableContainer<Data>
    // Extends LinearContainer with mutable access to elements

  private:

    // ...

  protected:

    // ...

  public:
    using LinearContainer<Data>::operator[];  // Import const versions of these operations
    using LinearContainer<Data>::Front;       // from base class to avoid hiding them
    using LinearContainer<Data>::Back;

    // Destructor
    virtual ~MutableLinearContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    MutableLinearContainer& operator=(const MutableLinearContainer&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    MutableLinearContainer& operator=(MutableLinearContainer&&) noexcept = delete;

    /* ************************************************************************ */

    // Specific member functions

    // type operator[](argument) specifiers; // (mutable version; concrete function must throw std::out_of_range when out of range)
    virtual Data& operator[](const ulong) = 0;  // Access element at specific index (mutable)

    // type Front() specifiers; // (mutable version; concrete function must throw std::length_error when empty)
    virtual Data& Front() = 0;  // Access the first element (mutable)

    // type Back() specifiers; // (mutable version; concrete function must throw std::length_error when empty)
    virtual Data& Back() = 0;  // Access the last element (mutable)

    /* ************************************************************************ */

    // Specific member function (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFun;

    void Map(MapFun) override;  // Generic mapping implementation

    /* ************************************************************************ */

    // Specific member function (inherited from PreOrderMappableContainer)

    void PreOrderMap(MapFun) override;  // Pre-order mapping for linear structures

    /* ************************************************************************ */

    // Specific member function (inherited from PostOrderMappableContainer)

    void PostOrderMap(MapFun) override;  // Post-order mapping for linear structures

  };

  template <typename Data>
  class SortableLinearContainer : virtual public MutableLinearContainer<Data> {
    // Must extend MutableLinearContainer<Data>
    // Extends MutableLinearContainer with sorting capabilities

  private:

    // ...

  protected:

    // ...

  public:

    // Destructor
    virtual ~SortableLinearContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    SortableLinearContainer& operator=(const SortableLinearContainer&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not be possible.
    SortableLinearContainer& operator=(SortableLinearContainer&&) noexcept = delete;

    /* ************************************************************************ */

    // Specific member function

    virtual void Sort() = 0;  // Pure virtual function to sort the container elements

  protected:

    // Auxiliary member functions

    // ...

  };

  /* ************************************************************************** */

}

#include "linear.cpp"  // Include implementation file

#endif