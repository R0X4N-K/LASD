#ifndef MYDICTIONARYTEST_HPP
#define MYDICTIONARYTEST_HPP

#include "../../container/dictionary.hpp"
#include "../../vector/vector.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

// Extended DictionaryContainer member functions tests

// Test operation sequence and consistency
template <typename Data>
void InsertRemoveConsistency(uint& testnum, uint& testerr, lasd::DictionaryContainer<Data>& con, const Data& val) {
  bool tst1, tst2, tst3, tst4;
  
  // Insert the value
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Insert-Exists consistency: Value \"" << val << "\" ";
  tst1 = con.Insert(val);
  tst2 = con.Exists(val);
  std::cout << (tst1 ? "was inserted" : "was not inserted") << " and " 
            << (tst2 ? "exists" : "does not exist") << ": ";
  std::cout << ((tst1 && tst2) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!(tst1 && tst2));
  
  // Try inserting again (should fail for sets)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Insert duplicate consistency: Value \"" << val << "\" ";
  tst3 = !con.Insert(val);
  std::cout << (tst3 ? "was correctly rejected" : "was incorrectly inserted again") << ": ";
  std::cout << (tst3 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst3);
  
  // Remove the value
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Remove-Exists consistency: Value \"" << val << "\" ";
  tst1 = con.Remove(val);
  tst2 = !con.Exists(val);
  std::cout << (tst1 ? "was removed" : "was not removed") << " and " 
            << (tst2 ? "no longer exists" : "still exists") << ": ";
  std::cout << ((tst1 && tst2) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!(tst1 && tst2));
  
  // Try removing again (should fail)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Remove non-existent consistency: Value \"" << val << "\" ";
  tst4 = !con.Remove(val);
  std::cout << (tst4 ? "was correctly not removed" : "was incorrectly removed") << ": ";
  std::cout << (tst4 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst4);
}

// Test InsertAll and RemoveAll on empty source
template <typename Data>
void EmptySourceOperations(uint& testnum, uint& testerr, lasd::DictionaryContainer<Data>& con) {
  lasd::List<Data> emptyList;
  bool tst1, tst2, tst3;
  
  // Insert from empty list (should return true)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") InsertAll from empty source: ";
  tst1 = con.InsertAll(emptyList);
  std::cout << (tst1 ? "returned true" : "returned false") << ": ";
  std::cout << (tst1 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst1);
  
  // Remove from empty list (should return true)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") RemoveAll from empty source: ";
  tst2 = con.RemoveAll(emptyList);
  std::cout << (tst2 ? "returned true" : "returned false") << ": ";
  std::cout << (tst2 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst2);
  
  // InsertSome from empty list (should return false)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") InsertSome from empty source: ";
  tst3 = !con.InsertSome(emptyList);
  std::cout << (!tst3 ? "returned true" : "returned false") << ": ";
  std::cout << (tst3 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst3);
}

// Test behavior when all elements are already present or none are present
template <typename Data>
void AllOrNonePresent(uint& testnum, uint& testerr, lasd::DictionaryContainer<Data>& con, const lasd::Vector<Data>& present, const lasd::Vector<Data>& absent) {
  bool tst1, tst2, tst3, tst4;
  
  // InsertAll on already present elements (should return false for sets)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") InsertAll when all elements already exist: ";
  tst1 = !con.InsertAll(present);
  std::cout << (!tst1 ? "correctly returned false" : "incorrectly returned true") << ": ";
  std::cout << (tst1 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst1);
  
  // RemoveAll on already present elements (should return true)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") RemoveAll when all elements exist: ";
  tst2 = con.RemoveAll(present);
  std::cout << (tst2 ? "correctly returned true" : "incorrectly returned false") << ": ";
  std::cout << (tst2 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst2);
  
  // RemoveAll on absent elements (should return false)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") RemoveAll when no elements exist: ";
  tst3 = !con.RemoveAll(absent);
  std::cout << (!tst3 ? "correctly returned false" : "incorrectly returned true") << ": ";
  std::cout << (tst3 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst3);
  
  // InsertAll on absent elements (should return true)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") InsertAll when no elements exist: ";
  tst4 = con.InsertAll(absent);
  std::cout << (tst4 ? "correctly returned true" : "incorrectly returned false") << ": ";
  std::cout << (tst4 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst4);
}

