#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class SetVec : virtual public Set<Data>,
    virtual protected Vector<Data> {
    // Must extend Set<Data>,
    //             Vector<Data>

  private:

    // ...

  protected:

    using Vector<Data>::elements;
    using Container::size;

    // ...

  public:

    // Default constructor
    SetVec() = default;

    /* ************************************************************************ */

    // Specific constructors
    SetVec(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
    SetVec(MappableContainer<Data>&&) noexcept; // A set obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    SetVec(const SetVec&);

    // Move constructor
    SetVec(SetVec&&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~SetVec() = default;

    /* ************************************************************************ */

    // Copy assignment
    SetVec& operator=(const SetVec&);

    // Move assignment
    SetVec& operator=(SetVec&&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const SetVec&) const noexcept;
    bool operator!=(const SetVec&) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from OrderedDictionaryContainer)

    const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

    const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

    const Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

    const Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

    /* ************************************************************************ */

    // Specific member functions (inherited from DictionaryContainer)

    bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
    bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
    bool Remove(const Data&) override; // Override DictionaryContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    using Vector<Data>::operator[];
    using Vector<Data>::Front;
    using Vector<Data>::Back;

    /* ************************************************************************** */

    // Specific member function (inherited from TestableContainer)

    virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    virtual inline void Clear() override;

  protected:

    // Auxiliary functions

    // Binary search function for finding an element or its insertion point
    ulong BinarySearch(const Data&) const;

    // Find the position of the predecessor to a given data value
    long FindPredecessorPos(const Data&) const;

    // Find the position of the successor to a given data value
    long FindSuccessorPos(const Data&) const;

    // Shifts elements right from a given position
    void ShiftRight(ulong);

    // Shifts elements left from a given position
    void ShiftLeft(ulong);

    // Sorts the vector to maintain order when needed
    void Sort();

  };

  /* ************************************************************************** */

}

#include "setvec.cpp"

#endif