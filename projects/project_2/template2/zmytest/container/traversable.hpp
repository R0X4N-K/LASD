#ifndef MYTRAVERSABLETEST_HPP
#define MYTRAVERSABLETEST_HPP

#include "../../container/traversable.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

// Extended test functions for TraversableContainer

// Test Fold consistency with Traverse
template <typename Data>
void FoldTraverseConsistency(uint &testnum, uint &testerr, const lasd::TraversableContainer<Data> &con)
{
  bool tst = true;
  testnum++;

  lasd::List<Data> traverseElements;
  lasd::List<Data> foldElements;

  // Collect elements via Traverse
  con.Traverse([&traverseElements](const Data &val)
               { traverseElements.InsertAtBack(val); });

  // Collect elements via Fold
  foldElements = con.template Fold<lasd::List<Data>>([](const Data &val, const lasd::List<Data> &acc) -> lasd::List<Data>
                                                     {
    lasd::List<Data> result(acc);
    result.InsertAtBack(val);
    return result; }, foldElements);

  std::cout << " " << testnum << " (" << testerr << ") Fold/Traverse consistency check: ";

  bool sizeMatch = (traverseElements.Size() == foldElements.Size());
  bool contentMatch = true;

  if (sizeMatch)
  {
    for (ulong i = 0; i < traverseElements.Size(); i++)
    {
      if (traverseElements[i] != foldElements[i])
      {
        contentMatch = false;
        break;
      }
    }
  }

  tst = sizeMatch && contentMatch;
  std::cout << (tst ? "Elements match" : "Elements differ") << ": ";
  std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

// Test with non-trivial accumulator types
template <typename Data>
void FoldComplexAccumulator(uint &testnum, uint &testerr, const lasd::TraversableContainer<Data> &con)
{
  bool tst = true;
  testnum++;

  // Create a complex accumulator (pair of count and sum)
  struct Accumulator
  {
    ulong count = 0;
    Data sum;

    Accumulator() : count(0), sum(Data{}) {}

    bool operator==(const Accumulator &other) const
    {
      return count == other.count && sum == other.sum;
    }
  };

  Accumulator expected;
  expected.sum = Data{};
  con.Traverse([&expected](const Data &val)
               {
    expected.count++;
    expected.sum = expected.sum + val; });

  Accumulator initial;
  initial.sum = Data{};
  Accumulator result = con.template Fold<Accumulator>([](const Data &val, const Accumulator &acc) -> Accumulator
                                                      {
    Accumulator newAcc = acc;
    newAcc.count++;
    newAcc.sum = newAcc.sum + val;
    return newAcc; }, initial);

  std::cout << " " << testnum << " (" << testerr << ") Fold with complex accumulator: ";
  std::cout << "Expected [count=" << expected.count << ", sum=" << expected.sum << "], ";
  std::cout << "Got [count=" << result.count << ", sum=" << result.sum << "]: ";

  tst = (expected == result);
  std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

// Test conditional traversal (early termination simulation)
template <typename Data>
void ConditionalTraverse(uint &testnum, uint &testerr, const lasd::TraversableContainer<Data> &con, const Data &targetValue)
{
  bool tst = true;
  testnum++;

  bool foundTarget = false;
  uint visitCount = 0;

  // Use Traverse to find a value, counting how many elements are visited
  con.Traverse([&foundTarget, &visitCount, &targetValue](const Data &val)
               {
                 visitCount++;
                 if (val == targetValue)
                 {
                   foundTarget = true;
                 }
                 // Note: We can't actually stop the traversal early, but we can count how many elements are visited
               });

  // Use Exists which should do the same thing
  bool existsResult = con.Exists(targetValue);

  std::cout << " " << testnum << " (" << testerr << ") Conditional traversal consistency: ";
  std::cout << "Traverse found " << (foundTarget ? "true" : "false") << ", Exists returned " << (existsResult ? "true" : "false");
  std::cout << " after visiting " << visitCount << " elements: ";

  tst = (foundTarget == existsResult);
  std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

/* ************************************************************************** */

// Extended test functions for PreOrderTraversableContainer
// Test consistency between PreOrderFold and PreOrderTraverse
template <typename Data>
void PreOrderFoldConsistency(uint &testnum, uint &testerr, const lasd::PreOrderTraversableContainer<Data> &con)
{
  bool tst = true;
  testnum++;

  lasd::List<Data> traverseElements;
  lasd::List<Data> foldElements;

  // Collect elements via PreOrderTraverse
  con.PreOrderTraverse([&traverseElements](const Data &val)
                       { traverseElements.InsertAtBack(val); });

  // Collect elements via PreOrderFold
  foldElements = con.template PreOrderFold<lasd::List<Data>>([](const Data &val, const lasd::List<Data> &acc) -> lasd::List<Data>
                                                             {
    lasd::List<Data> result(acc);
    result.InsertAtBack(val);
    return result; }, foldElements);

  std::cout << " " << testnum << " (" << testerr << ") PreOrderFold/PreOrderTraverse consistency: ";

  bool sizeMatch = (traverseElements.Size() == foldElements.Size());
  bool contentMatch = true;

  if (sizeMatch)
  {
    for (ulong i = 0; i < traverseElements.Size(); i++)
    {
      if (traverseElements[i] != foldElements[i])
      {
        contentMatch = false;
        break;
      }
    }
  }

  tst = sizeMatch && contentMatch;
  std::cout << (tst ? "Elements match" : "Elements differ") << ": ";
  std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

/* ************************************************************************** */

// Extended test functions for PostOrderTraversableContainer
// Test consistency between PostOrderFold and PostOrderTraverse
template <typename Data>
void PostOrderFoldConsistency(uint &testnum, uint &testerr, const lasd::PostOrderTraversableContainer<Data> &con)
{
  bool tst = true;
  testnum++;

  lasd::List<Data> traverseElements;
  lasd::List<Data> foldElements;

  // Collect elements via PostOrderTraverse
  con.PostOrderTraverse([&traverseElements](const Data &val)
                        { traverseElements.InsertAtBack(val); });

  // Collect elements via PostOrderFold
  foldElements = con.template PostOrderFold<lasd::List<Data>>([](const Data &val, const lasd::List<Data> &acc) -> lasd::List<Data>
                                                              {
    lasd::List<Data> result(acc);
    result.InsertAtBack(val);
    return result; }, foldElements);

  std::cout << " " << testnum << " (" << testerr << ") PostOrderFold/PostOrderTraverse consistency: ";

  bool sizeMatch = (traverseElements.Size() == foldElements.Size());
  bool contentMatch = true;

  if (sizeMatch)
  {
    for (ulong i = 0; i < traverseElements.Size(); i++)
    {
      if (traverseElements[i] != foldElements[i])
      {
        contentMatch = false;
        break;
      }
    }
  }

  tst = sizeMatch && contentMatch;
  std::cout << (tst ? "Elements match" : "Elements differ") << ": ";
  std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

// Test difference between PreOrder and PostOrder traversal
template <typename Data>
void OrderDifference(uint &testnum, uint &testerr,
                     const lasd::PreOrderTraversableContainer<Data> &precon,
                     const lasd::PostOrderTraversableContainer<Data> &postcon)
{
  // This test is valid only for non-linear containers where pre-order and post-order differ
  bool tst = true;
  testnum++;

  lasd::List<Data> preOrderElements;
  lasd::List<Data> postOrderElements;

  // Collect elements via PreOrderTraverse
  precon.PreOrderTraverse([&preOrderElements](const Data &val)
                          { preOrderElements.InsertAtBack(val); });

  // Collect elements via PostOrderTraverse
  postcon.PostOrderTraverse([&postOrderElements](const Data &val)
                            { postOrderElements.InsertAtBack(val); });

  std::cout << " " << testnum << " (" << testerr << ") PreOrder vs PostOrder traversal: ";

  // For linear containers, these should be the same
  // For non-linear containers (like trees), these should differ
  bool elementsMatch = (preOrderElements.Size() == postOrderElements.Size());

  if (elementsMatch)
  {
    for (ulong i = 0; i < preOrderElements.Size(); i++)
    {
      if (preOrderElements[i] != postOrderElements[i])
      {
        elementsMatch = false;
        break;
      }
    }
  }

  // Note: This test is informational - it's not a pass/fail test
  // For linear containers, pre-order and post-order should be the same
  // For non-linear containers, they should differ
  std::cout << (elementsMatch ? "Traversal orders match (linear container)" : "Traversal orders differ (non-linear container)") << std::endl;

  // Do not increment error count as this is informational
}

/* ************************************************************************** */

#endif