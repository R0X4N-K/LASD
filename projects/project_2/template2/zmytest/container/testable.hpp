#ifndef MYTESTABLETEST_HPP
#define MYTESTABLETEST_HPP

#include "../../container/testable.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

// Extended TestableContainer member functions tests

// Test Exists with extreme values (min, max in container)
template <typename Data>
void ExistsExtreme(uint &testnum, uint &testerr, const lasd::TestableContainer<Data> &con,
                   const Data &minVal, const Data &maxVal)
{
  bool tstMin, tstMax;

  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Extreme value test - Minimum value \"" << minVal << "\" "
            << ((tstMin = con.Exists(minVal)) ? "does" : "does not") << " exist: ";
  std::cout << ((tstMin) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tstMin);

  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Extreme value test - Maximum value \"" << maxVal << "\" "
            << ((tstMax = con.Exists(maxVal)) ? "does" : "does not") << " exist: ";
  std::cout << ((tstMax) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tstMax);
}

// Test Exists on an empty container
template <typename Data>
void ExistsOnEmpty(uint &testnum, uint &testerr, const lasd::TestableContainer<Data> &con, const Data &val)
{
  bool tst;
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Empty container test - Value \"" << val << "\" should not exist: ";
  std::cout << ((tst = (!con.Exists(val))) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

// Test Exists with specific values
template <typename Data>
void ExistsEdgeCase(uint &testnum, uint &testerr, const lasd::TestableContainer<Data> &con,
                    bool expected, const Data &val, const std::string &description)
{
  bool tst;
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Edge case: " << description << " - Value \"" << val << "\" "
            << ((tst = con.Exists(val)) ? "does" : "does not") << " exist: ";
  std::cout << ((tst == expected) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)(tst == expected));
}

// Test Exists before and after modification operations
template <typename Data>
void ExistsBeforeAfterOperation(uint &testnum, uint &testerr,
                                lasd::TestableContainer<Data> &con,
                                const Data &val,
                                const std::string &operation,
                                std::function<void()> operationFn,
                                bool shouldExistBefore,
                                bool shouldExistAfter)
{
  bool beforeTest, afterTest;

  // Test before operation
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Before " << operation << " - Value \"" << val << "\" "
            << ((beforeTest = con.Exists(val)) ? "does" : "does not") << " exist: ";
  std::cout << ((beforeTest == shouldExistBefore) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (beforeTest != shouldExistBefore);

  // Perform the operation
  operationFn();

  // Test after operation
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") After " << operation << " - Value \"" << val << "\" "
            << ((afterTest = con.Exists(val)) ? "does" : "does not") << " exist: ";
  std::cout << ((afterTest == shouldExistAfter) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (afterTest != shouldExistAfter);
}

// Test Exists behavior with duplicate values
template <typename Data>
void ExistsDuplicates(uint &testnum, uint &testerr, const lasd::TestableContainer<Data> &con,
                      const Data &val, int expectedOccurrences)
{
  bool tst;
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Duplicate value test - Value \"" << val << "\" with "
            << expectedOccurrences << " occurrences "
            << ((tst = con.Exists(val)) ? "does" : "does not") << " exist: ";
  std::cout << ((tst) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

// Test Exists with boundary values (just outside what's in the container)
template <typename Data>
void ExistsBoundary(uint &testnum, uint &testerr, const lasd::TestableContainer<Data> &con,
                    const Data &justBeforeMin, const Data &justAfterMax)
{
  bool tstBefore, tstAfter;

  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Boundary test - Value just before minimum \"" << justBeforeMin << "\" "
            << ((tstBefore = con.Exists(justBeforeMin)) ? "does" : "does not") << " exist: ";
  std::cout << ((!tstBefore) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (uint)tstBefore;

  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") Boundary test - Value just after maximum \"" << justAfterMax << "\" "
            << ((tstAfter = con.Exists(justAfterMax)) ? "does" : "does not") << " exist: ";
  std::cout << ((!tstAfter) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (uint)tstAfter;
}

/* ************************************************************************** */

#endif