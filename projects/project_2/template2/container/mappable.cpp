namespace lasd
{

  /* ************************************************************************** */

  // PreOrderMappableContainer implementation

  template <typename Data>
  void PreOrderMappableContainer<Data>::Map(MapFun fun)
  {
    PreOrderMap(fun); // Default Map implementation delegates to PreOrderMap
  }

  /* ************************************************************************** */

  // PostOrderMappableContainer implementation

  template <typename Data>
  void PostOrderMappableContainer<Data>::Map(MapFun fun)
  {
    PostOrderMap(fun); // Default Map implementation delegates to PostOrderMap
  }

  /* ************************************************************************** */

}