#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class Vector : virtual public MutableLinearContainer<Data>, virtual public ResizableContainer {
    // Must extend MutableLinearContainer<Data>,
    //             ResizableContainer

  private:

    // ...

  protected:

    using Container::size;  // Inherit size member from Container base class

    Data* elements = nullptr;  // Pointer to the dynamically allocated array of elements

    // ...

  public:

    // Default constructor
    Vector() = default;

    /* ************************************************************************ */

    // Specific constructors
    Vector(const ulong);  // A vector with a given initial dimension
    Vector(const TraversableContainer<Data>&);  // A vector obtained from a TraversableContainer
    Vector(MappableContainer<Data>&&) noexcept;  // A vector obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    Vector(const Vector&);

    // Move constructor
    Vector(Vector&&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~Vector();

    /* ************************************************************************ */

    // Copy assignment
    Vector& operator=(const Vector&);

    // Move assignment
    Vector& operator=(Vector&&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const Vector&) const noexcept;
    bool operator!=(const Vector&) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from MutableLinearContainer)

    Data& operator[](const ulong) override;  // Access element at specific index (mutable)

    Data& Front() override;  // Access first element (mutable)

    Data& Back() override;  // Access last element (mutable)

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    const Data& operator[](const ulong) const override;  // Access element at specific index (read-only)

    const Data& Front() const override;  // Access first element (read-only)

    const Data& Back() const override;  // Access last element (read-only)

    /* ************************************************************************ */

    // Specific member function (inherited from ResizableContainer)

    void Resize(const ulong) override;  // Change the capacity of the vector

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    void Clear() override;  // Remove all elements from the vector

  protected:

    // Auxiliary functions, if necessary!

  };

  /* ************************************************************************** */

  template <typename Data>
  class SortableVector : virtual public Vector<Data>, virtual public SortableLinearContainer<Data> {
    // Must extend Vector<Data>,
    //             SortableLinearContainer<Data>
    // Extends Vector with sorting capabilities

  private:

    // ...

  protected:

    using Container::size;  // Inherit size member from Container base class

    // ...

  public:

    // Default constructor
    SortableVector() = default;

    /* ************************************************************************ */

    // Specific constructors
    SortableVector(const ulong);  // A vector with a given initial dimension
    SortableVector(const TraversableContainer<Data>&);  // A vector obtained from a TraversableContainer
    SortableVector(MappableContainer<Data>&&) noexcept;  // A vector obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    SortableVector(const SortableVector&);

    // Move constructor
    SortableVector(SortableVector&&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~SortableVector() = default;

    /* ************************************************************************ */

    // Copy assignment
    SortableVector& operator=(const SortableVector&);

    // Move assignment
    SortableVector& operator=(SortableVector&&) noexcept;

    /* ************************************************************************ */

    // Specific member function (inherited from SortableLinearContainer)

    void Sort() override;  // Sort elements in the vector

  protected:

    // Auxiliary functions for Sort
    void InsertionSort(Data*, ulong);  // Helper method implementing insertion sort algorithm

  };

  /* ************************************************************************** */

}

#include "vector.cpp"  // Include implementation file

#endif