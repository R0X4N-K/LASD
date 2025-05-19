#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

#include <functional>
#include "testable.hpp"

namespace lasd {

template <typename Data>
class TraversableContainer : public TestableContainer<Data>{
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  ~TraversableContainer();

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.

  TraversableContainer<Data>& operator = (const TestableContainer<Data>&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.

  TraversableContainer<Data>& operator = (TestableContainer<Data>&&) noexcept = delete;

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.

  bool operator == (TraversableContainer<Data>&) const noexcept = delete;
  bool operator != (TraversableContainer<Data>&) const noexcept = delete;

  // Specific member function

  using TraverseFun = std::function<void(const Data &)>;

  virtual void Traverse(TraverseFun) const = 0;
  // type Traverse(arguments) specifiers;

  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator>, Accumulator) const;
  // type Fold(arguments) specifiers;


  // Specific member function (inherited from TestableContainer)

  inline bool Exists(const Data &) const noexcept override;
};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : public TraversableContainer<Data> {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  ~PreOrderTraversableContainer();


  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.

  PreOrderTraversableContainer<Data>& operator = (const TraversableContainer<Data>&) = delete;
  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.

  PreOrderTraversableContainer<Data>& operator = (TraversableContainer<Data>&&) noexcept = delete;
  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.

  bool operator == (const PreOrderTraversableContainer<Data>&) const noexcept = delete;
  bool operator != (const PreOrderTraversableContainer<Data>&) const noexcept = delete;

  // Specific member function

  // using typename TraversableContainer<Data>::TraverseFun;
  using TraverseFun = std::function<void(const Data &)>;
  
  // type PreOrderTraverse(arguments) specifiers;

  virtual void PreTraverse(TraverseFun) const = 0;

  // template <typename Accumulator>
  // using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  // template <typename Accumulator>
  // type PreOrderFold(arguments) specifiers;


  // Specific member function (inherited from TraversableContainer)
  

  // type Traverse(arguments) specifiers; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~PostOrderTraversableContainer() specifiers

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  // using typename TraversableContainer<Data>::TraverseFun;

  // type PostOrderTraverse(arguments) specifiers;

  // template <typename Accumulator>
  // using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  // template <typename Accumulator>
  // type PostOrderFold(arguments) specifiers;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // type Traverse(arguments) specifiers; // Override TraversableContainer member

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif
