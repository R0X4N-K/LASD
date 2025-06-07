#ifndef MYHEAPTEST_HPP
#define MYHEAPTEST_HPP

#include "../../heap/heap.hpp"

/* ************************************************************************** */

// Heap member functions!

template <typename Data>
void HeapConstructorWithSize(uint &testnum, uint &testerr, ulong size)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap constructor with size " << size << ": ";
    lasd::HeapVec<Data> heap(size);
    std::cout << ((tst = (heap.Size() == size && heap.Empty() == (size == 0) && heap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapFromEmptyContainer(uint &testnum, uint &testerr)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap from empty container: ";
    lasd::Vector<Data> emptyVec;
    lasd::HeapVec<Data> heap(emptyVec);
    std::cout << ((tst = (heap.Empty() && heap.Size() == 0 && heap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapInsert(uint &testnum, uint &testerr, lasd::HeapVec<Data> &heap, const Data &val)
{
  bool tst;
  testnum++;
  ulong oldSize = heap.Size();
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Insert \"" << val << "\" in heap: ";
    heap.Insert(val);
    std::cout << ((tst = (heap.Size() == oldSize + 1 && heap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapInsertMove(uint &testnum, uint &testerr, lasd::HeapVec<Data> &heap, Data &&val)
{
  bool tst;
  testnum++;
  ulong oldSize = heap.Size();
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Insert with move \"" << val << "\" in heap: ";
    heap.Insert(std::move(val));
    std::cout << ((tst = (heap.Size() == oldSize + 1 && heap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapRemoveRoot(uint &testnum, uint &testerr, lasd::HeapVec<Data> &heap, bool chk)
{
  bool tst;
  testnum++;
  ulong oldSize = heap.Size();
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Remove root from heap: ";
    heap.RemoveRoot();
    std::cout << ((tst = (heap.Size() == oldSize - 1 && (heap.Empty() || heap.IsHeap()) && chk)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::length_error &exc)
  {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << std::endl
              << "Wrong exception: " << exc.what() << "!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapEmptyIsHeap(uint &testnum, uint &testerr)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Empty heap IsHeap() verification: ";
    lasd::HeapVec<Data> emptyHeap;
    std::cout << ((tst = emptyHeap.IsHeap()) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapEmptyHeapify(uint &testnum, uint &testerr)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Empty heap Heapify() operation: ";
    lasd::HeapVec<Data> emptyHeap;
    emptyHeap.Heapify();
    std::cout << ((tst = (emptyHeap.Empty() && emptyHeap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapEmptySort(uint &testnum, uint &testerr)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Empty heap Sort() operation: ";
    lasd::HeapVec<Data> emptyHeap;
    emptyHeap.Sort();
    std::cout << ((tst = emptyHeap.Empty()) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapSingleElement(uint &testnum, uint &testerr, const Data &val)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Single element heap with \"" << val << "\": ";
    lasd::HeapVec<Data> singleHeap;
    singleHeap.Insert(val);
    std::cout << ((tst = (singleHeap.Size() == 1 && singleHeap.IsHeap() && !singleHeap.Empty())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapSingleElementSort(uint &testnum, uint &testerr, const Data &val)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Single element heap Sort() with \"" << val << "\": ";
    lasd::HeapVec<Data> singleHeap;
    singleHeap.Insert(val);
    singleHeap.Sort();
    std::cout << ((tst = (singleHeap.Size() == 1 && singleHeap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapSingleElementRemove(uint &testnum, uint &testerr, const Data &val)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Single element heap RemoveRoot() with \"" << val << "\": ";
    lasd::HeapVec<Data> singleHeap;
    singleHeap.Insert(val);
    singleHeap.RemoveRoot();
    std::cout << ((tst = (singleHeap.Empty() && singleHeap.Size() == 0)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapAllDuplicates(uint &testnum, uint &testerr, const Data &val, ulong count)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap with " << count << " duplicates of \"" << val << "\": ";
    lasd::Vector<Data> duplicateVec(count);
    for (ulong i = 0; i < count; ++i)
    {
      duplicateVec[i] = val;
    }
    lasd::HeapVec<Data> duplicateHeap(duplicateVec);
    std::cout << ((tst = (duplicateHeap.Size() == count && duplicateHeap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapDuplicatesSort(uint &testnum, uint &testerr, const Data &val, ulong count)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Duplicate heap Sort() maintains size with \"" << val << "\": ";
    lasd::Vector<Data> duplicateVec(count);
    for (ulong i = 0; i < count; ++i)
    {
      duplicateVec[i] = val;
    }
    lasd::HeapVec<Data> duplicateHeap(duplicateVec);
    duplicateHeap.Sort();
    std::cout << ((tst = (duplicateHeap.Size() == count)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapPropertyAfterHeapify(uint &testnum, uint &testerr, lasd::HeapVec<Data> &heap)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap property after Heapify(): ";
    heap.Heapify();
    std::cout << ((tst = heap.IsHeap()) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapPropertyLostAfterSort(uint &testnum, uint &testerr, lasd::HeapVec<Data> &heap)
{
  bool tst;
  testnum++;
  ulong originalSize = heap.Size();
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap property lost after Sort(): ";
    heap.Sort();
    std::cout << ((tst = (!heap.IsHeap() && heap.Size() == originalSize)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapClear(uint &testnum, uint &testerr, lasd::HeapVec<Data> &heap)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap Clear() operation: ";
    heap.Clear();
    std::cout << ((tst = (heap.Empty() && heap.Size() == 0 && heap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapAfterClear(uint &testnum, uint &testerr, lasd::HeapVec<Data> &heap, const Data &newVal)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Operations after Clear() with \"" << newVal << "\": ";
    heap.Insert(newVal);
    std::cout << ((tst = (heap.Size() == 1 && heap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapFromSortedAscending(uint &testnum, uint &testerr, const lasd::Vector<Data> &sortedData)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap from ascending sorted data: ";
    lasd::HeapVec<Data> ascendingHeap(sortedData);
    std::cout << ((tst = (ascendingHeap.Size() == sortedData.Size() && ascendingHeap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapFromSortedDescending(uint &testnum, uint &testerr, const lasd::Vector<Data> &sortedData)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap from descending sorted data: ";
    lasd::HeapVec<Data> descendingHeap(sortedData);
    std::cout << ((tst = (descendingHeap.Size() == sortedData.Size() && descendingHeap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapStressInsertions(uint &testnum, uint &testerr, const lasd::Vector<Data> &testData)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Stress test: Sequential insertions maintain heap property: ";
    lasd::HeapVec<Data> stressHeap;
    bool allHeap = true;

    for (ulong i = 0; i < testData.Size(); ++i)
    {
      stressHeap.Insert(testData[i]);
      if (!stressHeap.IsHeap())
      {
        allHeap = false;
        break;
      }
    }

    std::cout << ((tst = (allHeap && stressHeap.Size() == testData.Size())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapStressRemovals(uint &testnum, uint &testerr, const lasd::Vector<Data> &testData)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Stress test: Sequential removals maintain heap property: ";
    lasd::HeapVec<Data> stressHeap(testData);
    bool allHeap = true;
    ulong originalSize = stressHeap.Size();

    for (ulong i = 0; i < originalSize && !stressHeap.Empty(); ++i)
    {
      stressHeap.RemoveRoot();
      if (!stressHeap.Empty() && !stressHeap.IsHeap())
      {
        allHeap = false;
        break;
      }
    }

    std::cout << ((tst = (allHeap && stressHeap.Empty())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapSizeConsistency(uint &testnum, uint &testerr, lasd::HeapVec<Data> &heap, ulong expectedSize)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap size consistency check (expected " << expectedSize << "): ";
    std::cout << ((tst = (heap.Size() == expectedSize)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapEmptyConsistency(uint &testnum, uint &testerr, lasd::HeapVec<Data> &heap, bool expectedEmpty)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap empty status consistency: ";
    std::cout << ((tst = (heap.Empty() == expectedEmpty)) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void DeepHeapVerification(uint &testnum, uint &testerr, const lasd::HeapVec<Data> &heap)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Deep heap property verification: ";
    bool isValidHeap = true;

    if (!heap.Empty())
    {
      for (ulong i = 0; i < heap.Size(); ++i)
      {
        ulong leftChild = (2 * i) + 1;
        ulong rightChild = (2 * i) + 2;

        if (leftChild < heap.Size() && heap[i] < heap[leftChild])
        {
          isValidHeap = false;
          break;
        }

        if (rightChild < heap.Size() && heap[i] < heap[rightChild])
        {
          isValidHeap = false;
          break;
        }
      }
    }

    std::cout << ((tst = (isValidHeap == heap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
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

void mytestHeapInt(uint &testnum, uint &testerr)
{
  uint loctestnum = 0, loctesterr = 0;
  std::cout << std::endl
            << "Begin of My Heap<int> Extended Test:" << std::endl;

  try
  {
    // Test constructors
    HeapConstructorWithSize<int>(loctestnum, loctesterr, 0);
    HeapConstructorWithSize<int>(loctestnum, loctesterr, 5);
    HeapFromEmptyContainer<int>(loctestnum, loctesterr);

    // Test empty heap operations
    HeapEmptyIsHeap<int>(loctestnum, loctesterr);
    HeapEmptyHeapify<int>(loctestnum, loctesterr);
    HeapEmptySort<int>(loctestnum, loctesterr);

    // Test single element operations
    HeapSingleElement<int>(loctestnum, loctesterr, 42);
    HeapSingleElementSort<int>(loctestnum, loctesterr, 42);
    HeapSingleElementRemove<int>(loctestnum, loctesterr, 42);

    // Test duplicate elements
    HeapAllDuplicates<int>(loctestnum, loctesterr, 100, 5);
    HeapDuplicatesSort<int>(loctestnum, loctesterr, 100, 5);

    // Test Insert operations
    lasd::HeapVec<int> testHeap;
    HeapInsert<int>(loctestnum, loctesterr, testHeap, 50);
    HeapInsert<int>(loctestnum, loctesterr, testHeap, 25);
    HeapInsert<int>(loctestnum, loctesterr, testHeap, 75);

    // Test RemoveRoot operations
    HeapRemoveRoot<int>(loctestnum, loctesterr, testHeap, true);
    HeapRemoveRoot<int>(loctestnum, loctesterr, testHeap, true);
    HeapRemoveRoot<int>(loctestnum, loctesterr, testHeap, true);

    // Test RemoveRoot on empty heap
    lasd::HeapVec<int> emptyHeap;
    HeapRemoveRoot<int>(loctestnum, loctesterr, emptyHeap, false);

    // Test Clear operation
    testHeap.Insert(99);
    testHeap.Insert(88);
    HeapClear<int>(loctestnum, loctesterr, testHeap);
    HeapAfterClear<int>(loctestnum, loctesterr, testHeap, 77);

    // Test sorted data scenarios
    lasd::Vector<int> ascendingData(5);
    ascendingData[0] = 1;
    ascendingData[1] = 2;
    ascendingData[2] = 3;
    ascendingData[3] = 4;
    ascendingData[4] = 5;
    HeapFromSortedAscending<int>(loctestnum, loctesterr, ascendingData);

    lasd::Vector<int> descendingData(5);
    descendingData[0] = 5;
    descendingData[1] = 4;
    descendingData[2] = 3;
    descendingData[3] = 2;
    descendingData[4] = 1;
    HeapFromSortedDescending<int>(loctestnum, loctesterr, descendingData);

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
    HeapStressInsertions<int>(loctestnum, loctesterr, stressData);
    HeapStressRemovals<int>(loctestnum, loctesterr, stressData);

    // Test property consistency
    lasd::HeapVec<int> consistencyHeap(stressData);
    HeapPropertyAfterHeapify<int>(loctestnum, loctesterr, consistencyHeap);
    HeapPropertyLostAfterSort<int>(loctestnum, loctesterr, consistencyHeap);
    HeapPropertyAfterHeapify<int>(loctestnum, loctesterr, consistencyHeap);

    // Deep verification and consistency checks
    DeepHeapVerification<int>(loctestnum, loctesterr, consistencyHeap);
    HeapSizeConsistency<int>(loctestnum, loctesterr, consistencyHeap, consistencyHeap.Size());
    HeapEmptyConsistency<int>(loctestnum, loctesterr, consistencyHeap, false);
  }
  catch (...)
  {
    loctestnum++;
    loctesterr++;
    std::cout << std::endl
              << "Unmanaged error in My Heap<int> Extended Test!" << std::endl;
  }

  std::cout << "End of My Heap<int> Extended Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void mytestHeapString(uint &testnum, uint &testerr)
{
  uint loctestnum = 0, loctesterr = 0;
  std::cout << std::endl
            << "Begin of My Heap<string> Extended Test:" << std::endl;

  try
  {
    // Test constructors
    HeapConstructorWithSize<std::string>(loctestnum, loctesterr, 3);
    HeapFromEmptyContainer<std::string>(loctestnum, loctesterr);

    // Test empty operations
    HeapEmptyIsHeap<std::string>(loctestnum, loctesterr);
    HeapEmptyHeapify<std::string>(loctestnum, loctesterr);
    HeapEmptySort<std::string>(loctestnum, loctesterr);

    // Test single element
    HeapSingleElement<std::string>(loctestnum, loctesterr, std::string("unique"));
    HeapSingleElementSort<std::string>(loctestnum, loctesterr, std::string("unique"));
    HeapSingleElementRemove<std::string>(loctestnum, loctesterr, std::string("unique"));

    // Test duplicates
    HeapAllDuplicates<std::string>(loctestnum, loctesterr, std::string("duplicate"), 4);
    HeapDuplicatesSort<std::string>(loctestnum, loctesterr, std::string("duplicate"), 4);

    // Test Insert operations
    lasd::HeapVec<std::string> strTestHeap;
    HeapInsert<std::string>(loctestnum, loctesterr, strTestHeap, std::string("medium"));
    HeapInsert<std::string>(loctestnum, loctesterr, strTestHeap, std::string("small"));
    HeapInsert<std::string>(loctestnum, loctesterr, strTestHeap, std::string("large"));

    // Test RemoveRoot operations
    HeapRemoveRoot<std::string>(loctestnum, loctesterr, strTestHeap, true);
    HeapRemoveRoot<std::string>(loctestnum, loctesterr, strTestHeap, true);

    // Test Clear operation
    strTestHeap.Insert(std::string("after_clear"));
    HeapClear<std::string>(loctestnum, loctesterr, strTestHeap);
    HeapAfterClear<std::string>(loctestnum, loctesterr, strTestHeap, std::string("new_value"));

    // Test sorted string data
    lasd::Vector<std::string> ascendingStrData(4);
    ascendingStrData[0] = std::string("alpha");
    ascendingStrData[1] = std::string("beta");
    ascendingStrData[2] = std::string("gamma");
    ascendingStrData[3] = std::string("omega");
    HeapFromSortedAscending<std::string>(loctestnum, loctesterr, ascendingStrData);

    lasd::Vector<std::string> descendingStrData(4);
    descendingStrData[0] = std::string("omega");
    descendingStrData[1] = std::string("gamma");
    descendingStrData[2] = std::string("beta");
    descendingStrData[3] = std::string("alpha");
    HeapFromSortedDescending<std::string>(loctestnum, loctesterr, descendingStrData);

    // Test stress operations with strings
    lasd::Vector<std::string> strStressData(6);
    strStressData[0] = std::string("zebra");
    strStressData[1] = std::string("apple");
    strStressData[2] = std::string("orange");
    strStressData[3] = std::string("banana");
    strStressData[4] = std::string("kiwi");
    strStressData[5] = std::string("mango");
    HeapStressInsertions<std::string>(loctestnum, loctesterr, strStressData);
    HeapStressRemovals<std::string>(loctestnum, loctesterr, strStressData);

    // Test property consistency
    lasd::HeapVec<std::string> strConsistencyHeap(strStressData);
    HeapPropertyAfterHeapify<std::string>(loctestnum, loctesterr, strConsistencyHeap);
    HeapPropertyLostAfterSort<std::string>(loctestnum, loctesterr, strConsistencyHeap);

    // Deep verification for strings
    DeepHeapVerification<std::string>(loctestnum, loctesterr, strConsistencyHeap);
  }
  catch (...)
  {
    loctestnum++;
    loctesterr++;
    std::cout << std::endl
              << "Unmanaged error in My Heap<string> Extended Test!" << std::endl;
  }

  std::cout << "End of My Heap<string> Extended Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << std::endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

#endif