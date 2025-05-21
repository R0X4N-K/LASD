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
    virtual const Data& operator[](const ulong) const = 0;

    // type Front() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
    virtual const Data& Front() const = 0;

    // type Back() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
    virtual const Data& Back() const = 0;

    /* ************************************************************************ */

    // Specific member function (inherited from TraversableContainer)

    using typename TraversableContainer<Data>::TraverseFun;

    void Traverse(TraverseFun) const override;

    /* ************************************************************************ */

    // Specific member function (inherited from PreOrderTraversableContainer)

    void PreOrderTraverse(TraverseFun) const override;

    /* ************************************************************************ */

    // Specific member function (inherited from PostOrderTraversableContainer)

    void PostOrderTraverse(TraverseFun) const override;

  };

  /* ************************************************************************** */

  template <typename Data>
  class MutableLinearContainer : virtual public LinearContainer<Data>,
    virtual public PreOrderMappableContainer<Data>,
    virtual public PostOrderMappableContainer<Data> {
    // Must extend LinearContainer<Data>,
    //             PreOrderMappableContainer<Data>,
    //             PostOrderMappableContainer<Data>

  private:

    // ...

  protected:

    // ...

  public:

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
    virtual Data& operator[](const ulong) = 0;

    // type Front() specifiers; // (mutable version; concrete function must throw std::length_error when empty)
    virtual Data& Front() = 0;

    // type Back() specifiers; // (mutable version; concrete function must throw std::length_error when empty)
    virtual Data& Back() = 0;

    /* ************************************************************************ */

    // Specific member function (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFun;

    void Map(MapFun) override;

    /* ************************************************************************ */

    // Specific member function (inherited from PreOrderMappableContainer)

    void PreOrderMap(MapFun) override;

    /* ************************************************************************ */

    // Specific member function (inherited from PostOrderMappableContainer)

    void PostOrderMap(MapFun) override;

  };

  template <typename Data>
  class SortableLinearContainer : virtual public MutableLinearContainer<Data> {
    // Must extend MutableLinearContainer<Data>

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

    virtual void Sort() = 0;

  protected:

    // Auxiliary member functions

    // ...

  };

  /* ************************************************************************** */

}

#include "linear.cpp"

#endif