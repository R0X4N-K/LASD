#ifndef MYLINEARTEST_HPP
#define MYLINEARTEST_HPP

#include "../../container/linear.hpp"

/* ************************************************************************** */

// Extended LinearContainer tests

// Test accessing boundary elements (first and last)
template <typename Data>
void AccessBoundaryElements(uint& testnum, uint& testerr, const lasd::LinearContainer<Data>& con) {
  if (con.Empty()) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Boundary access test skipped - container is empty" << std::endl;
    return;
  }
  
  bool tst;
  
  // Access first element with operator[] and Front()
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Boundary test: Front() == operator[0]: ";
    tst = (con.Front() == con[0]);
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
  
  // Access last element with operator[] and Back()
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Boundary test: Back() == operator[Size()-1]: ";
    tst = (con.Back() == con[con.Size() - 1]);
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

// Test accessing out-of-range elements
template <typename Data>
void AccessOutOfRange(uint& testnum, uint& testerr, const lasd::LinearContainer<Data>& con) {
  bool tst;
  
  // Try to access with index = Size()
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Out-of-range test with index = Size(): ";
    Data val = con[con.Size()];
    std::cout << "No exception thrown: Error!" << std::endl;
    tst = false;
  }
  catch (std::out_of_range& exc) {
    std::cout << "std::out_of_range exception correctly thrown: Correct!" << std::endl;
    tst = true;
  }
  catch (std::exception& exc) {
    std::cout << "Wrong exception type: " << exc.what() << ": Error!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint)tst);
  
  // Try to access with very large index
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Out-of-range test with large index: ";
    Data val = con[con.Size() + 1000];
    std::cout << "No exception thrown: Error!" << std::endl;
    tst = false;
  }
  catch (std::out_of_range& exc) {
    std::cout << "std::out_of_range exception correctly thrown: Correct!" << std::endl;
    tst = true;
  }
  catch (std::exception& exc) {
    std::cout << "Wrong exception type: " << exc.what() << ": Error!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint)tst);
}

// Test Front/Back on empty container
template <typename Data>
void AccessEmptyContainer(uint& testnum, uint& testerr, const lasd::LinearContainer<Data>& con) {
  if (!con.Empty()) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Empty container test skipped - container is not empty" << std::endl;
    return;
  }
  
  bool tst;
  
  // Try to access Front() on empty container
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Front() on empty container: ";
    Data val = con.Front();
    std::cout << "No exception thrown: Error!" << std::endl;
    tst = false;
  }
  catch (std::length_error& exc) {
    std::cout << "std::length_error exception correctly thrown: Correct!" << std::endl;
    tst = true;
  }
  catch (std::exception& exc) {
    std::cout << "Wrong exception type: " << exc.what() << ": Error!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint)tst);
  
  // Try to access Back() on empty container
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Back() on empty container: ";
    Data val = con.Back();
    std::cout << "No exception thrown: Error!" << std::endl;
    tst = false;
  }
  catch (std::length_error& exc) {
    std::cout << "std::length_error exception correctly thrown: Correct!" << std::endl;
    tst = true;
  }
  catch (std::exception& exc) {
    std::cout << "Wrong exception type: " << exc.what() << ": Error!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint)tst);
}

/* ************************************************************************** */

// Extended MutableLinearContainer tests

// Test Map consistency with direct modification
template <typename Data>
void MapConsistency(uint& testnum, uint& testerr, lasd::MutableLinearContainer<Data>& con, const Data& increment) {
  if (con.Empty()) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Map consistency test skipped - container is empty" << std::endl;
    return;
  }
  
  bool tst = true;
  
  // Create a copy of the container for comparison
  lasd::Vector<Data> expected(con.Size());
  for (ulong i = 0; i < con.Size(); i++) {
    expected[i] = con[i] + increment;
  }
  
  // Apply Map to increment all values
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Map consistency test: ";
    con.Map([&increment](Data& val) {
      val = val + increment;
    });
    
    // Check if all elements were correctly incremented
    for (ulong i = 0; i < con.Size(); i++) {
      if (con[i] != expected[i]) {
        tst = false;
        break;
      }
    }
    
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

