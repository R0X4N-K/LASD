#ifndef TESTABLE_HPP
#define TESTABLE_HPP

/* ************************************************************************** */

#include "container.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class TestableContainer : virtual public Container {
    // Must extend Container
    // Abstract base class for containers that can test for element existence

  private:

    // ...

  protected:

    // ...

  public:

    // Destructor
    virtual ~TestableContainer() = default;

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.

    TestableContainer<Data>& operator = (const TestableContainer<Data>&) = delete;  // Disables copy assignment

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.

    TestableContainer<Data>& operator = (TestableContainer<Data>&&) noexcept = delete;  // Disables move assignment


    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.


    bool operator == (const TestableContainer<Data>&) const noexcept = delete;  // Disables equality comparison
    bool operator != (const TestableContainer<Data>&) const noexcept = delete;  // Disables inequality comparison

    // Specific member function
    // type Exists(argument) specifiers; // (concrete function should not throw exceptions)

    virtual bool Exists(const Data&) const noexcept = 0;  // Pure virtual function to check if an element exists in the container
  };


}

#endif