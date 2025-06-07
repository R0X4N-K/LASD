#ifndef MYSETVECTEST_HPP
#define MYSETVECTEST_HPP

#include "../../../set/vec/setvec.hpp"
#include "../../../list/list.hpp"
#include <string>
#include <type_traits>

/* ************************************************************************** */

// Helper to create values just before/after others for different types
template <typename Data>
Data GetValueBefore(const Data &val)
{
  if constexpr (std::is_integral_v<Data> || std::is_floating_point_v<Data>)
  {
    // For numeric types, just subtract 1
    return val - Data{1};
  }
  else if constexpr (std::is_same_v<Data, std::string>)
  {
    // For strings, we can prepend a character to make it lexicographically smaller
    return "!" + val;
  }
  else
  {
    // For other types, we don't have a general solution
    // Just return the value itself (test may not work properly)
    return val;
  }
}

template <typename Data>
Data GetValueAfter(const Data &val)
{
  if constexpr (std::is_integral_v<Data> || std::is_floating_point_v<Data>)
  {
    // For numeric types, just add 1
    return val + Data{1};
  }
  else if constexpr (std::is_same_v<Data, std::string>)
  {
    // For strings, we can append a character to make it lexicographically larger
    return val + "~";
  }
  else
  {
    // For other types, we don't have a general solution
    // Just return the value itself (test may not work properly)
    return val;
  }
}

/* ************************************************************************** */

// Extended SetVec test functions

