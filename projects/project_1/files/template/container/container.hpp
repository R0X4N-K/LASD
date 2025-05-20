
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "sys/types.h"

namespace lasd {

  class Container {

  private:

    ulong size;

  protected:
    // Default constructor
    // Container() specifiers;
    Container() { size = 0; }

  public:

    virtual ~Container() = default;

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.

    Container& operator = (const Container&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.

    Container& operator = (Container&&) noexcept = delete;

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

    bool operator == (const Container&) const noexcept = delete;
    bool operator !=(const Container&) const noexcept = delete;

    // Specific member functions

    // type Empty() specifiers; // (concrete function should not throw exceptions)

    // type Size() specifiers; // (concrete function should not throw exceptions)

    inline virtual bool Empty() const noexcept {
      return (size == 0);
    }

    inline virtual ulong Size() const noexcept {
      return size;
    }
  };


  class ClearableContainer : public Container {
    // Must extend Container

  private:

    // ...

  protected:

    // ...

  public:

    // Destructor
    // ~ClearableContainer() specifiers
    virtual ~ClearableContainer() = default;


    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.

    ClearableContainer& operator=(const ClearableContainer&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.

    ClearableContainer& operator=(ClearableContainer&&) noexcept = delete;

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

    bool operator==(const ClearableContainer&) const noexcept = delete;
    bool operator!=(const ClearableContainer&) const noexcept = delete;
    // Specific member functions

    // type Clear() specifiers;
    virtual void Clear() = 0;
  };


  class ResizableContainer : public ClearableContainer {
    // Must extend ClearableContainer

  private:

    // ...

  protected:

    // ...

  public:

    // Destructor
    // ~ResizableContainer() specifiers
    virtual ~ResizableContainer();

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    ResizableContainer& operator=(const ResizableContainer&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.

    ResizableContainer& operator=(ResizableContainer&&) noexcept = delete;
    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

    bool operator == (const ResizableContainer&) const noexcept = delete;
    bool operator != (const ResizableContainer&) const noexcept = delete;
    // Specific member functions

    // type Resize(argument) specifiers;
    virtual void Resize(ulong) = 0; //implementare

    // Specific member function (inherited from ClearableContainer)

    // type Clear() specifiers; // Override ClearableContainer member

    inline void Clear() override {
      Resize(0);
    }
  };


}

#endif