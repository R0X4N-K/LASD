#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"
#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data> {
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~DictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  DictionaryContainer& operator=(const DictionaryContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  DictionaryContainer& operator=(DictionaryContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator==(const DictionaryContainer&) const noexcept = delete;
  
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator!=(const DictionaryContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Insert(argument) specifiers; // Copy of the value
  virtual bool Insert(const Data&) = 0;
  
  // type Insert(argument) specifiers; // Move of the value
  virtual bool Insert(Data&&) = 0;
  
  // type Remove(argument) specifiers;
  virtual bool Remove(const Data&) = 0;

  // type InsertAll(argument) specifiers; // Copy of the value; From TraversableContainer; True if all are inserted
  virtual bool InsertAll(const TraversableContainer<Data>&);
  
  // type InsertAll(argument) specifiers; // Move of the value; From MappableContainer; True if all are inserted
  virtual bool InsertAll(MappableContainer<Data>&&);
  
  // type RemoveAll(argument) specifiers; // From TraversableContainer; True if all are removed
  virtual bool RemoveAll(const TraversableContainer<Data>&);

  // type InsertSome(argument) specifiers; // Copy of the value; From TraversableContainer; True if some is inserted
  virtual bool InsertSome(const TraversableContainer<Data>&);
  
  // type InsertSome(argument) specifiers; // Move of the value; From MappableContainer; True if some is inserted
  virtual bool InsertSome(MappableContainer<Data>&&);
  
  // type RemoveSome(argument) specifiers; // From TraversableContainer; True if some is removed
  virtual bool RemoveSome(const TraversableContainer<Data>&);

};

/* ************************************************************************** */

template <typename Data>
class OrderedDictionaryContainer : virtual public DictionaryContainer<Data> {
  // Must extend DictionaryContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~OrderedDictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  OrderedDictionaryContainer& operator=(const OrderedDictionaryContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  OrderedDictionaryContainer& operator=(OrderedDictionaryContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator==(const OrderedDictionaryContainer&) const noexcept = delete;
  
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator!=(const OrderedDictionaryContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Min(argument) specifiers; // (concrete function must throw std::length_error when empty)
  virtual const Data& Min() const = 0; // Returns the minimum value
  
  // type MinNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  virtual Data MinNRemove() = 0; // Returns and removes the minimum value
  
  // type RemoveMin(argument) specifiers; // (concrete function must throw std::length_error when empty)
  virtual void RemoveMin() = 0; // Removes the minimum value

  // type Max(argument) specifiers; // (concrete function must throw std::length_error when empty)
  virtual const Data& Max() const = 0; // Returns the maximum value
  
  // type MaxNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  virtual Data MaxNRemove() = 0; // Returns and removes the maximum value
  
  // type RemoveMax(argument) specifiers; // (concrete function must throw std::length_error when empty)
  virtual void RemoveMax() = 0; // Removes the maximum value

  // type Predecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  virtual const Data& Predecessor(const Data&) const = 0; // Returns the predecessor of a value
  
  // type PredecessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  virtual Data PredecessorNRemove(const Data&) = 0; // Returns and removes the predecessor of a value
  
  // type RemovePredecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  virtual void RemovePredecessor(const Data&) = 0; // Removes the predecessor of a value

  // type Successor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  virtual const Data& Successor(const Data&) const = 0; // Returns the successor of a value
  
  // type SuccessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  virtual Data SuccessorNRemove(const Data&) = 0; // Returns and removes the successor of a value
  
  // type RemoveSuccessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  virtual void RemoveSuccessor(const Data&) = 0; // Removes the successor of a value

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif