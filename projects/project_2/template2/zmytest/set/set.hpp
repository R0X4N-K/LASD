#ifndef MYSETTEST_HPP
#define MYSETTEST_HPP

#include "../../set/set.hpp"
#include "../../set/lst/setlst.hpp"
#include "../../set/vec/setvec.hpp"
#include "./lst/setlst.hpp"
#include "./vec/setvec.hpp"

/* ************************************************************************** */

// Common Set tests applicable to both implementations

// Test comparison between SetLst and SetVec
template <typename Data>
void CompareSetImplementations(uint &testnum, uint &testerr, lasd::SetLst<Data> &setlst, lasd::SetVec<Data> &setvec)
{
  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Comparison between SetLst and SetVec implementations: ";

    // Clear both sets
    setlst.Clear();
    setvec.Clear();

    // Insert the same elements in both sets
    Data val1 = Data{10};
    Data val2 = Data{20};
    Data val3 = Data{30};

    setlst.Insert(val1);
    setlst.Insert(val2);
    setlst.Insert(val3);

    setvec.Insert(val1);
    setvec.Insert(val2);
    setvec.Insert(val3);

    // Check sizes
    bool sizeEqual = (setlst.Size() == setvec.Size());

    // Check that each element in SetLst exists in SetVec
    bool allElementsInVec = true;
    for (ulong i = 0; i < setlst.Size(); i++)
    {
      if (!setvec.Exists(setlst[i]))
      {
        allElementsInVec = false;
        break;
      }
    }

    // Check that each element in SetVec exists in SetLst
    bool allElementsInLst = true;
    for (ulong i = 0; i < setvec.Size(); i++)
    {
      if (!setlst.Exists(setvec[i]))
      {
        allElementsInLst = false;
        break;
      }
    }

    // Check min/max consistency
    bool minEqual = (setlst.Min() == setvec.Min());
    bool maxEqual = (setlst.Max() == setvec.Max());

    // Remove the middle element from both sets
    setlst.Remove(val2);
    setvec.Remove(val2);

    // Check consistency after removal
    bool consistentAfterRemoval = (setlst.Size() == setvec.Size()) &&
                                  !setlst.Exists(val2) && !setvec.Exists(val2) &&
                                  (setlst.Min() == setvec.Min()) &&
                                  (setlst.Max() == setvec.Max());

    // Verify all conditions
    tst = sizeEqual && allElementsInVec && allElementsInLst &&
          minEqual && maxEqual && consistentAfterRemoval;

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test edge cases with boundary values
template <typename Data>
void SetBoundaryTests(uint &testnum, uint &testerr, lasd::Set<Data> &set,
                      const Data &smallVal, const Data &largeVal)
{
  if (!(smallVal < largeVal))
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Set boundary test skipped - values must be in ascending order" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Set boundary value tests: ";

    // Clear the set
    set.Clear();

    // Test operations on empty set
    bool emptyCorrect = set.Empty() && (set.Size() == 0);

    // Test exceptions on empty set
    bool minExceptionCorrect = false;
    bool maxExceptionCorrect = false;
    bool predExceptionCorrect = false;
    bool succExceptionCorrect = false;

    try
    {
      set.Min();
    }
    catch (std::length_error &)
    {
      minExceptionCorrect = true;
    }
    catch (...)
    {
      minExceptionCorrect = false;
    }

    try
    {
      set.Max();
    }
    catch (std::length_error &)
    {
      maxExceptionCorrect = true;
    }
    catch (...)
    {
      maxExceptionCorrect = false;
    }

    try
    {
      set.Predecessor(smallVal);
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
      set.Successor(smallVal);
    }
    catch (std::length_error &)
    {
      succExceptionCorrect = true;
    }
    catch (...)
    {
      succExceptionCorrect = false;
    }

    // Insert boundary values
    set.Insert(smallVal);
    set.Insert(largeVal);

    // Test min/max with boundary values
    bool minCorrect = (set.Min() == smallVal);
    bool maxCorrect = (set.Max() == largeVal);

    // Test predecessor/successor with boundary values
    bool predOfMaxCorrect = (set.Predecessor(largeVal) == smallVal);
    bool succOfMinCorrect = (set.Successor(smallVal) == largeVal);

    // Test exceptions for non-existent predecessor/successor
    bool predOfMinExceptionCorrect = false;
    bool succOfMaxExceptionCorrect = false;

    try
    {
      set.Predecessor(smallVal);
    }
    catch (std::length_error &)
    {
      predOfMinExceptionCorrect = true;
    }
    catch (...)
    {
      predOfMinExceptionCorrect = false;
    }

    try
    {
      set.Successor(largeVal);
    }
    catch (std::length_error &)
    {
      succOfMaxExceptionCorrect = true;
    }
    catch (...)
    {
      succOfMaxExceptionCorrect = false;
    }

    // Verify all conditions
    tst = emptyCorrect && minExceptionCorrect && maxExceptionCorrect &&
          predExceptionCorrect && succExceptionCorrect && minCorrect &&
          maxCorrect && predOfMaxCorrect && succOfMinCorrect &&
          predOfMinExceptionCorrect && succOfMaxExceptionCorrect;

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test operations sequence that stresses the set's ability to maintain order
template <typename Data>
void SetOrderStressTest(uint &testnum, uint &testerr, lasd::Set<Data> &set)
{
  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Set order maintenance stress test: ";

    // Clear the set
    set.Clear();

    // Create a sequence of values
    lasd::List<Data> values;
    for (int i = 0; i < 10; i++)
    {
      values.InsertAtBack(Data{i * 10});
    }

    // Insert values in reverse order to test sorting
    for (int i = 9; i >= 0; i--)
    {
      set.Insert(values[i]);
    }

    // Check that all values exist and are in order
    bool allExist = true;
    bool inOrder = true;

    for (int i = 0; i < 10; i++)
    {
      if (!set.Exists(values[i]))
      {
        allExist = false;
        break;
      }

      if (i > 0 && !(set[i - 1] < set[i]))
      {
        inOrder = false;
        break;
      }
    }

    // Remove odd-indexed elements
    for (int i = 1; i < 10; i += 2)
    {
      set.Remove(values[i]);
    }

    // Check that even-indexed elements still exist and are in order
    bool evenExist = true;
    bool evenInOrder = true;

    for (int i = 0; i < 10; i += 2)
    {
      if (!set.Exists(values[i]))
      {
        evenExist = false;
        break;
      }
    }

    for (ulong i = 1; i < set.Size(); i++)
    {
      if (!(set[i - 1] < set[i]))
      {
        evenInOrder = false;
        break;
      }
    }

    // Check min/max correctness
    bool minCorrect = (set.Min() == values[0]);
    bool maxCorrect = (set.Max() == values[8]);

    // Verify all conditions
    tst = allExist && inOrder && evenExist && evenInOrder && minCorrect && maxCorrect;

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