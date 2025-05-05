
#include "traversable.hpp"
namespace lasd {

    template <typename Data>
    template <typename Accumulator>
    inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const{
        Traverse(
            fun &acc(const Data & dat){
                acc = fun (dat, acc);
            }
        );
        return acc;
    }




    
}