// Test insertion with duplicates (should reject duplicates)
template <typename Data>
void SetVecInsertDuplicates(uint &testnum, uint &testerr, lasd::SetVec<Data> &set, const Data &val)
{
  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") SetVec duplicate rejection test: ";

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
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test binary search functionality (indirectly through Insert and Exists)
template <typename Data>
void SetVecBinarySearch(uint &testnum, uint &testerr, lasd::SetVec<Data> &set,
                        const Data &minVal, const Data &midVal, const Data &maxVal)
{
  if (!(minVal < midVal && midVal < maxVal))
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") SetVec binary search test skipped - values must be in ascending order" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") SetVec binary search functionality: ";

    // Clear the set
    set.Clear();

    // Insert values in non-sequential order to test binary search insertion
    set.Insert(maxVal);
    set.Insert(minVal);
    set.Insert(midVal);

    // Calculate intermediate values for search
    Data belowMin = GetValueBefore(minVal);

    // Create a value between minVal and midVal
    Data betweenMinMid;
    if constexpr (std::is_integral_v<Data> || std::is_floating_point_v<Data>)
    {
      // For numeric types, we can calculate intermediate value
      betweenMinMid = minVal + (midVal - minVal) / 2;
      if (betweenMinMid == minVal || betweenMinMid == midVal)
      {
        betweenMinMid = minVal; // If too close, just use minVal
      }
    }
    else if constexpr (std::is_same_v<Data, std::string>)
    {
      // For strings, we can concatenate
      betweenMinMid = minVal + "_" + midVal;
    }
    else
    {
      // For other types, just use minVal (test may not work correctly)
      betweenMinMid = minVal;
    }

    Data aboveMax = GetValueAfter(maxVal);

    // Test Exists for values in the set
    bool existsMin = set.Exists(minVal);
    bool existsMid = set.Exists(midVal);
    bool existsMax = set.Exists(maxVal);

    // Test Exists for values not in the set
    bool notExistsBelowMin = !set.Exists(belowMin);
    bool notExistsBetween = !set.Exists(betweenMinMid);
    bool notExistsAboveMax = !set.Exists(aboveMax);

    // Verify that order is maintained (check Min and Max)
    bool minCorrect = (set.Min() == minVal);
    bool maxCorrect = (set.Max() == maxVal);

    // Verify all conditions
    tst = existsMin && existsMid && existsMax &&
          notExistsBelowMin && notExistsBetween && notExistsAboveMax &&
          minCorrect && maxCorrect;

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test predecessor and successor functionality
template <typename Data>
void SetVecPredSucc(uint &testnum, uint &testerr, lasd::SetVec<Data> &set,
                    const Data &val1, const Data &val2, const Data &val3, const Data &val4)
{
  if (!(val1 < val2 && val2 < val3 && val3 < val4))
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") SetVec predecessor/successor test skipped - values must be in ascending order" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") SetVec predecessor and successor functionality: ";

    // Clear the set and insert values
    set.Clear();
    set.Insert(val1);
    set.Insert(val3);
    // Note: Intentionally not inserting val2 and val4

    // Test predecessor for different scenarios

    // 1. Predecessor of a value in the set with a predecessor
    bool predInSetCorrect = (set.Predecessor(val3) == val1);

    // 2. Predecessor of a value not in the set but between existing values
    Data betweenVal = val2; // val2 is between val1 and val3
    bool predBetweenCorrect = (set.Predecessor(betweenVal) == val1);

    // 3. Predecessor of a value greater than any in the set
    Data aboveVal = val4; // val4 is greater than val3
    bool predAboveCorrect = (set.Predecessor(aboveVal) == val3);

    // Test successor for different scenarios

    // 1. Successor of a value in the set with a successor
    bool succInSetCorrect = (set.Successor(val1) == val3);

    // 2. Successor of a value not in the set but between existing values
    bool succBetweenCorrect = (set.Successor(betweenVal) == val3);

    // 3. Successor of a value less than any in the set
    Data belowVal = GetValueBefore(val1);
    bool succBelowCorrect = (set.Successor(belowVal) == val1);

    // Test exceptions for values without predecessor/successor
    bool predExceptionCorrect = false;
    bool succExceptionCorrect = false;

    try
    {
      set.Predecessor(val1); // Minimum value has no predecessor
    }
    catch (std::length_error &)
    {
      predExceptionCorrect = true;
    }
    catch (...)
    {
      predExceptionCorrect = false;
    }

    try
    {
      set.Successor(val3); // Maximum value has no successor
    }
    catch (std::length_error &)
    {
      succExceptionCorrect = true;
    }
    catch (...)
    {
      succExceptionCorrect = false;
    }

    // Verify all conditions
    tst = predInSetCorrect && predBetweenCorrect && predAboveCorrect &&
          succInSetCorrect && succBetweenCorrect && succBelowCorrect &&
          predExceptionCorrect && succExceptionCorrect;

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test removal operations
template <typename Data>
void SetVecRemoval(uint &testnum, uint &testerr, lasd::SetVec<Data> &set,
                   const Data &val1, const Data &val2, const Data &val3)
{
  if (!(val1 < val2 && val2 < val3))
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") SetVec removal operations test skipped - values must be in ascending order" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") SetVec removal operations: ";

    // Clear the set and insert values
    set.Clear();
    set.Insert(val1);
    set.Insert(val2);
    set.Insert(val3);

    // Test removal of middle element
    bool removeResult = set.Remove(val2);
    bool removeVerify = !set.Exists(val2) && set.Size() == 2;

    // Test that order is maintained after removal
    bool orderMaintained = (set.Min() == val1) && (set.Max() == val3) && (set.Successor(val1) == val3);

    // Test removal of minimum
    set.RemoveMin();
    bool minRemoved = !set.Exists(val1) && set.Size() == 1 && set.Min() == val3;

    // Test removal of maximum (should make set empty)
    set.RemoveMax();
    bool maxRemoved = set.Empty();

    // Verify all conditions
    tst = removeResult && removeVerify && orderMaintained && minRemoved && maxRemoved;

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test construction from TraversableContainer
template <typename Data>
void SetVecFromTraversable(uint &testnum, uint &testerr, const lasd::TraversableContainer<Data> &container)
{
  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") SetVec construction from TraversableContainer: ";

    // Create a list with the elements from the container
    lasd::List<Data> elements;
    container.Traverse([&elements](const Data &val)
                       { elements.InsertAtBack(val); });

    // Construct a SetVec from the traversable container
    lasd::SetVec<Data> set(container);

    // Check that duplicates were removed
    bool noDuplicates = true;
    for (ulong i = 0; i < set.Size(); i++)
    {
      for (ulong j = i + 1; j < set.Size(); j++)
      {
        if (set[i] == set[j])
        {
          noDuplicates = false;
          break;
        }
      }
      if (!noDuplicates)
        break;
    }

    // Check that all elements from container exist in the set
    bool allExist = true;
    elements.Traverse([&set, &allExist](const Data &val)
                      {
      if (!set.Exists(val)) {
        allExist = false;
      } });

    // Check that elements are in order
    bool inOrder = true;
    for (ulong i = 1; i < set.Size(); i++)
    {
      if (set[i - 1] >= set[i])
      {
        inOrder = false;
        break;
      }
    }

    // Verify all conditions
    tst = noDuplicates && allExist && inOrder;

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