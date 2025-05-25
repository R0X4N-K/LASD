#include "test.hpp"

/* ************************************************************************** */

#include <iostream>
#include <string>
#include <utility>

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"

#include "../vector/vector.hpp"
#include "../list/list.hpp"

#include "../set/set.hpp"
#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"

/* ************************************************************************** */

#include "./container/traversable.hpp"
#include "./container/testable.hpp"
#include "./container/mappable.hpp"
#include "./container/linear.hpp"

#include "./list/list.hpp"
#include "./vector/vector.hpp"

#include "./set/set.hpp"
#include "./set/lst/setlst.hpp"
#include "./set/vec/setvec.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

// Test functions for Exercise 1A - Vectors and Lists
void testExercise1A(uint& testnum, uint& testerr) {
  cout << endl << "Test Exercise 1A - Vectors and Lists (Extended)" << endl;
  
  // Test Integer List
  cout << endl << "Test Integer List" << endl;
  
  lasd::List<int> intList;
  
  // Populate the list
  for (int i = 0; i < 5; i++) {
    intList.InsertAtBack(i * 10);
  }
  
  // Test list operations
  cout << "Testing list operations:" << endl;
  
  // Test traversable operations
  TraverseEmpty(testnum, testerr, intList);
  FoldTraverseConsistency(testnum, testerr, intList);
  FoldComplexAccumulator(testnum, testerr, intList);
  ConditionalTraverse(testnum, testerr, intList, 20);
  
  // Test order traversals
  PreOrderTraverseEquivalence(testnum, testerr, intList);
  PostOrderTraverseEquivalence(testnum, testerr, intList);
  PreOrderFoldConsistency(testnum, testerr, intList);
  PostOrderFoldConsistency(testnum, testerr, intList);
  ListTraversalOrders(testnum, testerr, intList);
  
  // Test testable container operations
  ExistsEdgeCase<int>(testnum, testerr, intList, true, 0, string("Minimum value"));
  ExistsEdgeCase<int>(testnum, testerr, intList, true, 40, string("Maximum value"));
  ExistsEdgeCase<int>(testnum, testerr, intList, false, 15, string("Value between elements"));
  ExistsEdgeCase<int>(testnum, testerr, intList, false, 50, string("Value above maximum"));
  
  // Test list specific operations
  ConstructFromTraversable(testnum, testerr, intList);
  
  lasd::List<int> copyList(intList);
  CopyListTest(testnum, testerr, intList);
  
  lasd::List<int> moveList(intList);
  MoveListTest(testnum, testerr, moveList);
  
  OperationSequence(testnum, testerr, intList, 100, 200, 300);
  ClearAndRebuild(testnum, testerr, intList, 42);
  
  // Test Integer Vector
  cout << endl << "Test Integer Vector" << endl;
  
  lasd::Vector<int> intVec(5);
  
  // Populate the vector
  for (int i = 0; i < 5; i++) {
    intVec[i] = i * 10;
  }
  
  // Test vector operations
  cout << "Testing vector operations:" << endl;
  
  // Test constructors
  ConstructWithSize(testnum, testerr, 3, 0);
  VectorFromTraversable(testnum, testerr, intList);
  
  // Test copy and move
  VectorCopyTest(testnum, testerr, intVec);
  
  lasd::Vector<int> moveVec(intVec);
  VectorMoveTest(testnum, testerr, moveVec);
  
  // Test resize and access
  VectorResizeTest(testnum, testerr, intVec, 8);
  VectorAccessTest(testnum, testerr, intVec, 55);
  VectorClearTest(testnum, testerr, intVec);
  
  // Test mappable operations
  MapEmpty(testnum, testerr, intVec);
  
  // Refill vector
  intVec.Resize(5);
  for (int i = 0; i < 5; i++) {
    intVec[i] = i * 10;
  }
  
  MapComposition(testnum, testerr, intVec, 5, 2);
  MapConditional(testnum, testerr, intVec, 20, 99);
  
  // Test linear container operations
  AccessBoundaryElements(testnum, testerr, intVec);
  AccessOutOfRange(testnum, testerr, intVec);
  
  // Test sortable vector
  lasd::SortableVector<int> sortVec(5);
  
  // Populate with unsorted values
  sortVec[0] = 30;
  sortVec[1] = 10;
  sortVec[2] = 50;
  sortVec[3] = 20;
  sortVec[4] = 40;
  
  SortableVectorSortTest(testnum, testerr, sortVec);
  SortAlreadySortedVectorTest(testnum, testerr, sortVec);
  
  // Test String List
  cout << endl << "Test String List" << endl;
  
  lasd::List<string> strList;
  
  // Populate the list
  strList.InsertAtBack(string("alpha"));
  strList.InsertAtBack(string("beta"));
  strList.InsertAtBack(string("gamma"));
  strList.InsertAtBack(string("delta"));
  strList.InsertAtBack(string("epsilon"));
  
  // Test list operations for strings
  ExistsEdgeCase<string>(testnum, testerr, strList, true, string("alpha"), string("First element"));
  ExistsEdgeCase<string>(testnum, testerr, strList, true, string("epsilon"), string("Last element"));
  ExistsEdgeCase<string>(testnum, testerr, strList, false, string("omega"), string("Non-existent element"));
  
  ListTraversalOrders(testnum, testerr, strList);
  
  string phi = "phi";
  string chi = "chi";
  string psi = "psi";
  OperationSequence(testnum, testerr, strList, phi, chi, psi);
  
  // Test mappable operations for strings
  string suffix = "suffix";
  MapPreOrderEquivalence(testnum, testerr, strList, suffix);
  MapPostOrderEquivalence(testnum, testerr, strList, suffix);
}