// Mixed operation sequence for InsertSome and RemoveSome
template <typename Data>
void MixedOperations(uint& testnum, uint& testerr, lasd::DictionaryContainer<Data>& con, const lasd::Vector<Data>& mixed) {
  bool tst1, tst2, tst3;
  
  // Test initial state
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Initial state before mixed operations: ";
  bool initialExists = con.Exists(mixed[0]);
  std::cout << (initialExists ? "first element exists" : "first element does not exist") << std::endl;
  
  // InsertSome with mixed content (should return true if at least one element wasn't in container)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") InsertSome with mixed content: ";
  tst1 = con.InsertSome(mixed);
  std::cout << (tst1 ? "correctly returned true" : "incorrectly returned false") << ": ";
  std::cout << (tst1 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst1);
  
  // Verify at least one element exists now
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Verify content after InsertSome: ";
  bool anyExists = false;
  for (ulong i = 0; i < mixed.Size(); i++) {
    anyExists |= con.Exists(mixed[i]);
  }
  std::cout << (anyExists ? "at least one element exists" : "no elements exist") << ": ";
  std::cout << (anyExists ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!anyExists);
  
  // RemoveSome with the same content (should return true if at least one element was in container)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") RemoveSome with mixed content: ";
  tst2 = con.RemoveSome(mixed);
  std::cout << (tst2 ? "correctly returned true" : "incorrectly returned false") << ": ";
  std::cout << (tst2 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst2);
  
  // Try RemoveSome again (should return false if all were already removed)
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") RemoveSome after already removing all elements: ";
  tst3 = !con.RemoveSome(mixed);
  std::cout << (!tst3 ? "correctly returned false" : "incorrectly returned true") << ": ";
  std::cout << (tst3 ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!tst3);
}

/* ************************************************************************** */

// Extended OrderedDictionaryContainer member functions tests

// Test order consistency between Min, Max, Successor, and Predecessor
template <typename Data>
void OrderConsistency(uint& testnum, uint& testerr, lasd::OrderedDictionaryContainer<Data>& con) {
  bool tst1 = true, tst2 = true;
  
  if (con.Empty()) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Order consistency test skipped - container is empty" << std::endl;
    return;
  }
  
  try {
    // Test if Min() <= Max()
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Min <= Max order consistency: ";
    Data min = con.Min();
    Data max = con.Max();
    tst1 = (min <= max);
    std::cout << "Min = " << min << ", Max = " << max << ": ";
    std::cout << (tst1 ? "Correct" : "Error") << "!" << std::endl;
    testerr += (!tst1);
    
    // If container has at least two elements, test Successor/Predecessor relationship
    if (min != max) {
      testnum++;
      std::cout << " " << testnum << " (" << testerr << ") Successor/Predecessor relationship: ";
      Data succ = con.Successor(min);
      Data pred = con.Predecessor(max);
      
      bool succTest = (min < succ) && (succ <= max);
      bool predTest = (min <= pred) && (pred < max);
      
      tst2 = succTest && predTest;
      std::cout << "Successor(Min) = " << succ << ", Predecessor(Max) = " << pred << ": ";
      std::cout << (tst2 ? "Correct" : "Error") << "!" << std::endl;
      testerr += (!tst2);
    }
  }
  catch (std::exception& e) {
    std::cout << "Exception thrown: " << e.what() << std::endl;
    testerr += 1;
  }
}

