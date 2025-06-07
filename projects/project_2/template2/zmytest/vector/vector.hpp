#ifndef MYVECTORTEST_HPP
#define MYVECTORTEST_HPP

#include "../../vector/vector.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

// Extended Vector test functions

// Test constructor with initial size
template <typename Data>
void ConstructWithSize(uint &testnum, uint &testerr, const ulong size, const Data &defaultVal)
{
  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Vector constructor with size " << size << ": ";

    lasd::Vector<Data> vec(size);

    // Verify size
    if (vec.Size() != size)
    {
      tst = false;
    }

    // Verify default initialization
    for (ulong i = 0; i < size; i++)
    {
      if (vec[i] != defaultVal)
      {
        tst = false;
        break;
      }
    }

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test constructor from TraversableContainer
template <typename Data>
void VectorFromTraversable(uint &testnum, uint &testerr, const lasd::TraversableContainer<Data> &container)
{
  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Vector constructor from TraversableContainer: ";

    lasd::Vector<Data> vec(container);

    // Verify size
    if (vec.Size() != container.Size())
    {
      tst = false;
    }

    // Create list to traverse container elements for comparison
    lasd::List<Data> elements;
    container.Traverse([&elements](const Data &val)
                       { elements.InsertAtBack(val); });

    // Verify content
    if (tst && !elements.Empty())
    {
      for (ulong i = 0; i < vec.Size(); i++)
      {
        if (vec[i] != elements[i])
        {
          tst = false;
          break;
        }
      }
    }

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test copy constructor and assignment
template <typename Data>
void VectorCopyTest(uint &testnum, uint &testerr, const lasd::Vector<Data> &original)
{
  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Vector copy constructor and assignment: ";

    // Test copy constructor
    lasd::Vector<Data> copiedVec(original);

    // Verify copied vector is equal to original
    if (!(copiedVec == original))
    {
      tst = false;
    }

    // Modify copied vector
    if (!copiedVec.Empty())
    {
      Data originalFront = copiedVec.Front();
      Data newFront = originalFront;
      newFront = newFront + Data{1}; // Increment the value
      copiedVec.Front() = newFront;

      // Verify original is unchanged
      if (original.Empty() || original.Front() != originalFront)
      {
        tst = false;
      }

      // Verify copy is changed
      if (copiedVec.Empty() || copiedVec.Front() != newFront)
      {
        tst = false;
      }

      // Verify vectors are now different
      if (copiedVec == original)
      {
        tst = false;
      }
    }

    // Test copy assignment
    lasd::Vector<Data> assignedVec(1); // Create with different size
    assignedVec = original;

    // Verify assigned vector is equal to original
    if (!(assignedVec == original))
    {
      tst = false;
    }

    // Modify assigned vector
    if (!assignedVec.Empty())
    {
      Data originalBack = assignedVec.Back();
      Data newBack = originalBack;
      newBack = newBack + Data{1}; // Increment the value
      assignedVec.Back() = newBack;

      // Verify original is unchanged
      if (original.Empty() || original.Back() != originalBack)
      {
        tst = false;
      }

      // Verify assigned vector is changed
      if (assignedVec.Empty() || assignedVec.Back() != newBack)
      {
        tst = false;
      }

      // Verify vectors are now different
      if (assignedVec == original)
      {
        tst = false;
      }
    }

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test move constructor and assignment
template <typename Data>
void VectorMoveTest(uint &testnum, uint &testerr, lasd::Vector<Data> &original)
{
  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Vector move constructor and assignment: ";

    // Create a copy for verification
    lasd::Vector<Data> originalCopy(original);

    // Test move constructor
    lasd::Vector<Data> movedVec(std::move(original));

    // Verify moved vector contains original values
    if (!(movedVec == originalCopy))
    {
      tst = false;
    }

    // Verify original vector is now in a valid but unspecified state
    // The standard doesn't specify what happens to the moved-from object
    // We can't test specific behavior here, but the object should be usable

    // Create a new vector for move assignment test
    lasd::Vector<Data> newOriginal(originalCopy);

    // Test move assignment
    lasd::Vector<Data> assignedVec;
    assignedVec = std::move(newOriginal);

    // Verify assigned vector contains original values
    if (!(assignedVec == originalCopy))
    {
      tst = false;
    }

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test Resize operations
template <typename Data>
void VectorResizeTest(uint &testnum, uint &testerr, lasd::Vector<Data> &vec, const ulong newSize)
{
  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Vector Resize from " << vec.Size() << " to " << newSize << ": ";

    // Create a copy of the vector for value preservation check
    lasd::List<Data> originalValues;
    ulong minSize = (vec.Size() < newSize) ? vec.Size() : newSize;

    for (ulong i = 0; i < vec.Size(); i++)
    {
      originalValues.InsertAtBack(vec[i]);
    }

    // Resize the vector
    vec.Resize(newSize);

    // Verify new size
    if (vec.Size() != newSize)
    {
      tst = false;
    }

    // Verify values are preserved up to min size
    if (tst && minSize > 0)
    {
      for (ulong i = 0; i < minSize; i++)
      {
        if (vec[i] != originalValues[i])
        {
          tst = false;
          break;
        }
      }
    }

    // Test special case: Resize to 0
    if (tst)
    {
      vec.Resize(0);
      if (!vec.Empty() || vec.Size() != 0)
      {
        tst = false;
      }
    }

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test access operations (operator[], Front, Back)
template <typename Data>
void VectorAccessTest(uint &testnum, uint &testerr, lasd::Vector<Data> &vec, const Data &newVal)
{
  if (vec.Empty())
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Vector access test skipped - vector is empty" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Vector element access and modification: ";

    // Store original values
    Data originalFront = vec.Front();
    Data originalBack = vec.Back();
    Data originalMiddle = vec[vec.Size() / 2];

    // Modify values
    vec.Front() = newVal;
    vec.Back() = newVal;
    vec[vec.Size() / 2] = newVal;

    // Verify changes
    if (vec.Front() != newVal || vec.Back() != newVal || vec[vec.Size() / 2] != newVal)
    {
      tst = false;
    }

    // Test out of range access
    bool correctException = false;
    try
    {
      Data val = vec[vec.Size()];
      (void)val; // Suppress unused variable warning
    }
    catch (std::out_of_range &)
    {
      correctException = true;
    }
    catch (...)
    {
      correctException = false;
    }

    if (!correctException)
    {
      tst = false;
    }

    // Restore original values
    vec.Front() = originalFront;
    vec.Back() = originalBack;
    vec[vec.Size() / 2] = originalMiddle;

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test Clear operation
template <typename Data>
void VectorClearTest(uint &testnum, uint &testerr, lasd::Vector<Data> &vec)
{
  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Vector Clear operation: ";

    // Clear the vector
    vec.Clear();

    // Verify vector is empty
    if (!vec.Empty() || vec.Size() != 0)
    {
      tst = false;
    }

    // Test exceptions after Clear
    bool correctExceptionFront = false;
    bool correctExceptionBack = false;
    bool correctExceptionAccess = false;

    try
    {
      Data front = vec.Front();
      (void)front; // Suppress unused variable warning
    }
    catch (std::length_error &)
    {
      correctExceptionFront = true;
    }
    catch (...)
    {
      correctExceptionFront = false;
    }

    try
    {
      Data back = vec.Back();
      (void)back; // Suppress unused variable warning
    }
    catch (std::length_error &)
    {
      correctExceptionBack = true;
    }
    catch (...)
    {
      correctExceptionBack = false;
    }

    try
    {
      Data val = vec[0];
      (void)val; // Suppress unused variable warning
    }
    catch (std::out_of_range &)
    {
      correctExceptionAccess = true;
    }
    catch (...)
    {
      correctExceptionAccess = false;
    }

    if (!correctExceptionFront || !correctExceptionBack || !correctExceptionAccess)
    {
      tst = false;
    }

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

/* ************************************************************************** */

// Extended SortableVector test functions

// Test Sort operation with random values
template <typename Data>
void SortableVectorSortTest(uint &testnum, uint &testerr, lasd::SortableVector<Data> &vec)
{
  if (vec.Empty() || vec.Size() == 1)
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") SortableVector Sort test skipped - vector has fewer than 2 elements" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") SortableVector Sort operation: ";

    // Store original values for later
    lasd::List<Data> originalValues;
    for (ulong i = 0; i < vec.Size(); i++)
    {
      originalValues.InsertAtBack(vec[i]);
    }

    // Sort the vector
    vec.Sort();

    // Verify vector is sorted
    for (ulong i = 1; i < vec.Size(); i++)
    {
      if (vec[i - 1] > vec[i])
      {
        tst = false;
        break;
      }
    }

    // Verify all original elements are still present (just reordered)
    if (tst)
    {
      lasd::List<Data> sortedValues;
      for (ulong i = 0; i < vec.Size(); i++)
      {
        sortedValues.InsertAtBack(vec[i]);
      }

      // Check if each original element exists in the sorted list
      bool allPresent = true;
      originalValues.Traverse([&sortedValues, &allPresent](const Data &val)
                              {
        // Simple linear search for this element
        bool found = false;
        for (ulong i = 0; i < sortedValues.Size(); i++) {
          if (sortedValues[i] == val) {
            found = true;
            break;
          }
        }
        if (!found) {
          allPresent = false;
        } });

      if (!allPresent)
      {
        tst = false;
      }
    }

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test SortableVector with already sorted data
template <typename Data>
void SortAlreadySortedVectorTest(uint &testnum, uint &testerr, lasd::SortableVector<Data> &vec)
{
  if (vec.Empty() || vec.Size() == 1)
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") SortableVector already sorted test skipped - vector has fewer than 2 elements" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") SortableVector on already sorted data: ";

    // First sort to ensure it's sorted
    vec.Sort();

    // Store sorted values
    lasd::List<Data> sortedValues;
    for (ulong i = 0; i < vec.Size(); i++)
    {
      sortedValues.InsertAtBack(vec[i]);
    }

    // Sort again
    vec.Sort();

    // Verify vector is still sorted
    for (ulong i = 1; i < vec.Size(); i++)
    {
      if (vec[i - 1] > vec[i])
      {
        tst = false;
        break;
      }
    }

    // Verify order hasn't changed
    for (ulong i = 0; i < vec.Size(); i++)
    {
      if (vec[i] != sortedValues[i])
      {
        tst = false;
        break;
      }
    }

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

/* ************************************************************************** */

#endif