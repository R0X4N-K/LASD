namespace lasd {

/* ************************************************************************** */

// PreOrderMappableContainer implementation

template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

/* ************************************************************************** */

// PostOrderMappableContainer implementation

template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFun fun) {
  PostOrderMap(fun);
}

/* ************************************************************************** */

}