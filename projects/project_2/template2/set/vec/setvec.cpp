namespace lasd {

    /* ************************************************************************** */

    // Specific constructors

    template <typename Data>
    SetVec<Data>::SetVec(const TraversableContainer<Data>& container) {
        // Insert all elements from the container
        container.Traverse([this](const Data& data) {
            Insert(data);  // Using Insert ensures no duplicates are added
            });
    }

    template <typename Data>
    SetVec<Data>::SetVec(MappableContainer<Data>&& container) noexcept {
        // Move all elements from the container
        container.Map([this](Data& data) {
            Insert(std::move(data));  // Move elements to avoid unnecessary copies
            });
    }

    // Copy constructor
    template <typename Data>
    SetVec<Data>::SetVec(const SetVec<Data>& other) : Vector<Data>(other) {}  // Leverage Vector's copy constructor

    // Move constructor
    template <typename Data>
    SetVec<Data>::SetVec(SetVec<Data>&& other) noexcept : Vector<Data>(std::move(other)) {}  // Leverage Vector's move constructor

    // Copy assignment
    template <typename Data>
    SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
        Vector<Data>::operator=(other);  // Delegate to Vector's copy assignment
        return *this;
    }

    // Move assignment
    template <typename Data>
    SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
        Vector<Data>::operator=(std::move(other));  // Delegate to Vector's move assignment
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
        if (size != other.size) {
            return false;  // Sets of different sizes cannot be equal
        }

        // For sets, we need to check if each element exists in the other set
        for (ulong i = 0; i < size; i++) {
            if (!other.Exists(elements[i])) {
                return false;  // Element not found in other set
            }
        }

        return true;  // All elements match
    }

    template <typename Data>
    bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
        return !(*this == other);  // Use equality operator for inverse check
    }

    // Specific member functions (inherited from OrderedDictionaryContainer)

    template <typename Data>
    const Data& SetVec<Data>::Min() const {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        return Front();  // In a sorted set, front element is the minimum
    }

    template <typename Data>
    Data SetVec<Data>::MinNRemove() {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        Data min = Front();  // Save minimum value
        RemoveMin();  // Remove it
        return min;  // Return saved value
    }

    template <typename Data>
    void SetVec<Data>::RemoveMin() {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        ShiftLeft(0);  // Remove first element by shifting all elements left
    }

    template <typename Data>
    const Data& SetVec<Data>::Max() const {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        return Back();  // In a sorted set, back element is the maximum
    }

    template <typename Data>
    Data SetVec<Data>::MaxNRemove() {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        Data max = Back();  // Save maximum value
        RemoveMax();  // Remove it
        return max;  // Return saved value
    }

    template <typename Data>
    void SetVec<Data>::RemoveMax() {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        Vector<Data>::Resize(size - 1);  // Last element can be removed by simply resizing
    }

    template <typename Data>
    const Data& SetVec<Data>::Predecessor(const Data& data) const {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindPredecessorPos(data);  // Find position of predecessor
        if (pos < 0) {
            throw std::length_error("SetVec: Predecessor not found");
        }

        return elements[pos];  // Return predecessor element
    }

    template <typename Data>
    Data SetVec<Data>::PredecessorNRemove(const Data& data) {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindPredecessorPos(data);  // Find position of predecessor
        if (pos < 0) {
            throw std::length_error("SetVec: Predecessor not found");
        }

        Data pred = elements[pos];  // Save predecessor value
        ShiftLeft(pos);  // Remove predecessor by shifting elements
        return pred;  // Return saved value
    }

    template <typename Data>
    void SetVec<Data>::RemovePredecessor(const Data& data) {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindPredecessorPos(data);  // Find position of predecessor
        if (pos < 0) {
            throw std::length_error("SetVec: Predecessor not found");
        }

        ShiftLeft(pos);  // Remove predecessor by shifting elements
    }

    template <typename Data>
    const Data& SetVec<Data>::Successor(const Data& data) const {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindSuccessorPos(data);  // Find position of successor
        if (pos < 0 || static_cast<ulong>(pos) >= size) {
            throw std::length_error("SetVec: Successor not found");
        }

        return elements[pos];  // Return successor element
    }

    template <typename Data>
    Data SetVec<Data>::SuccessorNRemove(const Data& data) {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindSuccessorPos(data);  // Find position of successor
        if (pos < 0 || static_cast<ulong>(pos) >= size) {
            throw std::length_error("SetVec: Successor not found");
        }

        Data succ = elements[pos];  // Save successor value
        ShiftLeft(pos);  // Remove successor by shifting elements
        return succ;  // Return saved value
    }

    template <typename Data>
    void SetVec<Data>::RemoveSuccessor(const Data& data) {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindSuccessorPos(data);  // Find position of successor
        if (pos < 0 || static_cast<ulong>(pos) >= size) {
            throw std::length_error("SetVec: Successor not found");
        }

        ShiftLeft(pos);  // Remove successor by shifting elements
    }

    // Specific member functions (inherited from DictionaryContainer)

    template <typename Data>
    bool SetVec<Data>::Insert(const Data& data) {
        // Binary search to find position or check existence
        ulong pos = BinarySearch(data);

        // If the element is found, return false (no duplicate allowed)
        if (static_cast<ulong>(pos) < size && elements[pos] == data) {
            return false;  // Element already exists
        }

        // Insert the element at the correct position
        if (this->Empty()) {
            Vector<Data>::Resize(1);  // Resize to accommodate first element
            elements[0] = data;  // Insert element
        }
        else {
            Vector<Data>::Resize(size + 1);  // Resize to accommodate new element
            // Shift elements to make space for the new element
            ShiftRight(pos);
            elements[pos] = data;  // Insert element at correct position
        }
        return true;  // Element successfully inserted
    }

    template <typename Data>
    bool SetVec<Data>::Insert(Data&& data) {
        // Binary search to find position or check existence
        ulong pos = BinarySearch(data);

        // If the element is found, return false (no duplicate allowed)
        if (static_cast<ulong>(pos) < size && elements[pos] == data) {
            return false;  // Element already exists
        }

        // Insert the element at the correct position
        if (this->Empty()) {
            Vector<Data>::Resize(1);  // Resize to accommodate first element
            elements[0] = std::move(data);  // Move element into place
        }
        else {
            Vector<Data>::Resize(size + 1);  // Resize to accommodate new element
            // Shift elements to make space for the new element
            ShiftRight(pos);
            elements[pos] = std::move(data);  // Move element into correct position
        }
        return true;  // Element successfully inserted
    }

    template <typename Data>
    bool SetVec<Data>::Remove(const Data& data) {
        // Binary search to find the element
        ulong pos = BinarySearch(data);

        // If the element is not found, return false
        if (static_cast<ulong>(pos) >= size || elements[pos] != data) {
            return false;  // Element not found
        }

        // Remove the element by shifting left
        ShiftLeft(pos);
        return true;  // Element successfully removed
    }

    // Specific member function (inherited from TestableContainer)

    template <typename Data>
    bool SetVec<Data>::Exists(const Data& data) const noexcept {
        if (this->Empty()) {
            return false;  // Empty set contains no elements
        }

        // Binary search to check if the element exists
        ulong pos = BinarySearch(data);
        return (static_cast<ulong>(pos) < size && elements[pos] == data);  // Check if element found
    }

    template <typename Data>
    void SetVec<Data>::Clear() {
        Vector<Data>::Clear();  // Delegate to Vector's Clear method
    }

    // Protected auxiliary functions

    template <typename Data>
    ulong SetVec<Data>::BinarySearch(const Data& data) const {
        if (this->Empty()) {
            return 0;  // Empty vector - insertion point is at beginning
        }

        long left = 0;
        long right = size - 1;

        while (left <= right) {
            long mid = left + (right - left) / 2;  // Calculate middle index (avoids overflow)

            if (elements[mid] == data) {
                return mid;  // Element found
            }
            else if (elements[mid] < data) {
                left = mid + 1;  // Search right half
            }
            else {
                right = mid - 1;  // Search left half
            }
        }

        return left;  // Return insertion point if not found
    }

    template <typename Data>
    long SetVec<Data>::FindPredecessorPos(const Data& data) const {
        if (this->Empty() || data <= Min()) {
            return -1;  // No predecessor if empty or if data is the minimum
        }

        ulong pos = BinarySearch(data);  // Find position of element or insertion point

        // If the exact element is found
        if (static_cast<ulong>(pos) < size && elements[pos] == data) {
            if (pos > 0) {
                return pos - 1;  // The predecessor is the element before
            }
            else {
                return -1;  // No predecessor if it's the first element
            }
        }

        // If the element is not found
        if (pos > 0) {
            return pos - 1;  // The predecessor is the element before the insertion point
        }

        return -1;  // No predecessor found
    }

    template <typename Data>
    long SetVec<Data>::FindSuccessorPos(const Data& data) const {
        if (this->Empty() || data >= Max()) {
            return -1;  // No successor if empty or if data is the maximum
        }

        ulong pos = BinarySearch(data);  // Find position of element or insertion point

        // If the exact element is found
        if (static_cast<ulong>(pos) < size && elements[pos] == data) {
            if (static_cast<ulong>(pos) < size - 1) {
                return pos + 1;  // The successor is the element after
            }
            else {
                return -1;  // No successor if it's the last element
            }
        }

        // If the element is not found, the insertion point is the successor
        if (static_cast<ulong>(pos) < size) {
            return pos;  // The insertion point is the successor
        }

        return -1;  // No successor found
    }

    template <typename Data>
    void SetVec<Data>::ShiftRight(ulong pos) {
        for (ulong i = size - 1; i > pos; i--) {
            elements[i] = std::move(elements[i - 1]);  // Shift elements right starting from the end
        }
    }

    template <typename Data>
    void SetVec<Data>::ShiftLeft(ulong pos) {
        for (ulong i = pos; i < size - 1; i++) {
            elements[i] = std::move(elements[i + 1]);  // Shift elements left to overwrite removed element
        }
        Vector<Data>::Resize(size - 1);  // Resize to remove last element
    }

    template <typename Data>
    void SetVec<Data>::Sort() {
        // Insertion sort algorithm
        for (ulong i = 1; i < size; i++) {
            Data key = std::move(elements[i]);  // Element to be inserted in sorted position
            long j = i - 1;

            // Shift elements greater than key to the right
            while (j >= 0 && elements[j] > key) {
                elements[j + 1] = std::move(elements[j]);
                j--;
            }

            elements[j + 1] = std::move(key);  // Insert key at correct position
        }
    }

    /* ************************************************************************** */

}