// Test PreOrderMap and PostOrderMap behavior
template <typename Data>
void MapOrderConsistency(uint& testnum, uint& testerr, lasd::MutableLinearContainer<Data>& con) {
  if (con.Empty() || con.Size() == 1) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Map order test skipped - container has fewer than 2 elements" << std::endl;
    return;
  }
  
  // Test that PreOrderMap processes elements from first to last
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") PreOrderMap processing order: ";
  bool preOrderCorrect = true;
  
  try {
    ulong expectedIndex = 0;
    con.PreOrderMap([&con, &expectedIndex, &preOrderCorrect](Data& val) {
      if (val != con[expectedIndex]) {
        preOrderCorrect = false;
      }
      expectedIndex++;
    });
    
    std::cout << (preOrderCorrect ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    preOrderCorrect = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  testerr += (1 - (uint)preOrderCorrect);
  
  // Test that PostOrderMap processes elements from last to first
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") PostOrderMap processing order: ";
  bool postOrderCorrect = true;
  
  try {
    ulong expectedIndex = con.Size() - 1;
    con.PostOrderMap([&con, &expectedIndex, &postOrderCorrect](Data& val) {
      if (val != con[expectedIndex]) {
        postOrderCorrect = false;
      }
      expectedIndex--;
    });
    
    std::cout << (postOrderCorrect ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    postOrderCorrect = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  testerr += (1 - (uint)postOrderCorrect);
}

// Test setting boundary elements
template <typename Data>
void SetBoundaryElements(uint& testnum, uint& testerr, lasd::MutableLinearContainer<Data>& con, const Data& frontVal, const Data& backVal) {
  if (con.Empty()) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Set boundary elements test skipped - container is empty" << std::endl;
    return;
  }
  
  bool tst1, tst2;
  
  // Set first element with operator[] and check with Front()
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Set first element consistency: ";
    con[0] = frontVal;
    tst1 = (con.Front() == frontVal);
    std::cout << (tst1 ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst1 = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  testerr += (1 - (uint)tst1);
  
  // Set last element with operator[] and check with Back()
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Set last element consistency: ";
    con[con.Size() - 1] = backVal;
    tst2 = (con.Back() == backVal);
    std::cout << (tst2 ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst2 = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  testerr += (1 - (uint)tst2);
}

/* ************************************************************************** */

// Extended SortableLinearContainer tests

// Test sort on already sorted container
template <typename Data>
void SortAlreadySorted(uint& testnum, uint& testerr, lasd::SortableLinearContainer<Data>& con) {
  if (con.Empty() || con.Size() == 1) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Sort already sorted test skipped - container has fewer than 2 elements" << std::endl;
    return;
  }
  
  bool tst = true;
  
  // Create a copy to verify the container is already sorted
  lasd::Vector<Data> beforeSort(con.Size());
  for (ulong i = 0; i < con.Size(); i++) {
    beforeSort[i] = con[i];
  }
  
  // Check if already sorted
  bool alreadySorted = true;
  for (ulong i = 1; i < con.Size(); i++) {
    if (beforeSort[i-1] > beforeSort[i]) {
      alreadySorted = false;
      break;
    }
  }
  
  if (!alreadySorted) {
    // Sort the container first
    con.Sort();
  }
  
  // Copy the sorted container
  lasd::Vector<Data> expected(con.Size());
  for (ulong i = 0; i < con.Size(); i++) {
    expected[i] = con[i];
  }
  
  // Run Sort() on already sorted container
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Sort on already sorted container: ";
    con.Sort();
    
    // Verify the container is still correctly sorted
    for (ulong i = 0; i < con.Size(); i++) {
      if (con[i] != expected[i]) {
        tst = false;
        break;
      }
    }
    
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

// Test sort with duplicate values
template <typename Data>
void SortWithDuplicates(uint& testnum, uint& testerr, lasd::SortableLinearContainer<Data>& con, const Data& duplicateVal) {
  if (con.Empty() || con.Size() < 3) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Sort with duplicates test skipped - container has fewer than 3 elements" << std::endl;
    return;
  }
  
  bool tst = true;
  
  // Insert duplicate values at specific positions
  ulong pos1 = con.Size() / 3;
  ulong pos2 = (con.Size() * 2) / 3;
  
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Sort with duplicate values: ";
    
    // Insert duplicates
    con[pos1] = duplicateVal;
    con[pos2] = duplicateVal;
    
    // Sort the container
    con.Sort();
    
    // Verify the container is correctly sorted
    for (ulong i = 1; i < con.Size(); i++) {
      if (con[i-1] > con[i]) {
        tst = false;
        break;
      }
    }
    
    // Check that duplicates are adjacent
    bool duplicatesFound = false;
    for (ulong i = 1; i < con.Size(); i++) {
      if (con[i-1] == con[i] && con[i] == duplicateVal) {
        duplicatesFound = true;
        break;
      }
    }
    
    tst = tst && duplicatesFound;
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

/* ************************************************************************** */

#endif