#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

#include <functional>
#include "testable.hpp"

namespace lasd
{

  template <typename Data>
  class TraversableContainer : virtual public TestableContainer<Data>
  {
    // Must extend TestableContainer<Data>
    // Abstract base class for containers that can be traversed

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~TraversableContainer() = default;

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    TraversableContainer<Data> &operator=(const TraversableContainer<Data> &) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    TraversableContainer<Data> &operator=(TraversableContainer<Data> &&) noexcept = delete;

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator==(const TraversableContainer<Data> &) const noexcept = delete;
    bool operator!=(const TraversableContainer<Data> &) const noexcept = delete;

    // Specific member function
    using TraverseFun = std::function<void(const Data &)>; // Function type for traversal operations
    virtual void Traverse(TraverseFun) const = 0;          // Apply function to each element (read-only)

    template <typename Accumulator>
    using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>; // Function type for fold operations

    template <typename Accumulator>
    Accumulator Fold(FoldFun<Accumulator>, Accumulator) const; // Apply fold operation across all elements

    // Specific member function (inherited from TestableContainer)
    inline bool Exists(const Data &) const noexcept override; // Implementation of element existence check
  };

  /* ************************************************************************** */

  template <typename Data>
  class PreOrderTraversableContainer : public virtual TraversableContainer<Data>
  {
    // Must extend TraversableContainer<Data>
    // Supports pre-order traversal of elements (root/current before children/subsequent)

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~PreOrderTraversableContainer() = default;

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    PreOrderTraversableContainer<Data> &operator=(const PreOrderTraversableContainer<Data> &) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    PreOrderTraversableContainer<Data> &operator=(PreOrderTraversableContainer<Data> &&) noexcept = delete;

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator==(const PreOrderTraversableContainer<Data> &) const noexcept = delete;
    bool operator!=(const PreOrderTraversableContainer<Data> &) const noexcept = delete;

    // Specific member function
    using typename TraversableContainer<Data>::TraverseFun;
    virtual void PreOrderTraverse(TraverseFun) const = 0; // Pure virtual for pre-order traversal

    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

    template <typename Accumulator>
    Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const; // Fold operation in pre-order

    // Specific member function (inherited from TraversableContainer)
    virtual void Traverse(TraverseFun) const override; // Default traversal implementation
  };

  /* ************************************************************************** */

  template <typename Data>
  class PostOrderTraversableContainer : public virtual TraversableContainer<Data>
  {
    // Must extend TraversableContainer<Data>
    // Supports post-order traversal of elements (children/subsequent before root/current)

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~PostOrderTraversableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    PostOrderTraversableContainer<Data> &operator=(const PostOrderTraversableContainer<Data> &) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    PostOrderTraversableContainer<Data> &operator=(PostOrderTraversableContainer<Data> &&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator==(const PostOrderTraversableContainer<Data> &) const noexcept = delete;
    bool operator!=(const PostOrderTraversableContainer<Data> &) const noexcept = delete;

    /* ************************************************************************ */

    // Specific member function
    using typename TraversableContainer<Data>::TraverseFun;
    virtual void PostOrderTraverse(TraverseFun) const = 0; // Pure virtual for post-order traversal

    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

    template <typename Accumulator>
    Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator) const; // Fold operation in post-order

    /* ************************************************************************ */

    // Specific member function (inherited from TraversableContainer)
    virtual void Traverse(TraverseFun) const override; // Default traversal implementation
  };

  /* ************************************************************************** */

}

#include "traversable.cpp" // Include implementation file

#endif