// Test functions for Exercise 1B - Sets
void testExercise1B(uint& testnum, uint& testerr) {
  cout << endl << "Test Exercise 1B - Sets (Extended)" << endl;
  
  // Test Integer SetLst
  cout << endl << "Test Integer SetLst" << endl;
  
  lasd::SetLst<int> intSetLst;
  
  // Test set operations
  cout << "Testing SetLst operations:" << endl;
  
  // Test insert and duplicates
  SetLstInsertDuplicates(testnum, testerr, intSetLst, 42);
  
  // Test order maintenance
  SetLstOrderMaintenance(testnum, testerr, intSetLst, 10, 20, 30);
  
  // Test remove operations
  SetLstRemoveOperations(testnum, testerr, intSetLst, 15, 25, 35);
  
  // Test predecessor/successor operations
  SetLstPredSuccOperations(testnum, testerr, intSetLst, 5, 15, 25);
  
  // Test min/max operations
  SetLstMinMaxOperations(testnum, testerr, intSetLst, 100, 200, 300);
  
  // Test Integer SetVec
  cout << endl << "Test Integer SetVec" << endl;
  
  lasd::SetVec<int> intSetVec;
  
  // Test set operations
  cout << "Testing SetVec operations:" << endl;
  
  // Test insert and duplicates
  SetVecInsertDuplicates(testnum, testerr, intSetVec, 42);
  
  // Test binary search
  SetVecBinarySearch(testnum, testerr, intSetVec, 10, 20, 30);
  
  // Test predecessor/successor
  SetVecPredSucc(testnum, testerr, intSetVec, 5, 15, 25, 35);
  
  // Test removal operations
  SetVecRemoval(testnum, testerr, intSetVec, 50, 60, 70);
  
  // Create a test container for SetVecFromTraversable
  lasd::List<int> testContainer;
  testContainer.InsertAtBack(100);
  testContainer.InsertAtBack(80);
  testContainer.InsertAtBack(60);
  testContainer.InsertAtBack(80); // Duplicate
  testContainer.InsertAtBack(40);
  testContainer.InsertAtBack(20);
  
  SetVecFromTraversable(testnum, testerr, testContainer);
  
  // Common Set tests
  cout << endl << "Common Set Tests" << endl;
  
  // Compare implementations
  CompareSetImplementations(testnum, testerr, intSetLst, intSetVec);
  
  // Test boundary cases
  SetBoundaryTests(testnum, testerr, intSetLst, 1, 1000);
  SetBoundaryTests(testnum, testerr, intSetVec, 1, 1000);
  
  // Test order stress
  SetOrderStressTest(testnum, testerr, intSetLst);
  SetOrderStressTest(testnum, testerr, intSetVec);
  
  // Test String Sets
  cout << endl << "Test String Sets" << endl;
  
  lasd::SetLst<string> strSetLst;
  lasd::SetVec<string> strSetVec;
  
  // Test with strings
  string test = "test";
  SetLstInsertDuplicates(testnum, testerr, strSetLst, test);
  SetVecInsertDuplicates(testnum, testerr, strSetVec, test);
  
  string alpha = "alpha";
  string beta = "beta";
  string gamma = "gamma";
  SetLstOrderMaintenance(testnum, testerr, strSetLst, alpha, beta, gamma);
  SetVecBinarySearch(testnum, testerr, strSetVec, alpha, beta, gamma);
  
  CompareSetImplementations(testnum, testerr, strSetLst, strSetVec);
}

/* ************************************************************************** */

void mylasdtest() {
  cout << endl << "~*~#~*~ My Extended LASD Test Suite ~*~#~*~ " << endl;

  uint testnum = 0, testerr = 0;

  testExercise1A(testnum, testerr);
  testExercise1B(testnum, testerr);

  cout << endl << "Extended Tests (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}

/* ************************************************************************** */