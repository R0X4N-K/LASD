
#include "dictionary.hpp"
#include "traversable.hpp"
namespace lasd {
    template <typename Data>
    
    inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> & con) {
        bool all = true;
        con.Traverse (
            [this, &all] (const Data & dat) {
                all &= Insert(dat);
            }
        );
        return all;
    } 
}
