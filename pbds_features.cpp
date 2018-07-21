#include <ext/pb_ds/assoc_container.hpp> // Общий файл. 
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

/* first: tree */

using superset = tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

superset s;
s.insert(1);
s.insert(2);
s.insert(4);
s.insert(8);
s.insert(16);

cout << *s.find_by_order(1) << endl; // 2
cout << *s.find_by_order(2) << endl; // 4
cout << *s.find_by_order(4) << endl; // 16
cout << (end(s) == s.find_by_order(6)) << endl; // true

cout << s.order_of_key(-5) <<endl;  // 0
cout << s.order_of_key(1) <<endl;   // 0
cout << s.order_of_key(3) <<endl;   // 2
cout << s.order_of_key(4) <<endl;   // 2
cout << s.order_of_key(400) <<endl; // 5
    
/* second: hash_table */

gp_hash_table<int, int> table;

// usage seems not to be different to unordered_map
