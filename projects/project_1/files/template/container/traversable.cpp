namespace lasd {

  /* ************************************************************************** */

  // TraversableContainer implementation

  template <typename Data>
  bool TraversableContainer<Data>::Exists(const Data& data) const noexcept {
    bool exists = false;

    Traverse([&exists, &data](const Data& currentData) {
      if (currentData == data) {
        exists = true;
      }
      });

    return exists;
  }

  /* ************************************************************************** */

  // PreOrderTraversableContainer implementation

  template <typename Data>
  void PreOrderTraversableContainer<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun fun) const {
    PreOrderTraverse(fun);
  }

  /* ************************************************************************** */

  // PostOrderTraversableContainer implementation

  template <typename Data>
  void PostOrderTraversableContainer<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun fun) const {
    PostOrderTraverse(fun);
  }

  /* ************************************************************************** */

  // Template functions implementation

  template <typename Data>
  template <typename Accumulator>
  Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const {
    Traverse([&accumulator, foldFun](const Data& data) {
      accumulator = foldFun(data, accumulator);
      });

    return accumulator;
  }

  template <typename Data>
  template <typename Accumulator>
  Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const {
    PreOrderTraverse([&accumulator, foldFun](const Data& data) {
      accumulator = foldFun(data, accumulator);
      });

    return accumulator;
  }

  template <typename Data>
  template <typename Accumulator>
  Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const {
    PostOrderTraverse([&accumulator, foldFun](const Data& data) {
      accumulator = foldFun(data, accumulator);
      });

    return accumulator;
  }

  /* ************************************************************************** */

}