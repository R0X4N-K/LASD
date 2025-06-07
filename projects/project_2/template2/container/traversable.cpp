namespace lasd
{

  /* ************************************************************************** */

  // TraversableContainer implementation

  template <typename Data>
  bool TraversableContainer<Data>::Exists(const Data &data) const noexcept
  {

    bool exists = false;

    Traverse([&exists, &data](const Data &currentData)
             {
      if (currentData == data) {
        exists = true;  // Set flag to true if element is found
      } }); // Traverse entire container looking for the element

    return exists; // Return whether element was found
  }

  /* ************************************************************************** */

  // PreOrderTraversableContainer implementation

  template <typename Data>
  void PreOrderTraversableContainer<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun fun) const
  {
    PreOrderTraverse(fun); // Default traversal delegates to pre-order traversal
  }

  /* ************************************************************************** */

  // PostOrderTraversableContainer implementation

  template <typename Data>
  void PostOrderTraversableContainer<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun fun) const
  {
    PostOrderTraverse(fun); // Default traversal delegates to post-order traversal
  }

  /* ************************************************************************** */

  // Template functions implementation

  template <typename Data>
  template <typename Accumulator>
  Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const
  {
    Traverse([&accumulator, foldFun](const Data &data)
             {
               accumulator = foldFun(data, accumulator); // Apply fold function to each element, updating accumulator
             });

    return accumulator; // Return final accumulated value
  }

  template <typename Data>
  template <typename Accumulator>
  Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const
  {
    PreOrderTraverse([&accumulator, foldFun](const Data &data)
                     {
                       accumulator = foldFun(data, accumulator); // Apply fold function in pre-order, updating accumulator
                     });

    return accumulator; // Return final accumulated value
  }

  template <typename Data>
  template <typename Accumulator>
  Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFun, Accumulator accumulator) const
  {
    PostOrderTraverse([&accumulator, foldFun](const Data &data)
                      {
                        accumulator = foldFun(data, accumulator); // Apply fold function in post-order, updating accumulator
                      });

    return accumulator; // Return final accumulated value
  }

  /* ************************************************************************** */

}