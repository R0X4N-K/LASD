
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */


namespace lasd {

/* ************************************************************************** */


class Container {

private:

  unsigned long int size;

protected:

  /* ************************************************************************ */

  // Default constructor
  // Container() specifiers;
  Container(){
    size = 0;
   }
public:

  // Destructor
  // ~Container() specifiers
  ~Container() { }
  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  // type Empty() specifiers; // (concrete function should not throw exceptions)

  // type Size() specifiers; // (concrete function should not throw exceptions)

  unsigned long int Size(){ return size; }

  bool Empty(){
    if(size == 0)
      return true;
    return false;
  }
 
};

/* ************************************************************************** */

class ClearableContainer: public Container{
  // Must extend Container

private:
  
  // ...

protected:

  // ...

public:

  // Destructor
  // ~ClearableContainer() specifiers
  ~ClearableContainer(){}

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  // type Clear() specifiers;
  void Clear();
};

/* ************************************************************************** */

class ResizableContainer: public ClearableContainer{
  // Must extend ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~ResizableContainer() specifiers
  ~ResizableContainer();
  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  // type Resize(argument) specifiers;
  void Resize(unsigned long int newSize); //implementare
  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#endif
