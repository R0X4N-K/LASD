#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class SetVec : virtual public Set<Data>,
                 virtual protected Vector<Data>
  {
    // Must extend Set<Data>,
    //             Vector<Data>

  private:
    // ...

  protected:
    using Vector<Data>::elements; // Access to the array of elements from Vector
    using Container::size;        // Access to size member from Container

    // ...

  public:
    // Default constructor
    SetVec() = default;

    /* ************************************************************************ */

    // Specific constructors
    SetVec(const TraversableContainer<Data> &);  // A set obtained from a TraversableContainer
    SetVec(MappableContainer<Data> &&) noexcept; // A set obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    SetVec(const SetVec &);

    // Move constructor
    SetVec(SetVec &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~SetVec() = default;

    /* ************************************************************************ */

    // Copy assignment
    SetVec &operator=(const SetVec &);

    // Move assignment
    SetVec &operator=(SetVec &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const SetVec &) const noexcept;
    bool operator!=(const SetVec &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from OrderedDictionaryContainer)

    const Data &Min() const override; // Return the smallest element in the set
    Data MinNRemove() override;       // Remove and return the smallest element
    void RemoveMin() override;        // Remove the smallest element

    const Data &Max() const override; // Return the largest element in the set
    Data MaxNRemove() override;       // Remove and return the largest element
    void RemoveMax() override;        // Remove the largest element

    const Data &Predecessor(const Data &) const override; // Find the largest element smaller than the given value
    Data PredecessorNRemove(const Data &) override;       // Remove and return the predecessor
    void RemovePredecessor(const Data &) override;        // Remove the predecessor

    const Data &Successor(const Data &) const override; // Find the smallest element larger than the given value
    Data SuccessorNRemove(const Data &) override;       // Remove and return the successor
    void RemoveSuccessor(const Data &) override;        // Remove the successor

    /* ************************************************************************ */

    // Specific member functions (inherited from DictionaryContainer)

    bool Insert(const Data &) override; // Add an element if not already present (copy)
    bool Insert(Data &&) override;      // Add an element if not already present (move)
    bool Remove(const Data &) override; // Remove an element if present

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    using Vector<Data>::operator[]; // Access elements by index
    using Vector<Data>::Front;      // Access first element
    using Vector<Data>::Back;       // Access last element

    /* ************************************************************************** */

    // Specific member function (inherited from TestableContainer)

    virtual bool Exists(const Data &) const noexcept override; // Check if an element exists in the set

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    virtual inline void Clear() override; // Remove all elements from the set

  protected:
    // Auxiliary functions

    // Binary search function for finding an element or its insertion point
    ulong BinarySearch(const Data &) const; // Efficiently locate elements in sorted array

    // Find the position of the predecessor to a given data value
    long FindPredecessorPos(const Data &) const; // Find index of predecessor element

    // Find the position of the successor to a given data value
    long FindSuccessorPos(const Data &) const; // Find index of successor element

    // Shifts elements right from a given position
    void ShiftRight(ulong); // Make room for insertion by moving elements

    // Shifts elements left from a given position
    void ShiftLeft(ulong); // Close gap after removal by moving elements

    // Sorts the vector to maintain order when needed
    void Sort(); // Ensure elements remain in sorted order
  };

  /* ************************************************************************** */

}

#include "setvec.cpp" // Include implementation file

#endif