// Test MinNRemove operation sequence
template <typename Data>
void MinMaxRemovalSequence(uint& testnum, uint& testerr, lasd::OrderedDictionaryContainer<Data>& con, uint numOps) {
  if (con.Empty()) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") MinMax removal sequence test skipped - container is empty" << std::endl;
    return;
  }
  
  // Save initial size
  ulong initialSize = con.Size();
  ulong expectedSize = initialSize;
  ulong actualOps = (numOps < initialSize) ? numOps : initialSize;
  
  // Test alternating MinNRemove and MaxNRemove
  bool testPassed = true;
  Data lastMin, lastMax;
  
  for (uint i = 0; i < actualOps; i++) {
    try {
      if (i % 2 == 0 && expectedSize > 0) {
        // MinNRemove
        testnum++;
        Data currentMin = con.Min();
        Data removedMin = con.MinNRemove();
        expectedSize--;
        
        std::cout << " " << testnum << " (" << testerr << ") MinNRemove consistency [" << i+1 << "/" << actualOps << "]: ";
        bool minTest = (currentMin == removedMin) && (con.Size() == expectedSize);
        
        // Check that new Min > previous Min
        if (i > 0 && !con.Empty()) {
          minTest &= (con.Min() > lastMin);
        }
        
        std::cout << "Removed " << removedMin << ", Size = " << con.Size() << ": ";
        std::cout << (minTest ? "Correct" : "Error") << "!" << std::endl;
        testPassed &= minTest;
        testerr += (!minTest);
        
        lastMin = removedMin;
      } else if (expectedSize > 0) {
        // MaxNRemove
        testnum++;
        Data currentMax = con.Max();
        Data removedMax = con.MaxNRemove();
        expectedSize--;
        
        std::cout << " " << testnum << " (" << testerr << ") MaxNRemove consistency [" << i+1 << "/" << actualOps << "]: ";
        bool maxTest = (currentMax == removedMax) && (con.Size() == expectedSize);
        
        // Check that new Max < previous Max
        if (i > 0 && !con.Empty()) {
          maxTest &= (con.Max() < lastMax);
        }
        
        std::cout << "Removed " << removedMax << ", Size = " << con.Size() << ": ";
        std::cout << (maxTest ? "Correct" : "Error") << "!" << std::endl;
        testPassed &= maxTest;
        testerr += (!maxTest);
        
        lastMax = removedMax;
      }
    }
    catch (std::exception& e) {
      std::cout << "Exception thrown: " << e.what() << std::endl;
      testPassed = false;
      testerr += 1;
    }
  }
  
  // Final check
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Final size after MinMax removal sequence: ";
  bool sizeTest = (con.Size() == expectedSize);
  std::cout << "Expected = " << expectedSize << ", Actual = " << con.Size() << ": ";
  std::cout << (sizeTest ? "Correct" : "Error") << "!" << std::endl;
  testerr += (!sizeTest);
}

// Test Successor and Predecessor operations on edge values
template <typename Data>
void SuccessorPredecessorEdgeCases(uint& testnum, uint& testerr, lasd::OrderedDictionaryContainer<Data>& con, const Data& beyondMin, const Data& beyondMax) {
  if (con.Empty()) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Successor/Predecessor edge cases test skipped - container is empty" << std::endl;
    return;
  }
  
  // Test cases for edge values
  try {
    // Test Successor on value less than Min
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Successor of value below minimum: ";
    Data min = con.Min();
    Data succ = con.Successor(beyondMin);
    bool succTest = (succ == min);
    std::cout << "Successor(" << beyondMin << ") = " << succ << ", Min = " << min << ": ";
    std::cout << (succTest ? "Correct" : "Error") << "!" << std::endl;
    testerr += (!succTest);
  }
  catch (std::exception& e) {
    std::cout << "Exception thrown: " << e.what() << " - expected Min" << std::endl;
    testerr += 1;
  }
  
  try {
    // Test Predecessor on value greater than Max
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Predecessor of value above maximum: ";
    Data max = con.Max();
    Data pred = con.Predecessor(beyondMax);
    bool predTest = (pred == max);
    std::cout << "Predecessor(" << beyondMax << ") = " << pred << ", Max = " << max << ": ";
    std::cout << (predTest ? "Correct" : "Error") << "!" << std::endl;
    testerr += (!predTest);
  }
  catch (std::exception& e) {
    std::cout << "Exception thrown: " << e.what() << " - expected Max" << std::endl;
    testerr += 1;
  }
  
  // Test expected exceptions
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Predecessor of minimum value - exception expected: ";
  bool exceptionThrown = false;
  try {
    Data min = con.Min();
    Data pred = con.Predecessor(min);
    std::cout << "No exception thrown, returned " << pred << ": Error!" << std::endl;
    testerr += 1;
  }
  catch (std::length_error& e) {
    std::cout << "Exception thrown as expected: Correct!" << std::endl;
  }
  catch (std::exception& e) {
    std::cout << "Wrong exception type thrown: " << e.what() << ": Error!" << std::endl;
    testerr += 1;
  }
  
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Successor of maximum value - exception expected: ";
  exceptionThrown = false;
  try {
    Data max = con.Max();
    Data succ = con.Successor(max);
    std::cout << "No exception thrown, returned " << succ << ": Error!" << std::endl;
    testerr += 1;
  }
  catch (std::length_error& e) {
    std::cout << "Exception thrown as expected: Correct!" << std::endl;
  }
  catch (std::exception& e) {
    std::cout << "Wrong exception type thrown: " << e.what() << ": Error!" << std::endl;
    testerr += 1;
  }
}

/* ************************************************************************** */

#endif