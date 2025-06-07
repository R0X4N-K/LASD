#ifndef MYCONTAINERTEST_HPP
#define MYCONTAINERTEST_HPP

#include "../../container/container.hpp"

/* ************************************************************************** */

// Container member functions tests

// Test ClearableContainer Clear() functionality
void ClearEffect(uint& testnum, uint& testerr, lasd::ClearableContainer& con, const std::string& message);

// Test ResizableContainer Resize() functionality
void ResizeEffect(uint& testnum, uint& testerr, lasd::ResizableContainer& con, ulong newSize, const std::string& message);

/* ************************************************************************** */

#endif