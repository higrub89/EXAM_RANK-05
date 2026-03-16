#pragma once

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag
{
    private:
        bool has_recursive(node* current, const int item) const;
    public:
        bool has(int item) const;
};