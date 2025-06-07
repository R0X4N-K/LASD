#include <iostream>

/* ************************************************************************** */

#include "container.hpp"

/* ************************************************************************** */

// Container member functions implementations
void ClearEffect(uint& testnum, uint& testerr, lasd::ClearableContainer& con, const std::string& message) {
  bool tst;
  ulong oldSize = con.Size();
  con.Clear();
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") " << message << ": ";
  std::cout << ((tst = (con.Empty() && con.Size() == 0)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
  
  if (tst) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Size changed from " << oldSize << " to 0 after Clear(): ";
    std::cout << "Correct!" << std::endl;
  } else {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Size changed from " << oldSize << " to 0 after Clear(): ";
    std::cout << "Error!" << std::endl;
    testerr++;
  }
}

void ResizeEffect(uint& testnum, uint& testerr, lasd::ResizableContainer& con, ulong newSize, const std::string& message) {
  bool tst;
  ulong oldSize = con.Size();
  con.Resize(newSize);
  testnum++;
  std::cout << " " << testnum << " (" << testerr << ") " << message << ": ";
  std::cout << ((tst = (con.Size() == newSize)) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
  
  if (newSize == 0) {
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Container is empty after Resize(0): ";
    std::cout << ((tst = con.Empty()) ? "Correct" : "Error") << "!" << std::endl;
    testerr += (1 - (uint)tst);
  }

  if (oldSize != newSize) {
    SizeTransition(testnum, testerr, con, oldSize, newSize, "Resize()");
  }
}

/* ************************************************************************** */