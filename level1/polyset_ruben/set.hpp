#pragma once

#include "searchable_bag.hpp"

class set {
    private:
        searchable_bag* bag;
    public:
        explicit set(searchable_bag& b);

        set();
        set(const set& other);
        set& operator=(const set& other);
        ~set();

        void insert(int item);
        void insert(int* items, int count);
        void print() const;
        void clear();

        bool has(int item) const;

        searchable_bag& get_bag();
        const searchable_bag& get_bag() const;
};