namespace lasd {

/* ************************************************************************** */

// TraversableContainer implementation

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data& data) const noexcept {
  bool exists = false;
  
  TraverseFun existsLambda = [&exists, &data](const Data& currentData) {
    if (currentData == data) {
      exists = true;
    }
  };
  
  Traverse(existsLambda);
  return exists;
}

/* ************************************************************************** */

// PreOrderTraversableContainer implementation

template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun fun) const {
  PreOrderTraverse(fun);
}

template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const {
  TraverseFun traverseLambda = [&foldFun, &accumulator](const Data& data) {
    accumulator = foldFun(data, accumulator);
  };
  
  Traverse(traverseLambda);
  return accumulator;
}

/* ************************************************************************** */

// PostOrderTraversableContainer implementation

template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun fun) const {
  PostOrderTraverse(fun);
}

/* ************************************************************************** */

}