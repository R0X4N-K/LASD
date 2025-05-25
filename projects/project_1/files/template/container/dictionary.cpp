namespace lasd {

  /* ************************************************************************** */

  // DictionaryContainer implementation

  template <typename Data>
  bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& container) {
    bool allInserted = true;  // Track if all elements were successfully inserted

    container.Traverse([this, &allInserted](const Data& data) {
      allInserted &= Insert(data);  // Logical AND assignment preserves false if any insert fails
      });

    return allInserted;
  }

  template <typename Data>
  bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& container) {
    bool allInserted = true;  // Track if all elements were successfully inserted

    container.Map([this, &allInserted](Data& data) {
      allInserted &= Insert(std::move(data));  // Move semantics for efficient insertion
      });

    return allInserted;
  }

  template <typename Data>
  bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& container) {
    bool allRemoved = true;  // Track if all elements were successfully removed

    container.Traverse([this, &allRemoved](const Data& data) {
      allRemoved &= Remove(data);  // Logical AND assignment preserves false if any removal fails
      });

    return allRemoved;
  }

  template <typename Data>
  bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& container) {
    bool someInserted = false;  // Track if at least one element was inserted

    container.Traverse([this, &someInserted](const Data& data) {
      someInserted |= Insert(data);  // Logical OR assignment becomes true if any insert succeeds
      });

    return someInserted;
  }

  template <typename Data>
  bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& container) {
    bool someInserted = false;  // Track if at least one element was inserted

    container.Map([this, &someInserted](Data& data) {
      someInserted |= Insert(std::move(data));  // Move semantics with OR assignment
      });

    return someInserted;
  }

  template <typename Data>
  bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& container) {
    bool someRemoved = false;  // Track if at least one element was removed

    container.Traverse([this, &someRemoved](const Data& data) {
      someRemoved |= Remove(data);  // Logical OR assignment becomes true if any removal succeeds
      });

    return someRemoved;
  }

  /* ************************************************************************** */

  // OrderedDictionaryContainer doesn't need implementation in .cpp because
  // all its methods are pure virtual (abstract) and will be implemented by derived classes

  /* ************************************************************************** */

}