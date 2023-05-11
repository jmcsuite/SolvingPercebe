#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

using map_t = tree<ll,null_type,
      less<ll>, rb_tree_tag,
      tree_order_statistics_node_update>;

// No inserta duplicados. 
// tiene mismas funciones que set o map (dependiendo de que uses);

int main(){
    map_t mp;
    mp.insert(3);
    mp.insert(5);
    mp.order_of_key(4); // devolveria 1
    mp.find_by_order(2); // devolveria el iterador al 5 (es un puntero);
}

