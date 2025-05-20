#ifndef TESTABLE_HPP
#define TESTABLE_HPP

/* ************************************************************************** */

#include "container.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class TestableContainer : public Container {
    // Must extend Container

  private:

    // ...

  protected:

    // ...

  public:

    // Destructor
    virtual ~TestableContainer();

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.

    TestableContainer<Data>& operator = (const TestableContainer<Data>&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.

    TestableContainer<Data>& operator = (TestableContainer<Data>&&) noexcept = delete;


    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.


    bool operator == (const TestableContainer<Data>&) const noexcept = delete;
    bool operator != (const TestableContainer<Data>&) const noexcept = delete;

    // Specific member function
    // type Exists(argument) specifiers; // (concrete function should not throw exceptions)

    virtual bool Exists(const Data&) const noexcept = 0;
  };


}

#endif
