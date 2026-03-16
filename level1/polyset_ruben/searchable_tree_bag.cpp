#include "searchable_tree_bag.hpp"
#include <algorithm>

bool searchable_tree_bag::has(int item) const {
    return has_recursive(tree, item);
}

bool searchable_tree_bag::has_recursive(node* current, int item) const {
    if (current == NULL){
        return false;
    }
    if (item == current->value) {
        return true;
    } 
    if (item < current->value) {
        return has_recursive(current->l, item);
    }else {
        return has_recursive(current->r, item);
    }
}