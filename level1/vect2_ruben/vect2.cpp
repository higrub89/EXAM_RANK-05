#include "vect2.hpp"

vect2& vect2::operator=(const vect2& rhs) {
    if (this != &rhs)
    {
        _x = rhs._x;
        _y = rhs._y;
    }
    return *this;
}

 int& vect2::operator[](int i) {
    if (i == 0)
        return _x;
    return _y;
}

const int& vect2::operator[](int i) const  {
    if (i == 0)
        return _x;
    return _y;
}


vect2 vect2::operator-() const {
    return vect2(-_x, -_y);
}

vect2& vect2::operator++() {
    _x++;
    _y++;
    return *this;
}

vect2 vect2::operator++(int) {
    vect2 tmp(*this);
    ++(*this);
    return tmp;
}

vect2& vect2::operator--() {
    return *this -= vect2(1, 1);
}

vect2 vect2::operator--(int) {
    vect2 tmp(*this);
    --(*this);
    return tmp;
}

vect2& vect2::operator+=(const vect2& rhs) {
    _x += rhs._x;
    _y += rhs._y;
    return *this;
}

vect2& vect2::operator-=(const vect2& rhs) {
    _x -= rhs._x;
    _y -= rhs._y;
    return *this;
}

vect2& vect2::operator*=(int s) {
    _x *= s;
    _y *= s;
    return *this;
}

bool vect2::operator==(const vect2& rhs) const {
    return _x == rhs._x && _y == rhs._y;
}

bool vect2::operator!=(const vect2& rhs) const {
    return !(*this == rhs);
}

vect2 operator+(vect2 lhs, const vect2& rhs) {
    return lhs += rhs;
}

vect2 operator-(vect2 lhs, const vect2& rhs) {
    return lhs -= rhs;
}

vect2 operator*(vect2 lhs, int scalar) {
    return lhs *= scalar;
}

vect2 operator*(int scalar, vect2 rhs) {
    return rhs *= scalar;
}

std::ostream& operator<<(std::ostream& os, const vect2& v) {
     os << "{" << v[0] << ", " << v[1] << "}";
     return os;
}

