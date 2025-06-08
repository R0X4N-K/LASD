#ifndef MYPQTEST_HPP
#define MYPQTEST_HPP

#include "../../pq/pq.hpp"

/* ************************************************************************** */

// Priority Queue specific test functions

template <typename Data>
void PQDefaultConstructor(uint &testnum, uint &testerr)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") PQ default constructor: ";
    lasd::PQHeap<Data> pq;
    std::cout << ((tst = (pq.Empty() && pq.Size() == 0)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQFromEmptyContainer(uint &testnum, uint &testerr)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") PQ from empty container: ";
    lasd::Vector<Data> emptyVec;
    lasd::PQHeap<Data> pq(emptyVec);
    std::cout << ((tst = (pq.Empty() && pq.Size() == 0)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQTipOnEmpty(uint &testnum, uint &testerr)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Tip() on empty PQ should throw exception: ";
    lasd::PQHeap<Data> emptyPQ;
    emptyPQ.Tip();
    tst = false;
    std::cout << "Error (No exception)!" << std::endl;
  }
  catch (std::length_error &)
  {
    tst = true;
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": Error (Wrong exception)!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQRemoveTipOnEmpty(uint &testnum, uint &testerr)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") RemoveTip() on empty PQ should throw exception: ";
    lasd::PQHeap<Data> emptyPQ;
    emptyPQ.RemoveTip();
    tst = false;
    std::cout << "Error (No exception)!" << std::endl;
  }
  catch (std::length_error &)
  {
    tst = true;
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": Error (Wrong exception)!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQTipNRemoveOnEmpty(uint &testnum, uint &testerr)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") TipNRemove() on empty PQ should throw exception: ";
    lasd::PQHeap<Data> emptyPQ;
    emptyPQ.TipNRemove();
    tst = false;
    std::cout << "Error (No exception)!" << std::endl;
  }
  catch (std::length_error &)
  {
    tst = true;
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": Error (Wrong exception)!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQInsert(uint &testnum, uint &testerr, lasd::PQHeap<Data> &pq, const Data &val)
{
  bool tst;
  testnum++;
  ulong oldSize = pq.Size();
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Insert \"" << val << "\" in PQ: ";
    pq.Insert(val);
    std::cout << ((tst = (pq.Size() == oldSize + 1)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQInsertMove(uint &testnum, uint &testerr, lasd::PQHeap<Data> &pq, Data &&val)
{
  bool tst;
  testnum++;
  ulong oldSize = pq.Size();
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Insert with move \"" << val << "\" in PQ: ";
    pq.Insert(std::move(val));
    std::cout << ((tst = (pq.Size() == oldSize + 1)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQSingleElement(uint &testnum, uint &testerr, const Data &val)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Single element PQ with \"" << val << "\": ";
    lasd::PQHeap<Data> singlePQ;
    singlePQ.Insert(val);
    std::cout << ((tst = (singlePQ.Size() == 1 && !singlePQ.Empty() && singlePQ.Tip() == val)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQSingleElementRemove(uint &testnum, uint &testerr, const Data &val)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Single element PQ TipNRemove() with \"" << val << "\": ";
    lasd::PQHeap<Data> singlePQ;
    singlePQ.Insert(val);
    Data removed = singlePQ.TipNRemove();
    std::cout << ((tst = (singlePQ.Empty() && singlePQ.Size() == 0 && removed == val)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQDuplicateInsertions(uint &testnum, uint &testerr, const Data &val, ulong count)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Insert " << count << " duplicates of \"" << val << "\": ";
    lasd::PQHeap<Data> dupPQ;
    for (ulong i = 0; i < count; ++i)
    {
      dupPQ.Insert(val);
    }
    bool allSame = true;
    for (ulong i = 0; i < count && !dupPQ.Empty(); ++i)
    {
      if (dupPQ.TipNRemove() != val)
      {
        allSame = false;
        break;
      }
    }
    std::cout << ((tst = (allSame && dupPQ.Empty())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQFromDuplicates(uint &testnum, uint &testerr, const Data &val, ulong count)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") PQ from container with " << count << " duplicates: ";
    lasd::Vector<Data> dupVec(count);
    for (ulong i = 0; i < count; ++i)
    {
      dupVec[i] = val;
    }
    lasd::PQHeap<Data> dupPQ(dupVec);
    std::cout << ((tst = (dupPQ.Size() == count && !dupPQ.Empty() && dupPQ.Tip() == val)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQClear(uint &testnum, uint &testerr, lasd::PQHeap<Data> &pq)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") PQ Clear() operation: ";
    pq.Clear();
    std::cout << ((tst = (pq.Empty() && pq.Size() == 0)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQAfterClear(uint &testnum, uint &testerr, lasd::PQHeap<Data> &pq, const Data &newVal)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Operations after Clear() with \"" << newVal << "\": ";
    pq.Insert(newVal);
    std::cout << ((tst = (pq.Size() == 1 && pq.Tip() == newVal)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQChangeOutOfBounds(uint &testnum, uint &testerr, lasd::PQHeap<Data> &pq, ulong invalidIndex, const Data &val)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Change() with out of bounds index " << invalidIndex << ": ";
    pq.Change(invalidIndex, val);
    tst = false;
    std::cout << "Error (No exception)!" << std::endl;
  }
  catch (std::out_of_range &)
  {
    tst = true;
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": Error (Wrong exception)!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQGetAtOutOfBounds(uint &testnum, uint &testerr, lasd::PQHeap<Data> &pq, ulong invalidIndex)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") GetAt() with out of bounds index " << invalidIndex << ": ";
    pq[invalidIndex];
    tst = false;
    std::cout << "Error (No exception)!" << std::endl;
  }
  catch (std::out_of_range &)
  {
    tst = true;
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": Error (Wrong exception)!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQPriorityOrder(uint &testnum, uint &testerr, const lasd::Vector<Data> &values)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Priority order verification: ";
    lasd::PQHeap<Data> pq(values);

    bool correctOrder = true;
    Data lastRemoved = pq.TipNRemove();

    while (!pq.Empty())
    {
      Data current = pq.TipNRemove();
      if (current > lastRemoved)
      {
        correctOrder = false;
        break;
      }
      lastRemoved = current;
    }

    std::cout << ((tst = correctOrder) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQStressInsertions(uint &testnum, uint &testerr, const lasd::Vector<Data> &testData)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Stress test: Sequential insertions: ";
    lasd::PQHeap<Data> stressPQ;

    for (ulong i = 0; i < testData.Size(); ++i)
    {
      stressPQ.Insert(testData[i]);
    }

    std::cout << ((tst = (stressPQ.Size() == testData.Size())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQStressRemovals(uint &testnum, uint &testerr, const lasd::Vector<Data> &testData)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Stress test: Sequential removals: ";
    lasd::PQHeap<Data> stressPQ(testData);
    ulong originalSize = stressPQ.Size();

    for (ulong i = 0; i < originalSize && !stressPQ.Empty(); ++i)
    {
      stressPQ.RemoveTip();
    }

    std::cout << ((tst = stressPQ.Empty()) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQFromSortedAscending(uint &testnum, uint &testerr, const lasd::Vector<Data> &sortedData)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") PQ from ascending sorted data: ";
    lasd::PQHeap<Data> ascendingPQ(sortedData);
    Data maxElement = sortedData[sortedData.Size() - 1];
    std::cout << ((tst = (ascendingPQ.Size() == sortedData.Size() && ascendingPQ.Tip() == maxElement)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQFromSortedDescending(uint &testnum, uint &testerr, const lasd::Vector<Data> &sortedData)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") PQ from descending sorted data: ";
    lasd::PQHeap<Data> descendingPQ(sortedData);
    Data maxElement = sortedData[0];
    std::cout << ((tst = (descendingPQ.Size() == sortedData.Size() && descendingPQ.Tip() == maxElement)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQSizeConsistency(uint &testnum, uint &testerr, lasd::PQHeap<Data> &pq, ulong expectedSize)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") PQ size consistency check (expected " << expectedSize << "): ";
    std::cout << ((tst = (pq.Size() == expectedSize)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQEmptyConsistency(uint &testnum, uint &testerr, lasd::PQHeap<Data> &pq, bool expectedEmpty)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") PQ empty status consistency: ";
    std::cout << ((tst = (pq.Empty() == expectedEmpty)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQChangeAndVerify(uint &testnum, uint &testerr, lasd::PQHeap<Data> &pq, ulong index, const Data &oldVal, const Data &newVal)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Change index " << index << " from \"" << oldVal << "\" to \"" << newVal << "\": ";
    if (pq[index] == oldVal)
    {
      pq.Change(index, newVal);
      std::cout << ((tst = (pq[index] == newVal)) ? "Correct" : "Error") << "!" << std::endl;
    }
    else
    {
      tst = false;
      std::cout << "Error (Initial value mismatch)!" << std::endl;
    }
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQInsertRemoveSequence(uint &testnum, uint &testerr, const Data &val1, const Data &val2, const Data &val3)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Insert-Remove sequence test: ";
    lasd::PQHeap<Data> seqPQ;

    seqPQ.Insert(val1);
    seqPQ.Insert(val2);
    seqPQ.Insert(val3);

    ulong sizeAfterInserts = seqPQ.Size();
    Data tip1 = seqPQ.TipNRemove();
    Data tip2 = seqPQ.TipNRemove();
    Data tip3 = seqPQ.TipNRemove();

    std::cout << ((tst = (sizeAfterInserts == 3 && seqPQ.Empty() && tip1 >= tip2 && tip2 >= tip3)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQCopyConstructor(uint &testnum, uint &testerr, const lasd::Vector<Data> &data)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") PQ copy constructor maintains priority order: ";
    lasd::PQHeap<Data> originalPQ(data);
    lasd::PQHeap<Data> copiedPQ(originalPQ);
    std::cout << ((tst = (copiedPQ.Size() == originalPQ.Size() && !copiedPQ.Empty() && copiedPQ.Tip() == originalPQ.Tip())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void PQMoveConstructor(uint &testnum, uint &testerr, const lasd::Vector<Data> &data)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") PQ move constructor maintains priority order: ";
    lasd::PQHeap<Data> originalPQ(data);
    Data expectedTip = originalPQ.Tip();
    ulong expectedSize = originalPQ.Size();
    lasd::PQHeap<Data> movedPQ(std::move(originalPQ));
    std::cout << ((tst = (movedPQ.Size() == expectedSize && !movedPQ.Empty() && movedPQ.Tip() == expectedTip)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

/* ************************************************************************** */

// Complete test functions for different data types

void mytestPQInt(uint &testnum, uint &testerr)
{
  uint loctestnum = 0, loctesterr = 0;
  std::cout << std::endl
            << "Begin of My PQ<int> Extended Test:" << std::endl;

  try
  {
    // Test constructors
    PQDefaultConstructor<int>(loctestnum, loctesterr);
    PQFromEmptyContainer<int>(loctestnum, loctesterr);

    // Test empty PQ operations
    PQTipOnEmpty<int>(loctestnum, loctesterr);
    PQRemoveTipOnEmpty<int>(loctestnum, loctesterr);
    PQTipNRemoveOnEmpty<int>(loctestnum, loctesterr);

    // Test single element operations
    PQSingleElement<int>(loctestnum, loctesterr, 42);
    PQSingleElementRemove<int>(loctestnum, loctesterr, 42);

    // Test duplicate elements
    PQDuplicateInsertions<int>(loctestnum, loctesterr, 100, 5);
    PQFromDuplicates<int>(loctestnum, loctesterr, 100, 5);

    // Test Insert operations
    lasd::PQHeap<int> testPQ;
    PQInsert<int>(loctestnum, loctesterr, testPQ, 50);
    PQInsert<int>(loctestnum, loctesterr, testPQ, 25);
    PQInsert<int>(loctestnum, loctesterr, testPQ, 75);

    // Test out of bounds operations
    PQChangeOutOfBounds<int>(loctestnum, loctesterr, testPQ, 10, 99);
    PQGetAtOutOfBounds<int>(loctestnum, loctesterr, testPQ, 10);

    // Test Change operations
    PQChangeAndVerify<int>(loctestnum, loctesterr, testPQ, 0, 75, 100);

    // Test Clear operation
    PQClear<int>(loctestnum, loctesterr, testPQ);
    PQAfterClear<int>(loctestnum, loctesterr, testPQ, 77);

    // Test sorted data scenarios
    lasd::Vector<int> ascendingData(5);
    ascendingData[0] = 1;
    ascendingData[1] = 2;
    ascendingData[2] = 3;
    ascendingData[3] = 4;
    ascendingData[4] = 5;
    PQFromSortedAscending<int>(loctestnum, loctesterr, ascendingData);

    lasd::Vector<int> descendingData(5);
    descendingData[0] = 5;
    descendingData[1] = 4;
    descendingData[2] = 3;
    descendingData[3] = 2;
    descendingData[4] = 1;
    PQFromSortedDescending<int>(loctestnum, loctesterr, descendingData);

    // Test priority order
    lasd::Vector<int> randomData(6);
    randomData[0] = 15;
    randomData[1] = 8;
    randomData[2] = 22;
    randomData[3] = 3;
    randomData[4] = 11;
    randomData[5] = 27;
    PQPriorityOrder<int>(loctestnum, loctesterr, randomData);

    // Test stress operations
    lasd::Vector<int> stressData(8);
    stressData[0] = 15;
    stressData[1] = 8;
    stressData[2] = 22;
    stressData[3] = 3;
    stressData[4] = 11;
    stressData[5] = 27;
    stressData[6] = 6;
    stressData[7] = 19;
    PQStressInsertions<int>(loctestnum, loctesterr, stressData);
    PQStressRemovals<int>(loctestnum, loctesterr, stressData);

    // Test Insert-Remove sequence
    PQInsertRemoveSequence<int>(loctestnum, loctesterr, 30, 10, 20);

    // Test copy and move constructors
    PQCopyConstructor<int>(loctestnum, loctesterr, stressData);
    PQMoveConstructor<int>(loctestnum, loctesterr, stressData);

    // Test consistency checks
    lasd::PQHeap<int> consistencyPQ(stressData);
    PQSizeConsistency<int>(loctestnum, loctesterr, consistencyPQ, consistencyPQ.Size());
    PQEmptyConsistency<int>(loctestnum, loctesterr, consistencyPQ, false);
  }
  catch (...)
  {
    loctestnum++;
    loctesterr++;
    std::cout << std::endl
              << "Unmanaged error in My PQ<int> Extended Test!" << std::endl;
  }

  std::cout << "End of My PQ<int> Extended Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void mytestPQString(uint &testnum, uint &testerr)
{
  uint loctestnum = 0, loctesterr = 0;
  std::cout << std::endl
            << "Begin of My PQ<string> Extended Test:" << std::endl;

  try
  {
    // Test constructors
    PQDefaultConstructor<std::string>(loctestnum, loctesterr);
    PQFromEmptyContainer<std::string>(loctestnum, loctesterr);

    // Test empty operations
    PQTipOnEmpty<std::string>(loctestnum, loctesterr);
    PQRemoveTipOnEmpty<std::string>(loctestnum, loctesterr);
    PQTipNRemoveOnEmpty<std::string>(loctestnum, loctesterr);

    // Test single element
    PQSingleElement<std::string>(loctestnum, loctesterr, std::string("unique"));
    PQSingleElementRemove<std::string>(loctestnum, loctesterr, std::string("unique"));

    // Test duplicates
    PQDuplicateInsertions<std::string>(loctestnum, loctesterr, std::string("duplicate"), 4);
    PQFromDuplicates<std::string>(loctestnum, loctesterr, std::string("duplicate"), 4);

    // Test Insert operations
    lasd::PQHeap<std::string> strTestPQ;
    PQInsert<std::string>(loctestnum, loctesterr, strTestPQ, std::string("medium"));
    PQInsert<std::string>(loctestnum, loctesterr, strTestPQ, std::string("small"));
    PQInsert<std::string>(loctestnum, loctesterr, strTestPQ, std::string("large"));

    // Test out of bounds
    PQChangeOutOfBounds<std::string>(loctestnum, loctesterr, strTestPQ, 10, std::string("invalid"));
    PQGetAtOutOfBounds<std::string>(loctestnum, loctesterr, strTestPQ, 10);

    // Test Change operations
    PQChangeAndVerify<std::string>(loctestnum, loctesterr, strTestPQ, 0, std::string("small"), std::string("zzz"));

    // Test Clear operation
    PQClear<std::string>(loctestnum, loctesterr, strTestPQ);
    PQAfterClear<std::string>(loctestnum, loctesterr, strTestPQ, std::string("new_value"));

    // Test sorted string data
    lasd::Vector<std::string> ascendingStrData(4);
    ascendingStrData[0] = std::string("alpha");
    ascendingStrData[1] = std::string("beta");
    ascendingStrData[2] = std::string("gamma");
    ascendingStrData[3] = std::string("omega");
    PQFromSortedAscending<std::string>(loctestnum, loctesterr, ascendingStrData);

    lasd::Vector<std::string> descendingStrData(4);
    descendingStrData[0] = std::string("omega");
    descendingStrData[1] = std::string("gamma");
    descendingStrData[2] = std::string("beta");
    descendingStrData[3] = std::string("alpha");
    PQFromSortedDescending<std::string>(loctestnum, loctesterr, descendingStrData);

    // Test priority order with strings
    lasd::Vector<std::string> randomStrData(5);
    randomStrData[0] = std::string("zebra");
    randomStrData[1] = std::string("apple");
    randomStrData[2] = std::string("orange");
    randomStrData[3] = std::string("banana");
    randomStrData[4] = std::string("kiwi");
    PQPriorityOrder<std::string>(loctestnum, loctesterr, randomStrData);

    // Test stress operations with strings
    lasd::Vector<std::string> strStressData(6);
    strStressData[0] = std::string("zebra");
    strStressData[1] = std::string("apple");
    strStressData[2] = std::string("orange");
    strStressData[3] = std::string("banana");
    strStressData[4] = std::string("kiwi");
    strStressData[5] = std::string("mango");
    PQStressInsertions<std::string>(loctestnum, loctesterr, strStressData);
    PQStressRemovals<std::string>(loctestnum, loctesterr, strStressData);

    // Test Insert-Remove sequence
    PQInsertRemoveSequence<std::string>(loctestnum, loctesterr, std::string("charlie"), std::string("alpha"), std::string("bravo"));

    // Test copy and move constructors
    PQCopyConstructor<std::string>(loctestnum, loctesterr, strStressData);
    PQMoveConstructor<std::string>(loctestnum, loctesterr, strStressData);

    // Test consistency
    lasd::PQHeap<std::string> strConsistencyPQ(strStressData);
    PQSizeConsistency<std::string>(loctestnum, loctesterr, strConsistencyPQ, strConsistencyPQ.Size());
    PQEmptyConsistency<std::string>(loctestnum, loctesterr, strConsistencyPQ, false);
  }
  catch (...)
  {
    loctestnum++;
    loctesterr++;
    std::cout << std::endl
              << "Unmanaged error in My PQ<string> Extended Test!" << std::endl;
  }

  std::cout << "End of My PQ<string> Extended Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

#endif