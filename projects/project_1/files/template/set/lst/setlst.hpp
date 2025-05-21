#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class SetLst : virtual public Set<Data>,
    virtual protected List<Data>
  {
    // Must extend Set<Data>,
    //             List<Data>

  private:
    // ...

  protected:
    using Container::size;
    using List<Data>::head;
    using List<Data>::tail;

  public:
    // Default constructor
    SetLst() = default;

    /* ************************************************************************ */

    // Specific constructors
    SetLst(const TraversableContainer<Data>&);  // A set obtained from a TraversableContainer
    SetLst(MappableContainer<Data>&&) noexcept; // A set obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    SetLst(const SetLst&);

    // Move constructor
    SetLst(SetLst&&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~SetLst() = default;

    /* ************************************************************************ */

    // Copy assignment
    SetLst& operator=(const SetLst&);

    // Move assignment
    SetLst& operator=(SetLst&&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const SetLst&) const noexcept;
    bool operator!=(const SetLst&) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from OrderedDictionaryContainer)

    const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data MinNRemove() override;       // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemoveMin() override;        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

    const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data MaxNRemove() override;       // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemoveMax() override;        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

    const Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    Data PredecessorNRemove(const Data&) override;       // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    void RemovePredecessor(const Data&) override;        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

    const Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    Data SuccessorNRemove(const Data&) override;       // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    void RemoveSuccessor(const Data&) override;        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

    /* ************************************************************************ */

    // Specific member functions (inherited from DictionaryContainer)

    bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
    bool Insert(Data&&) override;      // Override DictionaryContainer member (move of the value)
    bool Remove(const Data&) override; // Override DictionaryContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from TestableContainer)

    virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    using List<Data>::operator[];
    using List<Data>::Front;
    using List<Data>::Back;

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    using List<Data>::Clear;

  protected:
    // Auxiliary functions for binary search operations
    typedef typename List<Data>::Node Node;

    // Binary search (finds a node with the data or its insertion position)
    Node* FindNodeWithBinarySearch(const Data&) const;

    // Find successor node
    Node* FindSuccessorNode(const Data&) const;

    // Find predecessor node
    Node* FindPredecessorNode(const Data&) const;

    // Insert maintaining order
    bool InsertInOrder(Node*, const Data&);
    bool InsertInOrder(Node*, Data&&);
  };

  /* ************************************************************************** */

}

#include "setlst.cpp"

#endif