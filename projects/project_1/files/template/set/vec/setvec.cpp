namespace lasd {

    /* ************************************************************************** */

    // Specific constructors

    template <typename Data>
    SetVec<Data>::SetVec(const TraversableContainer<Data>& container) {
        // Insert all elements from the container
        container.Traverse([this](const Data& data) {
            Insert(data);
            });
    }

    template <typename Data>
    SetVec<Data>::SetVec(MappableContainer<Data>&& container) noexcept {
        // Move all elements from the container
        container.Map([this](Data& data) {
            Insert(std::move(data));
            });
    }

    // Copy constructor
    template <typename Data>
    SetVec<Data>::SetVec(const SetVec<Data>& other) : Vector<Data>(other) {}

    // Move constructor
    template <typename Data>
    SetVec<Data>::SetVec(SetVec<Data>&& other) noexcept : Vector<Data>(std::move(other)) {}

    // Copy assignment
    template <typename Data>
    SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
        Vector<Data>::operator=(other);
        return *this;
    }

    // Move assignment
    template <typename Data>
    SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
        Vector<Data>::operator=(std::move(other));
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
        if (size != other.size) {
            return false;
        }

        // For sets, we need to check if each element exists in the other set
        for (ulong i = 0; i < size; i++) {
            if (!other.Exists(elements[i])) {
                return false;
            }
        }

        return true;
    }

    template <typename Data>
    bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
        return !(*this == other);
    }

    // Specific member functions (inherited from OrderedDictionaryContainer)

    template <typename Data>
    const Data& SetVec<Data>::Min() const {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        return Front();
    }

    template <typename Data>
    Data SetVec<Data>::MinNRemove() {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        Data min = Front();
        RemoveMin();
        return min;
    }

    template <typename Data>
    void SetVec<Data>::RemoveMin() {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        ShiftLeft(0);
    }

    template <typename Data>
    const Data& SetVec<Data>::Max() const {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        return Back();
    }

    template <typename Data>
    Data SetVec<Data>::MaxNRemove() {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        Data max = Back();
        RemoveMax();
        return max;
    }

    template <typename Data>
    void SetVec<Data>::RemoveMax() {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }
        Vector<Data>::Resize(size - 1);
    }

    template <typename Data>
    const Data& SetVec<Data>::Predecessor(const Data& data) const {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindPredecessorPos(data);
        if (pos < 0) {
            throw std::length_error("SetVec: Predecessor not found");
        }

        return elements[pos];
    }

    template <typename Data>
    Data SetVec<Data>::PredecessorNRemove(const Data& data) {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindPredecessorPos(data);
        if (pos < 0) {
            throw std::length_error("SetVec: Predecessor not found");
        }

        Data pred = elements[pos];
        ShiftLeft(pos);
        return pred;
    }

    template <typename Data>
    void SetVec<Data>::RemovePredecessor(const Data& data) {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindPredecessorPos(data);
        if (pos < 0) {
            throw std::length_error("SetVec: Predecessor not found");
        }

        ShiftLeft(pos);
    }

    template <typename Data>
    const Data& SetVec<Data>::Successor(const Data& data) const {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindSuccessorPos(data);
        if (pos < 0 || pos >= size) {
            throw std::length_error("SetVec: Successor not found");
        }

        return elements[pos];
    }

    template <typename Data>
    Data SetVec<Data>::SuccessorNRemove(const Data& data) {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindSuccessorPos(data);
        if (pos < 0 || pos >= size) {
            throw std::length_error("SetVec: Successor not found");
        }

        Data succ = elements[pos];
        ShiftLeft(pos);
        return succ;
    }

    template <typename Data>
    void SetVec<Data>::RemoveSuccessor(const Data& data) {
        if (this->Empty()) {
            throw std::length_error("SetVec: Empty container");
        }

        long pos = FindSuccessorPos(data);
        if (pos < 0 || pos >= size) {
            throw std::length_error("SetVec: Successor not found");
        }

        ShiftLeft(pos);
    }

    // Specific member functions (inherited from DictionaryContainer)

    template <typename Data>
    bool SetVec<Data>::Insert(const Data& data) {
        // Binary search to find position or check existence
        ulong pos = BinarySearch(data);

        // If the element is found, return false (no duplicate allowed)
        if (pos < size && elements[pos] == data) {
            return false;
        }

        // Insert the element at the correct position
        if (this->Empty()) {
            Vector<Data>::Resize(1);
            elements[0] = data;
        }
        else {
            Vector<Data>::Resize(size + 1);
            // Shift elements to make space for the new element
            ShiftRight(pos);
            elements[pos] = data;
        }
        return true;
    }

    template <typename Data>
    bool SetVec<Data>::Insert(Data&& data) {
        // Binary search to find position or check existence
        ulong pos = BinarySearch(data);

        // If the element is found, return false (no duplicate allowed)
        if (pos < size && elements[pos] == data) {
            return false;
        }

        // Insert the element at the correct position
        if (this->Empty()) {
            Vector<Data>::Resize(1);
            elements[0] = std::move(data);
        }
        else {
            Vector<Data>::Resize(size + 1);
            // Shift elements to make space for the new element
            ShiftRight(pos);
            elements[pos] = std::move(data);
        }
        return true;
    }

    template <typename Data>
    bool SetVec<Data>::Remove(const Data& data) {
        // Binary search to find the element
        ulong pos = BinarySearch(data);

        // If the element is not found, return false
        if (pos >= size || elements[pos] != data) {
            return false;
        }

        // Remove the element by shifting left
        ShiftLeft(pos);
        return true;
    }

    // Specific member function (inherited from TestableContainer)

    template <typename Data>
    bool SetVec<Data>::Exists(const Data& data) const noexcept {
        if (this->Empty()) {
            return false;
        }

        // Binary search to check if the element exists
        ulong pos = BinarySearch(data);
        return (pos < size && elements[pos] == data);
    }

    template <typename Data>
    void SetVec<Data>::Clear() {
        Vector<Data>::Clear();
    }

    // Protected auxiliary functions

    template <typename Data>
    ulong SetVec<Data>::BinarySearch(const Data& data) const {
        if (this->Empty()) {
            return 0;
        }

        long left = 0;
        long right = size - 1;

        while (left <= right) {
            long mid = left + (right - left) / 2;

            if (elements[mid] == data) {
                return mid;
            }
            else if (elements[mid] < data) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return left; // Return insertion point if not found
    }

    template <typename Data>
    long SetVec<Data>::FindPredecessorPos(const Data& data) const {
        if (this->Empty() || data <= Min()) {
            return -1; // No predecessor if empty or if data is the minimum
        }

        ulong pos = BinarySearch(data);

        // If the exact element is found
        if (pos < size && elements[pos] == data) {
            if (pos > 0) {
                return pos - 1; // The predecessor is the element before
            }
            else {
                return -1; // No predecessor if it's the first element
            }
        }

        // If the element is not found
        if (pos > 0) {
            return pos - 1; // The predecessor is the element before the insertion point
        }

        return -1; // No predecessor found
    }

    template <typename Data>
    long SetVec<Data>::FindSuccessorPos(const Data& data) const {
        if (this->Empty() || data >= Max()) {
            return -1; // No successor if empty or if data is the maximum
        }

        ulong pos = BinarySearch(data);

        // If the exact element is found
        if (pos < size && elements[pos] == data) {
            if (pos < size - 1) {
                return pos + 1; // The successor is the element after
            }
            else {
                return -1; // No successor if it's the last element
            }
        }

        // If the element is not found, the insertion point is the successor
        if (pos < size) {
            return pos;
        }

        return -1; // No successor found
    }

    template <typename Data>
    void SetVec<Data>::ShiftRight(ulong pos) {
        for (ulong i = size - 1; i > pos; i--) {
            elements[i] = std::move(elements[i - 1]);
        }
    }

    template <typename Data>
    void SetVec<Data>::ShiftLeft(ulong pos) {
        for (ulong i = pos; i < size - 1; i++) {
            elements[i] = std::move(elements[i + 1]);
        }
        Vector<Data>::Resize(size - 1);
    }

    template <typename Data>
    void SetVec<Data>::Sort() {
        // Insertion sort algorithm
        for (ulong i = 1; i < size; i++) {
            Data key = std::move(elements[i]);
            long j = i - 1;

            while (j >= 0 && elements[j] > key) {
                elements[j + 1] = std::move(elements[j]);
                j--;
            }

            elements[j + 1] = std::move(key);
        }
    }

    /* ************************************************************************** */

}