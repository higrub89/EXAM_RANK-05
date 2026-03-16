#include "set.hpp"
#include <iostream>

set::set(searchable_bag& b) : bag(&b) {}

set::set() : bag(NULL) {}

set& set::operator=(const set& other) {
    if (this != &other)
    {
        bag = other.bag;
    }
    return *this;
}

set::~set() {}

void set::insert(int item) {
    if (!bag->has(item)) {
        bag->insert(item);
    }   
}

void set::insert(int* items, int count) {
    for (int i = 0; i < count; i++) {
        if (!bag->has(items[i])) {
            bag->insert(items[i]);
        }
    }
}

void set::print() const {
    if (bag) {
        bag->print();
    }
}

void set::clear() {
    if (bag) {
        bag->clear();
    }
}

bool set::has(int item) const {
    if (bag) {
        return bag->has(item);
    }
    return false;
}

searchable_bag& set::get_bag() {
    return *bag;
}

const searchable_bag& set::get_bag() const {
    return *bag;
}