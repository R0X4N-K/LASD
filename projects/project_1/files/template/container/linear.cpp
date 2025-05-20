namespace lasd {

  /* ************************************************************************** */

  // LinearContainer

  template <typename Data>
  void LinearContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
  }

  template <typename Data>
  void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
    for (ulong i = 0; i < this->Size(); i++) {
      fun(operator[](i));
    }
  }

  template <typename Data>
  void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
    ulong size = this->Size();
    for (ulong i = 0; i < size; i++) {
      fun(operator[](size - 1 - i));
    }
  }

  // MutableLinearContainer

  template <typename Data>
  void MutableLinearContainer<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
  }

  template <typename Data>
  void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
    for (ulong i = 0; i < this->Size(); i++) {
      fun(operator[](i));
    }
  }

  template <typename Data>
  void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
    ulong size = this->Size();
    for (ulong i = 0; i < size; i++) {
      fun(operator[](size - 1 - i));
    }
  }

  /* ************************************************************************** */

}