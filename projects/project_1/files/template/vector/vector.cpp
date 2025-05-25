#include <stdexcept>

namespace lasd {

    /* ************************************************************************** */

    // Vector specific constructors

    template <typename Data>
    Vector<Data>::Vector(const ulong newSize) {
        size = newSize;
        elements = new Data[newSize]();  // Allocate array with default-initialized elements
    }

    template <typename Data>
    Vector<Data>::Vector(const TraversableContainer<Data>& traversableC) : Vector(traversableC.Size()) {
        ulong i = 0;
        traversableC.Traverse([this, &i](const Data& data) {
            elements[i] = data;  // Copy each element from the traversable container
            i++;
            });
    }

    template <typename Data>
    Vector<Data>::Vector(MappableContainer<Data>&& mappableC) noexcept : Vector(mappableC.Size()) {
        ulong i = 0;
        mappableC.Map([this, &i](Data& data) {
            elements[i] = std::move(data);  // Move each element from the mappable container
            i++;
            });
    }

    // Vector copy & move constructors

    template <typename Data>
    Vector<Data>::Vector(const Vector<Data>& vectorToCopy) {
        size = vectorToCopy.size;
        elements = new Data[size];  // Allocate new array
        for (ulong i = 0; i < size; i++) {
            elements[i] = vectorToCopy.elements[i];  // Copy each element
        }
    }

    template <typename Data>
    Vector<Data>::Vector(Vector<Data>&& vectorToMove) noexcept {
        std::swap(size, vectorToMove.size);  // Take ownership of other vector's resources
        std::swap(elements, vectorToMove.elements);
    }

    // Vector destructor

    template <typename Data>
    Vector<Data>::~Vector() {
        delete[] elements;  // Free the allocated array
    }

    // Vector copy & move assignments

    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vectorToAssign) {
        if (this != &vectorToAssign) {
            size = vectorToAssign.size;
            Data* newElements = new Data[size];  // Create new array
            for (ulong i = 0; i < size; i++) {
                newElements[i] = vectorToAssign.elements[i];  // Copy elements
            }
            delete[] elements;  // Free old array
            elements = newElements;  // Point to new array
        }
        return *this;
    }

    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vectorToAssign) noexcept {
        std::swap(size, vectorToAssign.size);  // Exchange resources with other vector
        std::swap(elements, vectorToAssign.elements);
        return *this;
    }

    // Vector comparison operators

    template <typename Data>
    bool Vector<Data>::operator==(const Vector<Data>& vectorToCompare) const noexcept {
        if (size != vectorToCompare.size) {
            return false;  // Different sizes means different vectors
        }

        for (ulong i = 0; i < size; i++) {
            if (elements[i] != vectorToCompare.elements[i]) {
                return false;  // Element mismatch
            }
        }

        return true;  // All elements match
    }

    template <typename Data>
    bool Vector<Data>::operator!=(const Vector<Data>& vectorToCompare) const noexcept {
        return !(*this == vectorToCompare);  // Use equality operator for inverse check
    }

    // Vector linear container methods (non-mutable)

    template <typename Data>
    const Data& Vector<Data>::operator[](const ulong index) const {
        if (index >= size) {
            throw std::out_of_range("Vector: Index out of range");
        }
        return elements[index];  // Return const reference to element at index
    }

    template <typename Data>
    const Data& Vector<Data>::Front() const {
        if (Empty()) {
            throw std::length_error("Vector: Empty container");
        }
        return elements[0];  // Return const reference to first element
    }

    template <typename Data>
    const Data& Vector<Data>::Back() const {
        if (Empty()) {
            throw std::length_error("Vector: Empty container");
        }
        return elements[size - 1];  // Return const reference to last element
    }

    // Vector mutable linear container methods

    template <typename Data>
    Data& Vector<Data>::operator[](const ulong index) {
        if (index >= size) {
            throw std::out_of_range("Vector: Index out of range");
        }
        return elements[index];  // Return mutable reference to element at index
    }

    template <typename Data>
    Data& Vector<Data>::Front() {
        if (Empty()) {
            throw std::length_error("Vector: Empty container");
        }
        return elements[0];  // Return mutable reference to first element
    }

    template <typename Data>
    Data& Vector<Data>::Back() {
        if (Empty()) {
            throw std::length_error("Vector: Empty container");
        }
        return elements[size - 1];  // Return mutable reference to last element
    }

    // Vector resizable methods

    template <typename Data>
    void Vector<Data>::Resize(const ulong newSize) {
        if (newSize == 0) {
            Clear();  // Special case: resize to 0 means clear
        }
        else if (size != newSize) {
            Data* newElements = new Data[newSize]();  // Allocate new array
            ulong minSize = (size < newSize) ? size : newSize;  // Determine how many elements to copy

            for (ulong i = 0; i < minSize; i++) {
                newElements[i] = std::move(elements[i]);  // Move existing elements to new array
            }

            delete[] elements;  // Free old array
            elements = newElements;  // Point to new array
            size = newSize;  // Update size
        }
    }

    // Vector clearable methods

    template <typename Data>
    void Vector<Data>::Clear() {
        delete[] elements;  // Free array
        elements = nullptr;
        size = 0;
    }

    /* ************************************************************************** */

    // SortableVector specific constructors

    template <typename Data>
    SortableVector<Data>::SortableVector(const ulong newSize) : Vector<Data>(newSize) {}

    template <typename Data>
    SortableVector<Data>::SortableVector(const TraversableContainer<Data>& traversableC) : Vector<Data>(traversableC) {}

    template <typename Data>
    SortableVector<Data>::SortableVector(MappableContainer<Data>&& mappableC) noexcept : Vector<Data>(std::move(mappableC)) {}

    // SortableVector copy & move constructors

    template <typename Data>
    SortableVector<Data>::SortableVector(const SortableVector<Data>& vectorToCopy) : Vector<Data>(vectorToCopy) {}

    template <typename Data>
    SortableVector<Data>::SortableVector(SortableVector<Data>&& vectorToMove) noexcept : Vector<Data>(std::move(vectorToMove)) {}

    // SortableVector copy & move assignments

    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& vectorToAssign) {
        Vector<Data>::operator=(vectorToAssign);  // Delegate to base class assignment
        return *this;
    }

    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& vectorToAssign) noexcept {
        Vector<Data>::operator=(std::move(vectorToAssign));  // Delegate to base class move assignment
        return *this;
    }

    // SortableVector sorting methods

    template <typename Data>
    void SortableVector<Data>::Sort() {
        if (size > 1) {
            InsertionSort(this->elements, size);  // Use insertion sort algorithm
        }
    }

    template <typename Data>
    void SortableVector<Data>::InsertionSort(Data* array, ulong length) {
        for (ulong i = 1; i < length; i++) {
            Data key = array[i];  // Element to be inserted in the right position
            ulong j = i;

            // Shift elements greater than key to the right
            while (j > 0 && array[j - 1] > key) {
                array[j] = array[j - 1];
                j--;
            }

            array[j] = key;  // Insert key at the correct position
        }
    }

    /* ************************************************************************** */

}