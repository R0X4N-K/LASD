#ifndef MYSETLSTTEST_HPP
#define MYSETLSTTEST_HPP

#include "../../../set/lst/setlst.hpp"
#include "../../../list/list.hpp"

/* ************************************************************************** */

// Extended SetLst test functions

// Test insertion with duplicates (should reject duplicates)
template <typename Data>
void SetLstInsertDuplicates(uint& testnum, uint& testerr, lasd::SetLst<Data>& set, const Data& val) {
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") SetLst duplicate rejection test: ";
    
    // First insertion should succeed
    bool firstInsert = set.Insert(val);
    
    // Second insertion of same value should fail
    bool secondInsert = set.Insert(val);
    
    // Check exists
    bool exists = set.Exists(val);
    
    // Verify behavior
    tst = (firstInsert && !secondInsert && exists);
    
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  
  testerr += (1 - (uint)tst);
}

// Test order maintenance through series of operations
template <typename Data>
void SetLstOrderMaintenance(uint& testnum, uint& testerr, lasd::SetLst<Data>& set, 
                           const Data& val1, const Data& val2, const Data& val3) {
  if (!(val1 < val2 && val2 < val3)) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") SetLst order maintenance test skipped - values must be in ascending order" << std::endl;
    return;
  }
  
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") SetLst order maintenance through operations: ";
    
    // Clear the set and insert values in non-ordered sequence
    set.Clear();
    set.Insert(val2);
    set.Insert(val3);
    set.Insert(val1);
    
    // Check that min is val1 and max is val3
    bool minCorrect = (set.Min() == val1);
    bool maxCorrect = (set.Max() == val3);
    
    // Check predecessor and successor relationships
    bool pred1Correct = false;
    bool succ1Correct = (set.Successor(val1) == val2);
    
    bool pred2Correct = (set.Predecessor(val2) == val1);
    bool succ2Correct = (set.Successor(val2) == val3);
    
    bool pred3Correct = (set.Predecessor(val3) == val2);
    bool succ3Correct = false;
    
    // Check predecessor/successor exceptions
    try {
      set.Predecessor(val1);
      pred1Correct = false;
    } catch (std::length_error&) {
      pred1Correct = true;
    } catch (...) {
      pred1Correct = false;
    }
    
    try {
      set.Successor(val3);
      succ3Correct = false;
    } catch (std::length_error&) {
      succ3Correct = true;
    } catch (...) {
      succ3Correct = false;
    }
    
    // Verify all conditions
    tst = minCorrect && maxCorrect && 
          pred1Correct && succ1Correct && 
          pred2Correct && succ2Correct && 
          pred3Correct && succ3Correct;
    
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  
  testerr += (1 - (uint)tst);
}

// Test remove operations and their effect on the set structure
template <typename Data>
void SetLstRemoveOperations(uint& testnum, uint& testerr, lasd::SetLst<Data>& set,
                           const Data& val1, const Data& val2, const Data& val3) {
  if (!(val1 < val2 && val2 < val3)) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") SetLst remove operations test skipped - values must be in ascending order" << std::endl;
    return;
  }
  
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") SetLst remove operations: ";
    
    // Clear the set and insert values
    set.Clear();
    set.Insert(val1);
    set.Insert(val2);
    set.Insert(val3);
    
    // Initial size
    ulong initialSize = set.Size();
    
    // Remove middle element
    bool removeResult = set.Remove(val2);
    
    // Check size decreased
    bool sizeCorrect = (set.Size() == initialSize - 1);
    
    // Check val2 no longer exists
    bool existsCorrect = !set.Exists(val2);
    
    // Check new relationship: val3 should now be successor of val1
    bool relationshipCorrect = (set.Successor(val1) == val3);
    
    // Try to remove non-existent element
    bool removeNonExistent = !set.Remove(val2);
    
    // Verify all conditions
    tst = removeResult && sizeCorrect && existsCorrect && relationshipCorrect && removeNonExistent;
    
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  
  testerr += (1 - (uint)tst);
}

// Test predecessor and successor removal operations
template <typename Data>
void SetLstPredSuccOperations(uint& testnum, uint& testerr, lasd::SetLst<Data>& set,
                              const Data& val1, const Data& val2, const Data& val3) {
  if (!(val1 < val2 && val2 < val3)) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") SetLst predecessor/successor operations test skipped - values must be in ascending order" << std::endl;
    return;
  }
  
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") SetLst predecessor and successor operations: ";
    
    // Clear the set and insert values
    set.Clear();
    set.Insert(val1);
    set.Insert(val2);
    set.Insert(val3);
    
    // Test PredecessorNRemove
    Data pred = set.PredecessorNRemove(val3);
    bool predCorrect = (pred == val2);
    bool predRemoved = !set.Exists(val2);
    
    // Reinsert val2
    set.Insert(val2);
    
    // Test SuccessorNRemove
    Data succ = set.SuccessorNRemove(val1);
    bool succCorrect = (succ == val2);
    bool succRemoved = !set.Exists(val2);
    
    // Reinsert val2
    set.Insert(val2);
    
    // Test RemovePredecessor
    set.RemovePredecessor(val3);
    bool predRemoveCorrect = !set.Exists(val2);
    
    // Reinsert val2
    set.Insert(val2);
    
    // Test RemoveSuccessor
    set.RemoveSuccessor(val1);
    bool succRemoveCorrect = !set.Exists(val2);
    
    // Verify all conditions
    tst = predCorrect && predRemoved && succCorrect && succRemoved && predRemoveCorrect && succRemoveCorrect;
    
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  
  testerr += (1 - (uint)tst);
}

// Test Min/Max operations and their effect on the set
template <typename Data>
void SetLstMinMaxOperations(uint& testnum, uint& testerr, lasd::SetLst<Data>& set,
                           const Data& val1, const Data& val2, const Data& val3) {
  if (!(val1 < val2 && val2 < val3)) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") SetLst Min/Max operations test skipped - values must be in ascending order" << std::endl;
    return;
  }
  
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") SetLst Min and Max operations: ";
    
    // Clear the set and insert values
    set.Clear();
    set.Insert(val1);
    set.Insert(val2);
    set.Insert(val3);
    
    // Test MinNRemove
    Data min = set.MinNRemove();
    bool minCorrect = (min == val1);
    bool minRemoved = !set.Exists(val1);
    bool newMinCorrect = (set.Min() == val2);
    
    // Test MaxNRemove
    Data max = set.MaxNRemove();
    bool maxCorrect = (max == val3);
    bool maxRemoved = !set.Exists(val3);
    bool newMaxCorrect = (set.Max() == val2);
    
    // Now set should contain only val2
    bool sizeCorrect = (set.Size() == 1);
    
    // Remove the last element with RemoveMin
    set.RemoveMin();
    bool emptyCorrect = set.Empty();
    
    // Verify all conditions
    tst = minCorrect && minRemoved && newMinCorrect && 
          maxCorrect && maxRemoved && newMaxCorrect && 
          sizeCorrect && emptyCorrect;
    
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