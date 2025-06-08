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

template <typename Data>
void HeapFromTraversableContainer(uint &testnum, uint &testerr, const lasd::Vector<Data> &data)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap from TraversableContainer maintains heap property: ";
    lasd::HeapVec<Data> heap(data);
    std::cout << ((tst = (heap.Size() == data.Size() && heap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapSortPreservesElements(uint &testnum, uint &testerr, const lasd::Vector<Data> &originalData)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Sort preserves all elements: ";
    lasd::HeapVec<Data> heap(originalData);
    heap.Sort();

    bool allElementsPresent = true;
    for (ulong i = 0; i < originalData.Size(); ++i)
    {
      bool found = false;
      for (ulong j = 0; j < heap.Size(); ++j)
      {
        if (heap[j] == originalData[i])
        {
          found = true;
          break;
        }
      }
      if (!found)
      {
        allElementsPresent = false;
        break;
      }
    }

    std::cout << ((tst = (allElementsPresent && heap.Size() == originalData.Size())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapCopyConstructor(uint &testnum, uint &testerr, const lasd::Vector<Data> &data)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap copy constructor maintains heap property: ";
    lasd::HeapVec<Data> originalHeap(data);
    lasd::HeapVec<Data> copiedHeap(originalHeap);
    std::cout << ((tst = (copiedHeap.Size() == originalHeap.Size() && copiedHeap.IsHeap() && originalHeap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception &exc)
  {
    tst = false;
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
  }
  testerr += (1 - (uint)tst);
}

template <typename Data>
void HeapMoveConstructor(uint &testnum, uint &testerr, const lasd::Vector<Data> &data)
{
  bool tst;
  testnum++;
  try
  {
    std::cout << " " << testnum << " (" << testerr << ") Heap move constructor maintains heap property: ";
    lasd::HeapVec<Data> originalHeap(data);
    ulong originalSize = originalHeap.Size();
    lasd::HeapVec<Data> movedHeap(std::move(originalHeap));
    std::cout << ((tst = (movedHeap.Size() == originalSize && movedHeap.IsHeap())) ? "Correct" : "Error") << "!" << std::endl;
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

    // Test duplicate elements
    HeapAllDuplicates<int>(loctestnum, loctesterr, 100, 5);
    HeapDuplicatesSort<int>(loctestnum, loctesterr, 100, 5);

    // Test sorted data scenarios
    lasd::Vector<int> ascendingData(5);
    ascendingData[0] = 1;
    ascendingData[1] = 2;
    ascendingData[2] = 3;
    ascendingData[3] = 4;
    ascendingData[4] = 5;
    HeapFromSortedAscending<int>(loctestnum, loctesterr, ascendingData);
    HeapFromTraversableContainer<int>(loctestnum, loctesterr, ascendingData);

    lasd::Vector<int> descendingData(5);
    descendingData[0] = 5;
    descendingData[1] = 4;
    descendingData[2] = 3;
    descendingData[3] = 2;
    descendingData[4] = 1;
    HeapFromSortedDescending<int>(loctestnum, loctesterr, descendingData);

    // Test mixed data scenarios
    lasd::Vector<int> mixedData(8);
    mixedData[0] = 15;
    mixedData[1] = 8;
    mixedData[2] = 22;
    mixedData[3] = 3;
    mixedData[4] = 11;
    mixedData[5] = 27;
    mixedData[6] = 6;
    mixedData[7] = 19;

    // Test property consistency
    lasd::HeapVec<int> consistencyHeap(mixedData);
    HeapPropertyAfterHeapify<int>(loctestnum, loctesterr, consistencyHeap);
    HeapPropertyLostAfterSort<int>(loctestnum, loctesterr, consistencyHeap);
    HeapPropertyAfterHeapify<int>(loctestnum, loctesterr, consistencyHeap);

    // Test sort preserves elements
    HeapSortPreservesElements<int>(loctestnum, loctesterr, mixedData);

    // Test copy and move constructors
    HeapCopyConstructor<int>(loctestnum, loctesterr, mixedData);
    HeapMoveConstructor<int>(loctestnum, loctesterr, mixedData);

    // Deep verification and consistency checks
    lasd::HeapVec<int> verificationHeap(mixedData);
    DeepHeapVerification<int>(loctestnum, loctesterr, verificationHeap);
    HeapSizeConsistency<int>(loctestnum, loctesterr, verificationHeap, verificationHeap.Size());
    HeapEmptyConsistency<int>(loctestnum, loctesterr, verificationHeap, false);

    // Test Clear operation
    HeapClear<int>(loctestnum, loctesterr, verificationHeap);
    HeapEmptyConsistency<int>(loctestnum, loctesterr, verificationHeap, true);
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

    // Test duplicates
    HeapAllDuplicates<std::string>(loctestnum, loctesterr, std::string("duplicate"), 4);
    HeapDuplicatesSort<std::string>(loctestnum, loctesterr, std::string("duplicate"), 4);

    // Test sorted string data
    lasd::Vector<std::string> ascendingStrData(4);
    ascendingStrData[0] = std::string("alpha");
    ascendingStrData[1] = std::string("beta");
    ascendingStrData[2] = std::string("gamma");
    ascendingStrData[3] = std::string("omega");
    HeapFromSortedAscending<std::string>(loctestnum, loctesterr, ascendingStrData);
    HeapFromTraversableContainer<std::string>(loctestnum, loctesterr, ascendingStrData);

    lasd::Vector<std::string> descendingStrData(4);
    descendingStrData[0] = std::string("omega");
    descendingStrData[1] = std::string("gamma");
    descendingStrData[2] = std::string("beta");
    descendingStrData[3] = std::string("alpha");
    HeapFromSortedDescending<std::string>(loctestnum, loctesterr, descendingStrData);

    // Test mixed string data
    lasd::Vector<std::string> mixedStrData(6);
    mixedStrData[0] = std::string("zebra");
    mixedStrData[1] = std::string("apple");
    mixedStrData[2] = std::string("orange");
    mixedStrData[3] = std::string("banana");
    mixedStrData[4] = std::string("kiwi");
    mixedStrData[5] = std::string("mango");

    // Test property consistency
    lasd::HeapVec<std::string> strConsistencyHeap(mixedStrData);
    HeapPropertyAfterHeapify<std::string>(loctestnum, loctesterr, strConsistencyHeap);
    HeapPropertyLostAfterSort<std::string>(loctestnum, loctesterr, strConsistencyHeap);

    // Test sort preserves elements
    HeapSortPreservesElements<std::string>(loctestnum, loctesterr, mixedStrData);

    // Test copy and move constructors
    HeapCopyConstructor<std::string>(loctestnum, loctesterr, mixedStrData);
    HeapMoveConstructor<std::string>(loctestnum, loctesterr, mixedStrData);

    // Deep verification for strings
    lasd::HeapVec<std::string> strVerificationHeap(mixedStrData);
    DeepHeapVerification<std::string>(loctestnum, loctesterr, strVerificationHeap);
    HeapSizeConsistency<std::string>(loctestnum, loctesterr, strVerificationHeap, strVerificationHeap.Size());

    // Test Clear operation
    HeapClear<std::string>(loctestnum, loctesterr, strVerificationHeap);
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
