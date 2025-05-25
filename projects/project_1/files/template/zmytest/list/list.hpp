#ifndef MYLISTTEST_HPP
#define MYLISTTEST_HPP

#include "../../list/list.hpp"

/* ************************************************************************** */

// Extended List test functions

// Test constructor from TraversableContainer
template <typename Data>
void ConstructFromTraversable(uint& testnum, uint& testerr, const lasd::TraversableContainer<Data>& container) {
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") Constructing List from TraversableContainer: ";
    
    lasd::List<Data> list(container);
    
    // Verify size
    if (list.Size() != container.Size()) {
      tst = false;
    }
    
    // Verify content by traversing both containers
    if (tst) {
      ulong listSize = list.Size();
      ulong counter = 0;
      bool contentMatch = true;
      
      // Function to compare elements at each position
      std::function<void(const Data&)> checkElement = [&list, &counter, &contentMatch](const Data& val) {
        if (counter < list.Size() && list[counter] != val) {
          contentMatch = false;
        }
        counter++;
      };
      
      container.Traverse(checkElement);
      
      if (!contentMatch || counter != listSize) {
        tst = false;
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

// Test constructor from MappableContainer (move semantics)
template <typename Data>
void ConstructFromMappable(uint& testnum, uint& testerr, lasd::MappableContainer<Data>& container) {
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") Constructing List from MappableContainer (move): ";
    
    // Create a copy of the container for verification
    lasd::List<Data> expectedValues;
    container.Traverse([&expectedValues](const Data& val) {
      expectedValues.InsertAtBack(val);
    });
    
    // Create list using move semantics
    lasd::List<Data> list(std::move(container));
    
    // Verify size
    if (list.Size() != expectedValues.Size()) {
      tst = false;
    }
    
    // Verify content
    if (tst) {
      for (ulong i = 0; i < list.Size(); i++) {
        if (list[i] != expectedValues[i]) {
          tst = false;
          break;
        }
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

// Test copy constructor and assignment
template <typename Data>
void CopyListTest(uint& testnum, uint& testerr, const lasd::List<Data>& original) {
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") Copy constructor and assignment test: ";
    
    // Test copy constructor
    lasd::List<Data> copiedList(original);
    
    // Verify copied list is equal to original
    if (!(copiedList == original)) {
      tst = false;
    }
    
    // Modify copied list
    if (!copiedList.Empty()) {
      Data originalFront = copiedList.Front();
      Data newFront = originalFront;
      newFront = newFront + Data{1}; // Increment the value
      copiedList.Front() = newFront;
      
      // Verify original is unchanged
      if (original.Empty() || original.Front() != originalFront) {
        tst = false;
      }
      
      // Verify copy is different
      if (copiedList.Empty() || copiedList.Front() != newFront) {
        tst = false;
      }
      
      // Verify lists are now different
      if (copiedList == original) {
        tst = false;
      }
    }
    
    // Test copy assignment
    lasd::List<Data> assignedList;
    assignedList = original;
    
    // Verify assigned list is equal to original
    if (!(assignedList == original)) {
      tst = false;
    }
    
    // Modify assigned list
    if (!assignedList.Empty()) {
      Data originalBack = assignedList.Back();
      Data newBack = originalBack;
      newBack = newBack + Data{1}; // Increment the value
      assignedList.Back() = newBack;
      
      // Verify original is unchanged
      if (original.Empty() || original.Back() != originalBack) {
        tst = false;
      }
      
      // Verify assigned list is changed
      if (assignedList.Empty() || assignedList.Back() != newBack) {
        tst = false;
      }
      
      // Verify lists are now different
      if (assignedList == original) {
        tst = false;
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

// Test move constructor and assignment
template <typename Data>
void MoveListTest(uint& testnum, uint& testerr, lasd::List<Data>& original) {
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") Move constructor and assignment test: ";
    
    // Create a copy for verification
    lasd::List<Data> originalCopy(original);
    
    // Test move constructor
    lasd::List<Data> movedList(std::move(original));
    
    // Verify moved list contains original values
    if (!(movedList == originalCopy)) {
      tst = false;
    }
    
    // Verify original list is now empty
    if (!original.Empty()) {
      tst = false;
    }
    
    // Create a new list for move assignment test
    lasd::List<Data> newOriginal(originalCopy);
    
    // Test move assignment
    lasd::List<Data> assignedList;
    assignedList = std::move(newOriginal);
    
    // Verify assigned list contains original values
    if (!(assignedList == originalCopy)) {
      tst = false;
    }
    
    // Verify new original list is now empty
    if (!newOriginal.Empty()) {
      tst = false;
    }
    
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  
  testerr += (1 - (uint)tst);
}

// Test sequence of operations
template <typename Data>
void OperationSequence(uint& testnum, uint& testerr, lasd::List<Data>& lst, const Data& val1, const Data& val2, const Data& val3) {
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") Sequence of operations test: ";
    
    // Initial size
    ulong initialSize = lst.Size();
    
    // Sequence: InsertAtFront, InsertAtBack, RemoveFromFront, RemoveFromBack
    lst.InsertAtFront(val1);
    lst.InsertAtBack(val2);
    
    // Verify front and back
    if (lst.Front() != val1 || lst.Back() != val2) {
      tst = false;
    }
    
    // Verify size increased by 2
    if (lst.Size() != initialSize + 2) {
      tst = false;
    }
    
    lst.RemoveFromFront();
    
    // Verify front has changed
    if (lst.Empty() || (lst.Size() > 0 && lst.Front() == val1)) {
      tst = false;
    }
    
    lst.RemoveFromBack();
    
    // Verify size is back to initial
    if (lst.Size() != initialSize) {
      tst = false;
    }
    
    // Try FrontNRemove and BackNRemove
    if (!lst.Empty()) {
      Data frontVal = lst.Front();
      Data removedFront = lst.FrontNRemove();
      
      // Verify removed value matches original front
      if (removedFront != frontVal) {
        tst = false;
      }
      
      // Verify size decreased
      if (lst.Size() != initialSize - 1) {
        tst = false;
      }
      
      // If still not empty, test BackNRemove
      if (!lst.Empty()) {
        Data backVal = lst.Back();
        Data removedBack = lst.BackNRemove();
        
        // Verify removed value matches original back
        if (removedBack != backVal) {
          tst = false;
        }
        
        // Verify size decreased
        if (lst.Size() != initialSize - 2) {
          tst = false;
        }
      }
    }
    
    // Restore list to initial size + 1
    for (ulong i = lst.Size(); i < initialSize + 1; i++) {
      lst.InsertAtBack(val3);
    }
    
    // Verify size is initialSize + 1
    if (lst.Size() != initialSize + 1) {
      tst = false;
    }
    
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  
  testerr += (1 - (uint)tst);
}

// Test with Clear and subsequent operations
template <typename Data>
void ClearAndRebuild(uint& testnum, uint& testerr, lasd::List<Data>& lst, const Data& val) {
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") Clear and rebuild test: ";
    
    // Clear the list
    lst.Clear();
    
    // Verify list is empty
    if (!lst.Empty() || lst.Size() != 0) {
      tst = false;
    }
    
    // Try operations on empty list
    bool correctExceptionFront = false;
    try {
      Data front = lst.Front();
    }
    catch (std::length_error&) {
      correctExceptionFront = true;
    }
    catch (...) {
      correctExceptionFront = false;
    }
    
    bool correctExceptionBack = false;
    try {
      Data back = lst.Back();
    }
    catch (std::length_error&) {
      correctExceptionBack = true;
    }
    catch (...) {
      correctExceptionBack = false;
    }
    
    if (!correctExceptionFront || !correctExceptionBack) {
      tst = false;
    }
    
    // Rebuild list
    lst.InsertAtFront(val);
    lst.InsertAtBack(val);
    
    // Verify list has two elements
    if (lst.Size() != 2) {
      tst = false;
    }
    
    // Verify front and back
    if (lst.Front() != val || lst.Back() != val) {
      tst = false;
    }
    
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception& exc) {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }
  
  testerr += (1 - (uint)tst);
}

// Test different traversal orders (PreOrder vs PostOrder)
template <typename Data>
void ListTraversalOrders(uint& testnum, uint& testerr, lasd::List<Data>& lst) {
  if (lst.Empty() || lst.Size() == 1) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Traversal orders test skipped - list has fewer than 2 elements" << std::endl;
    return;
  }
  
  bool tst = true;
  testnum++;
  
  try {
    std::cout << " " << testnum << " (" << testerr << ") List traversal orders test: ";
    
    // Collect elements in pre-order
    lasd::List<Data> preOrderElements;
    lst.PreOrderTraverse([&preOrderElements](const Data& val) {
      preOrderElements.InsertAtBack(val);
    });
    
    // Collect elements in post-order
    lasd::List<Data> postOrderElements;
    lst.PostOrderTraverse([&postOrderElements](const Data& val) {
      postOrderElements.InsertAtBack(val);
    });
    
    // Verify sizes match
    if (preOrderElements.Size() != lst.Size() || postOrderElements.Size() != lst.Size()) {
      tst = false;
    }
    
    // For lists, pre-order should be front-to-back and post-order should be back-to-front
    if (tst) {
      // Check pre-order
      for (ulong i = 0; i < lst.Size(); i++) {
        if (preOrderElements[i] != lst[i]) {
          tst = false;
          break;
        }
      }
      
      // Check post-order by comparing with reversed traversal
      for (ulong i = 0; i < lst.Size(); i++) {
        if (postOrderElements[i] != lst[lst.Size() - 1 - i]) {
          tst = false;
          break;
        }
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

/* ************************************************************************** */

#endif