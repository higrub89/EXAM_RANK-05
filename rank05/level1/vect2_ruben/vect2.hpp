#ifndef VECT2_HPP
# define VECT2_HPP

# include <iostream>

class vect2 {
    private:
        int _x;
        int _y;
    
    public:
        vect2(int x = 0, int y = 0) : _x(x), _y(y) {}
        vect2(const vect2& src) : _x(src._x), _y(src._y) {}
        ~vect2() {}

        vect2& operator=(const vect2& rhs);
        int& operator[](int index);
        const int& operator[](int index) const;

        vect2 operator-() const;
        vect2& operator++();
        vect2 operator++(int);
        vect2& operator--();
        vect2 operator--(int);

        vect2& operator+=(const vect2& rhs);
        vect2& operator-=(const vect2& rhs);
        vect2& operator*=(int scalar);

        bool operator==(const vect2& rhs) const;
        bool operator!=(const vect2& rhs) const;

        int getX() const {return _x;}
        int getY() const {return _y;}
};

vect2 operator+(vect2 lhs, const vect2& rhs);
vect2 operator-(vect2 lhs, const vect2& rhs);
vect2 operator*(vect2 lhs, int scalar);
vect2 operator*(int scalar, vect2 rhs);

std::ostream& operator<<(std::ostream& os, const vect2& v);

#endif