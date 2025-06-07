#ifndef MYMAPPABLETEST_HPP
#define MYMAPPABLETEST_HPP

#include "../../container/mappable.hpp"
#include "../../vector/vector.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

// Extended MappableContainer tests

// Test Map on empty container
template <typename Data>
void MapEmpty(uint &testnum, uint &testerr, lasd::MappableContainer<Data> &con)
{
  if (!con.Empty())
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Map on empty container test skipped - container is not empty" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Map on empty container: ";
    ulong mapCallCount = 0;

    con.Map([&mapCallCount](Data &val)
            { mapCallCount++; });

    tst = (mapCallCount == 0);
    std::cout << (tst ? "No mapping operations performed" : "Unexpectedly performed mapping") << ": ";
    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test Map function composition
template <typename Data>
void MapComposition(uint &testnum, uint &testerr, lasd::MappableContainer<Data> &con,
                    const Data &increment, const Data &multiplier)
{
  if (con.Empty())
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Map composition test skipped - container is empty" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  // Create a copy for verification
  lasd::Vector<Data> expected(con.Size());
  ulong index = 0;
  con.Traverse([&expected, &index](const Data &val)
               { expected[index++] = val; });

  // Apply transformations to expected results
  for (ulong i = 0; i < expected.Size(); i++)
  {
    // First transformation: increment
    expected[i] = expected[i] + increment;
    // Second transformation: multiply
    expected[i] = expected[i] * multiplier;
  }

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Map function composition: ";

    // First map operation
    con.Map([&increment](Data &val)
            { val = val + increment; });

    // Second map operation
    con.Map([&multiplier](Data &val)
            { val = val * multiplier; });

    // Verify results
    index = 0;
    con.Traverse([&expected, &index, &tst](const Data &val)
                 {
      if (val != expected[index++]) {
        tst = false;
      } });

    std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "Exception thrown: " << exc.what() << ": Error!" << std::endl;
  }

  testerr += (1 - (uint)tst);
}

