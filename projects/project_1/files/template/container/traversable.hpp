#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

#include <functional>
#include "testable.hpp"

namespace lasd {

  template <typename Data>
  class TraversableContainer : public TestableContainer<Data> {
    // Must extend TestableContainer<Data>

  private:

    // ...

  protected:

    // ...

  public:

    // Destructor
    virtual ~TraversableContainer() = default;

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    TraversableContainer<Data>& operator = (const TraversableContainer<Data>&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    TraversableContainer<Data>& operator = (TraversableContainer<Data>&&) noexcept = delete;

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator == (const TraversableContainer<Data>&) const noexcept = delete;
    bool operator != (const TraversableContainer<Data>&) const noexcept = delete;

    // Specific member function
    using TraverseFun = std::function<void(const Data&)>;
    virtual void Traverse(TraverseFun) const = 0;

    template <typename Accumulator>
    using FoldFun = std::function<Accumulator(const Data&, const Accumulator&)>;

    template <typename Accumulator>
    Accumulator Fold(FoldFun<Accumulator>, Accumulator) const = 0;

    // Specific member function (inherited from TestableContainer)
    inline bool Exists(const Data&) const noexcept override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class PreOrderTraversableContainer : public virtual TraversableContainer<Data> {
    // Must extend TraversableContainer<Data>

  private:

    // ...

  protected:

    // ...

  public:

    // Destructor
    virtual ~PreOrderTraversableContainer() = default;

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    PreOrderTraversableContainer<Data>& operator = (const PreOrderTraversableContainer<Data>&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    PreOrderTraversableContainer<Data>& operator = (PreOrderTraversableContainer<Data>&&) noexcept = delete;

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator == (const PreOrderTraversableContainer<Data>&) const noexcept = delete;
    bool operator != (const PreOrderTraversableContainer<Data>&) const noexcept = delete;

    // Specific member function
    using typename TraversableContainer<Data>::TraverseFun;
    virtual void PreOrderTraverse(TraverseFun) const = 0;

    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

    template <typename Accumulator>
    virtual Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const = 0;

    // Specific member function (inherited from TraversableContainer)
    virtual void Traverse(TraverseFun) const override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class PostOrderTraversableContainer : public virtual TraversableContainer<Data> {
    // Must extend TraversableContainer<Data>

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
    PostOrderTraversableContainer<Data>& operator = (const PostOrderTraversableContainer<Data>&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    PostOrderTraversableContainer<Data>& operator = (PostOrderTraversableContainer<Data>&&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator == (const PostOrderTraversableContainer<Data>&) const noexcept = delete;
    bool operator != (const PostOrderTraversableContainer<Data>&) const noexcept = delete;

    /* ************************************************************************ */

    // Specific member function
    using typename TraversableContainer<Data>::TraverseFun;
    virtual void PostOrderTraverse(TraverseFun) const = 0;

    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

    template <typename Accumulator>
    virtual Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator) const = 0;

    /* ************************************************************************ */

    // Specific member function (inherited from TraversableContainer)
    virtual void Traverse(TraverseFun) const override;
  };

  /* ************************************************************************** */

}

#include "traversable.cpp"

#endif