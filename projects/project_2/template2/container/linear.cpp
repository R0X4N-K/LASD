namespace lasd
{

  /* ************************************************************************** */

  // LinearContainer

  template <typename Data>
  void LinearContainer<Data>::Traverse(TraverseFun fun) const
  {
    PreOrderTraverse(fun); // Default traversal is equivalent to pre-order traversal
  }

  template <typename Data>
  void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const
  {
    for (ulong i = 0; i < this->Size(); i++)
    {
      fun(operator[](i)); // Applies function to elements from first to last (index 0 to size-1)
    }
  }

  template <typename Data>
  void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const
  {
    ulong size = this->Size();
    for (ulong i = 0; i < size; i++)
    {
      fun(operator[](size - 1 - i)); // Applies function to elements from last to first (index size-1 to 0)
    }
  }

  // Comparison operators implementation
  template <typename Data>
  bool LinearContainer<Data>::operator==(const LinearContainer &other) const noexcept
  {
    if (this->Size() != other.Size())
    {
      return false; // Containers with different sizes cannot be equal
    }

    for (ulong i = 0; i < this->Size(); i++)
    {
      if (operator[](i) != other[i])
      {
        return false; // If any element differs, containers are not equal
      }
    }

    return true; // All elements are equal and sizes match
  }

  template <typename Data>
  bool LinearContainer<Data>::operator!=(const LinearContainer &other) const noexcept
  {
    return !(*this == other); // Leverages equality operator for inequality check
  }

  // MutableLinearContainer

  template <typename Data>
  void MutableLinearContainer<Data>::Map(MapFun fun)
  {
    PreOrderMap(fun); // Default mapping is equivalent to pre-order mapping
  }

  template <typename Data>
  void MutableLinearContainer<Data>::PreOrderMap(MapFun fun)
  {
    for (ulong i = 0; i < this->Size(); i++)
    {
      fun(operator[](i)); // Applies function to elements from first to last (index 0 to size-1)
    }
  }

  template <typename Data>
  void MutableLinearContainer<Data>::PostOrderMap(MapFun fun)
  {
    ulong size = this->Size();
    for (ulong i = 0; i < size; i++)
    {
      fun(operator[](size - 1 - i)); // Applies function to elements from last to first (index size-1 to 0)
    }
  }

  /* ************************************************************************** */

}