#ifndef SET_HPP
#define SET_HPP

/* ************************************************************************** */

#include "../container/dictionary.hpp"
#include "../container/linear.hpp"
#include "../container/traversable.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Set : virtual public OrderedDictionaryContainer<Data>,
              virtual public LinearContainer<Data>,
              virtual public ClearableContainer
  {
    // Must extend OrderedDictionaryContainer<Data>,
    //             LinearContainer<Data>,
    //             ClearableContainer

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~Set() = default;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.
    Set &operator=(const Set &) = delete; // Disable copy assignment for abstract base

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.
    Set &operator=(Set &&) noexcept = delete; // Disable move assignment for abstract base

    using DictionaryContainer<Data>::Exists; // Inherit Exists method from DictionaryContainer
  };

  /* ************************************************************************** */

}

#endif