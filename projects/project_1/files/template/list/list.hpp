#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class List : virtual public MutableLinearContainer<Data>, virtual public ClearableContainer {
    // Must extend MutableLinearContainer<Data>,
    //             ClearableContainer

  private:

    // ...

  protected:

    using Container::size;

    struct Node {

      // Data
      Data element;
      Node* next = nullptr;

      /* ********************************************************************** */

      // Default constructor
      Node() = default;

      // Specific constructors
      Node(const Data& data) : element(data) {}
      Node(Data&& data) noexcept : element(std::move(data)) {}

      /* ********************************************************************** */

      // Copy constructor
      Node(const Node& other) : element(other.element), next(nullptr) {}

      // Move constructor
      Node(Node&& other) noexcept : element(std::move(other.element)), next(other.next) {
        other.next = nullptr;
      }

      /* ********************************************************************** */

      // Destructor
      virtual ~Node() = default;

      /* ********************************************************************** */

      // Comparison operators
      bool operator==(const Node& other) const noexcept {
        return (element == other.element);
      }

      bool operator!=(const Node& other) const noexcept {
        return !(*this == other);
      }

      /* ********************************************************************** */

      // Specific member functions

      // Clone method - creates a deep copy of the current node and its chain
      Node* Clone() const {
        Node* temp = new Node(element);
        if (next != nullptr) {
          temp->next = next->Clone();
        }
        return temp;
      }
    };

    Node* head = nullptr;
    Node* tail = nullptr;

  public:

    // Default constructor
    List() = default;

    /* ************************************************************************ */

    // Specific constructor
    List(const TraversableContainer<Data>& container); // A list obtained from a TraversableContainer
    List(MappableContainer<Data>&& container) noexcept; // A list obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    List(const List& other);

    // Move constructor
    List(List&& other) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~List();

    /* ************************************************************************ */

    // Copy assignment
    List& operator=(const List& other);

    // Move assignment
    List& operator=(List&& other) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const List& other) const noexcept;
    bool operator!=(const List& other) const noexcept;

    /* ************************************************************************ */

    // Specific member functions

    void InsertAtFront(const Data& data); // Copy of the value
    void InsertAtFront(Data&& data) noexcept; // Move of the value
    void RemoveFromFront(); // (must throw std::length_error when empty)
    Data FrontNRemove(); // (must throw std::length_error when empty)

    void InsertAtBack(const Data& data); // Copy of the value
    void InsertAtBack(Data&& data) noexcept; // Move of the value
    void RemoveFromBack(); // (must throw std::length_error when empty)
    Data BackNRemove(); // (must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from MutableLinearContainer)

    Data& operator[](const ulong index) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

    Data& Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

    Data& Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    const Data& operator[](const ulong index) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

    const Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

    const Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member function (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFun;

    void Map(MapFun) override; // Override MappableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from PreOrderMappableContainer)

    void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from PostOrderMappableContainer)

    void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from TraversableContainer)

    using typename TraversableContainer<Data>::TraverseFun;

    void Traverse(TraverseFun) const override; // Override TraversableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from PreOrderTraversableContainer)

    void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from PostOrderTraversableContainer)

    void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    void Clear() override; // Override ClearableContainer member

  protected:

    // Auxiliary function to find node at a specific position
    Node* GetNodeAt(ulong index) const;

  };

  /* ************************************************************************** */

}

#include "list.cpp"

#endif