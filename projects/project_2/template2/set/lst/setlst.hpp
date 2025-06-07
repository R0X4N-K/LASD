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
    // Implementation of a set using a linked list as underlying container
    // Elements are maintained in sorted order for efficient operations

  private:
    // ...

  protected:
    using Container::size;  // Access to size member from Container
    using List<Data>::head;  // Access to head node pointer from List
    using List<Data>::tail;  // Access to tail node pointer from List

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

    const Data& Min() const override;  // Return the smallest element in the set
    Data MinNRemove() override;  // Remove and return the smallest element
    void RemoveMin() override;  // Remove the smallest element

    const Data& Max() const override;  // Return the largest element in the set
    Data MaxNRemove() override;  // Remove and return the largest element
    void RemoveMax() override;  // Remove the largest element

    const Data& Predecessor(const Data&) const override;  // Find the largest element smaller than the given value
    Data PredecessorNRemove(const Data&) override;  // Remove and return the predecessor
    void RemovePredecessor(const Data&) override;  // Remove the predecessor

    const Data& Successor(const Data&) const override;  // Find the smallest element larger than the given value
    Data SuccessorNRemove(const Data&) override;  // Remove and return the successor
    void RemoveSuccessor(const Data&) override;  // Remove the successor

    /* ************************************************************************ */

    // Specific member functions (inherited from DictionaryContainer)

    bool Insert(const Data&) override;  // Add an element if not already present (copy)
    bool Insert(Data&&) override;  // Add an element if not already present (move)
    bool Remove(const Data&) override;  // Remove an element if present

    /* ************************************************************************ */

    // Specific member functions (inherited from TestableContainer)

    virtual bool Exists(const Data&) const noexcept override;  // Check if an element exists in the set

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    using List<Data>::operator[];  // Access elements by index
    using List<Data>::Front;  // Access first element
    using List<Data>::Back;  // Access last element

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    using List<Data>::Clear;  // Remove all elements from the set

  protected:
    // Auxiliary functions for binary search operations
    typedef typename List<Data>::Node Node;  // Use Node type from List

    // Binary search (finds a node with the data or its insertion position)
    Node* FindNodeWithBinarySearch(const Data&) const;  // Efficiently locate node in sorted list

    // Find successor node
    Node* FindSuccessorNode(const Data&) const;  // Find node containing successor element

    // Find predecessor node
    Node* FindPredecessorNode(const Data&) const;  // Find node containing predecessor element

    // Insert maintaining order
    bool InsertInOrder(Node*, const Data&);  // Insert element (copy) in sorted position
    bool InsertInOrder(Node*, Data&&);  // Insert element (move) in sorted position
  };

  /* ************************************************************************** */

}

#include "setlst.cpp"  // Include implementation file

#endif