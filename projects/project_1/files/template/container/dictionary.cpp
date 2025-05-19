namespace lasd {

/* ************************************************************************** */

// DictionaryContainer implementation

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& container) {
  bool allInserted = true;
  
  container.Traverse([this, &allInserted](const Data& data) {
    allInserted &= Insert(data);
  });
  
  return allInserted;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& container) {
  bool allInserted = true;
  
  container.Map([this, &allInserted](Data& data) {
    allInserted &= Insert(std::move(data));
  });
  
  return allInserted;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& container) {
  bool allRemoved = true;
  
  container.Traverse([this, &allRemoved](const Data& data) {
    allRemoved &= Remove(data);
  });
  
  return allRemoved;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& container) {
  bool someInserted = false;
  
  container.Traverse([this, &someInserted](const Data& data) {
    someInserted |= Insert(data);
  });
  
  return someInserted;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& container) {
  bool someInserted = false;
  
  container.Map([this, &someInserted](Data& data) {
    someInserted |= Insert(std::move(data));
  });
  
  return someInserted;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& container) {
  bool someRemoved = false;
  
  container.Traverse([this, &someRemoved](const Data& data) {
    someRemoved |= Remove(data);
  });
  
  return someRemoved;
}

/* ************************************************************************** */

// OrderedDictionaryContainer doesn't need implementation in .cpp because
// all its methods are pure virtual (abstract) and will be implemented by derived classes

/* ************************************************************************** */

}