// Test conditional Map function
template <typename Data>
void MapConditional(uint &testnum, uint &testerr, lasd::MappableContainer<Data> &con,
                    const Data &threshold, const Data &valueIfOver)
{
  if (con.Empty())
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Conditional Map test skipped - container is empty" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  // Create a copy for verification
  lasd::Vector<Data> expected(con.Size());
  ulong index = 0;
  con.Traverse([&expected, &index](const Data &val)
               { expected[index++] = val; });

  // Apply conditional transformation to expected results
  for (ulong i = 0; i < expected.Size(); i++)
  {
    if (expected[i] > threshold)
    {
      expected[i] = valueIfOver;
    }
  }

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Conditional Map function: ";

    // Apply conditional map
    con.Map([&threshold, &valueIfOver](Data &val)
            {
      if (val > threshold) {
        val = valueIfOver;
      } });

    // Verify results
    index = 0;
    con.Traverse([&expected, &index, &tst](const Data &val)
                 {
      if (val != expected[index++]) {
        tst = false;
      } });

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

// Extended PreOrderMappableContainer tests

// Test that Map and PreOrderMap are equivalent
template <typename Data>
void MapPreOrderEquivalence(uint &testnum, uint &testerr, lasd::PreOrderMappableContainer<Data> &con, const Data &increment)
{
  if (con.Empty())
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Map/PreOrderMap equivalence test skipped - container is empty" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  // Create two copies of the container
  lasd::Vector<Data> original(con.Size());
  ulong index = 0;
  con.Traverse([&original, &index](const Data &val)
               { original[index++] = val; });

  // Copy original data to container
  index = 0;
  con.Map([&original, &index](Data &val)
          { val = original[index++]; });

  // First approach: using Map
  lasd::Vector<Data> afterMap(con.Size());
  con.Map([&increment](Data &val)
          { val = val + increment; });

  index = 0;
  con.Traverse([&afterMap, &index](const Data &val)
               { afterMap[index++] = val; });

  // Reset container to original state
  index = 0;
  con.Map([&original, &index](Data &val)
          { val = original[index++]; });

  // Second approach: using PreOrderMap
  lasd::Vector<Data> afterPreOrderMap(con.Size());
  con.PreOrderMap([&increment](Data &val)
                  { val = val + increment; });

  index = 0;
  con.Traverse([&afterPreOrderMap, &index](const Data &val)
               { afterPreOrderMap[index++] = val; });

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Map and PreOrderMap equivalence: ";

    // Verify that both approaches yield the same results
    for (ulong i = 0; i < afterMap.Size(); i++)
    {
      if (afterMap[i] != afterPreOrderMap[i])
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

// Extended PostOrderMappableContainer tests

// Test that Map and PostOrderMap are equivalent
template <typename Data>
void MapPostOrderEquivalence(uint &testnum, uint &testerr, lasd::PostOrderMappableContainer<Data> &con, const Data &increment)
{
  if (con.Empty())
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Map/PostOrderMap equivalence test skipped - container is empty" << std::endl;
    return;
  }

  bool tst = true;
  testnum++;

  // Create two copies of the container
  lasd::Vector<Data> original(con.Size());
  ulong index = 0;
  con.Traverse([&original, &index](const Data &val)
               { original[index++] = val; });

  // Copy original data to container
  index = 0;
  con.Map([&original, &index](Data &val)
          { val = original[index++]; });

  // First approach: using Map
  lasd::Vector<Data> afterMap(con.Size());
  con.Map([&increment](Data &val)
          { val = val + increment; });

  index = 0;
  con.Traverse([&afterMap, &index](const Data &val)
               { afterMap[index++] = val; });

  // Reset container to original state
  index = 0;
  con.Map([&original, &index](Data &val)
          { val = original[index++]; });

  // Second approach: using PostOrderMap
  lasd::Vector<Data> afterPostOrderMap(con.Size());
  con.PostOrderMap([&increment](Data &val)
                   { val = val + increment; });

  index = 0;
  con.Traverse([&afterPostOrderMap, &index](const Data &val)
               { afterPostOrderMap[index++] = val; });

  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Map and PostOrderMap equivalence: ";

    // Verify that both approaches yield the same results for the final container state
    // (Note: for linear containers, pre-order and post-order traversal will produce different
    // intermediate states but the final result should be the same)
    for (ulong i = 0; i < afterMap.Size(); i++)
    {
      if (afterMap[i] != afterPostOrderMap[i])
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

// Test for difference between PreOrderMap and PostOrderMap
template <typename Data>
void PrePostOrderDifference(uint &testnum, uint &testerr,
                            lasd::PreOrderMappableContainer<Data> &precon,
                            lasd::PostOrderMappableContainer<Data> &postcon,
                            const Data &initialValue,
                            const Data &multiplyBy)
{
  if (precon.Empty() || precon.Size() < 2)
  {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Pre/Post order difference test skipped - container has fewer than 2 elements" << std::endl;
    return;
  }

  // This test is informational, it demonstrates the difference between pre-order and post-order
  // for non-linear structures. For linear structures, the difference is in the order of traversal,
  // but the final state will be the same.

  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Pre/Post order map behavior: ";

  // Initialize both containers with same values
  lasd::Vector<Data> initialValues(precon.Size(), initialValue);

  ulong index = 0;
  precon.Map([&initialValues, &index](Data &val)
             { val = initialValues[index++]; });

  index = 0;
  postcon.Map([&initialValues, &index](Data &val)
              { val = initialValues[index++]; });

  // The operation: First multiply the value by multiplyBy, then add 1
  // In pre-order, we visit parent first, then children
  // In post-order, we visit children first, then parent

  // For linear containers, this just means forward vs reverse traversal
  // For non-linear containers like trees, the difference is more significant

  precon.PreOrderMap([&multiplyBy](Data &val)
                     { val = val * multiplyBy + Data{1}; });

  postcon.PostOrderMap([&multiplyBy](Data &val)
                       { val = val * multiplyBy + Data{1}; });

  // For linear containers, the final state should be the same
  // For non-linear containers, the final state may differ

  lasd::List<Data> preResults;
  lasd::List<Data> postResults;

  precon.Traverse([&preResults](const Data &val)
                  { preResults.InsertAtBack(val); });

  postcon.Traverse([&postResults](const Data &val)
                   { postResults.InsertAtBack(val); });

  bool sameResults = (preResults.Size() == postResults.Size());
  if (sameResults)
  {
    for (ulong i = 0; i < preResults.Size(); i++)
    {
      if (preResults[i] != postResults[i])
      {
        sameResults = false;
        break;
      }
    }
  }

  // This is informational, not a pass/fail test
  std::cout << (sameResults ? "Final states are identical (linear container)" : "Final states differ (non-linear container)") << std::endl;
}

/* ************************************************************************** */

#endif