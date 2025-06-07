#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class List : virtual public MutableLinearContainer<Data>, virtual public ClearableContainer
  {
    // Must extend MutableLinearContainer<Data>,
    //             ClearableContainer
    // Implementation of a singly linked list data structure

  private:
    // ...

  protected:
    using Container::size; // Inherit size member from Container base class

    struct Node
    {
      // Node structure for the linked list implementation

      // Data
      Data element;         // Value stored in the node
      Node *next = nullptr; // Pointer to the next node in the list

      /* ********************************************************************** */

      // Default constructor
      Node() = default;

      // Specific constructors
      Node(const Data &data) : element(data) {}                // Construct node with copied data
      Node(Data &&data) noexcept : element(std::move(data)) {} // Construct node with moved data

      /* ********************************************************************** */

      // Copy constructor
      Node(const Node &other) : element(other.element), next(nullptr) {} // Create copy with no link to next node

      // Move constructor
      Node(Node &&other) noexcept : element(std::move(other.element)), next(other.next)
      {
        other.next = nullptr; // Ensure other node no longer points to the moved next node
      }

      /* ********************************************************************** */

      // Destructor
      virtual ~Node() = default;

      /* ********************************************************************** */

      // Comparison operators
      bool operator==(const Node &other) const noexcept
      {
        return (element == other.element); // Nodes are equal if their elements are equal
      }

      bool operator!=(const Node &other) const noexcept
      {
        return !(*this == other); // Leverages equality operator for inequality check
      }

      /* ********************************************************************** */

      // Specific member functions

      // Clone method - creates a deep copy of the current node and its chain
      Node *Clone() const
      {
        Node *temp = new Node(element); // Create new node with copied element
        if (next != nullptr)
        {
          temp->next = next->Clone(); // Recursively clone all subsequent nodes
        }
        return temp;
      }
    };

    Node *head = nullptr; // Pointer to first node in the list
    Node *tail = nullptr; // Pointer to last node in the list for efficient back operations

  public:
    // Default constructor
    List() = default;

    /* ************************************************************************ */

    // Specific constructor
    List(const TraversableContainer<Data> &container);  // A list obtained from a TraversableContainer
    List(MappableContainer<Data> &&container) noexcept; // A list obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    List(const List &other);

    // Move constructor
    List(List &&other) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~List();

    /* ************************************************************************ */

    // Copy assignment
    List &operator=(const List &other);

    // Move assignment
    List &operator=(List &&other) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const List &other) const noexcept;
    bool operator!=(const List &other) const noexcept;

    /* ************************************************************************ */

    // Specific member functions

    void InsertAtFront(const Data &data);     // Insert copy of data at the beginning of the list
    void InsertAtFront(Data &&data) noexcept; // Insert moved data at the beginning of the list
    void RemoveFromFront();                   // Remove first element (must throw std::length_error when empty)
    Data FrontNRemove();                      // Remove and return first element (must throw std::length_error when empty)

    void InsertAtBack(const Data &data);     // Insert copy of data at the end of the list
    void InsertAtBack(Data &&data) noexcept; // Insert moved data at the end of the list
    void RemoveFromBack();                   // Remove last element (must throw std::length_error when empty)
    Data BackNRemove();                      // Remove and return last element (must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from MutableLinearContainer)

    Data &operator[](const ulong index) override; // Access element at index (mutable version)

    Data &Front() override; // Access first element (mutable version)

    Data &Back() override; // Access last element (mutable version)

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    const Data &operator[](const ulong index) const override; // Access element at index (non-mutable version)

    const Data &Front() const override; // Access first element (non-mutable version)

    const Data &Back() const override; // Access last element (non-mutable version)

    /* ************************************************************************ */

    // Specific member function (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFun;

    void Map(MapFun) override; // Apply function to all elements

    /* ************************************************************************ */

    // Specific member function (inherited from PreOrderMappableContainer)

    void PreOrderMap(MapFun) override; // Apply function to all elements in pre-order (front to back)

    /* ************************************************************************ */

    // Specific member function (inherited from PostOrderMappableContainer)

    void PostOrderMap(MapFun) override; // Apply function to all elements in post-order (back to front)

    /* ************************************************************************ */

    // Specific member function (inherited from TraversableContainer)

    using typename TraversableContainer<Data>::TraverseFun;

    void Traverse(TraverseFun) const override; // Apply function to all elements (non-modifying)

    /* ************************************************************************ */

    // Specific member function (inherited from PreOrderTraversableContainer)

    void PreOrderTraverse(TraverseFun) const override; // Apply function to all elements in pre-order (front to back)

    /* ************************************************************************ */

    // Specific member function (inherited from PostOrderTraversableContainer)

    void PostOrderTraverse(TraverseFun) const override; // Apply function to all elements in post-order (back to front)

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    void Clear() override; // Remove all elements from the list

  protected:
    // Auxiliary function to find node at a specific position
    Node *GetNodeAt(ulong index) const; // Helper to retrieve node at given position
  };

  /* ************************************************************************** */

}

#include "list.cpp" // Include implementation file

#endif