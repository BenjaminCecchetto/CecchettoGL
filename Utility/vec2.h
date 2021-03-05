/*
 * vec2.h
 *
 *  Created on: Jul 3, 2014
 *      Author: root
 */

#ifndef CGL_VEC2_H_
#define CGL_VEC2_H_

#include <cmath>

namespace cgl {

class vec2 {
public:
    double x, y;
    vec2() :
            x(0), y(0) {
    }
    vec2(const vec2& v) : x(v.x), y(v.y) {}
    vec2 operator=(const vec2& v) { return vec2(v); }

    vec2(double a) :
            x(a), y(a) {
    }
    vec2(double _x, double _y) :
            x(_x), y(_y) {
    }

    vec2 operator-(const vec2& rhs) {
        return vec2(x - rhs.x, y - rhs.y);
    }
    vec2 operator+(const vec2& rhs) {
        return vec2(x + rhs.x, y + rhs.y);
    }
    vec2& operator+=(const vec2& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vec2& operator-=(const vec2& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    double dot(const vec2& rhs) {
        return x*rhs.x + y*rhs.y;
    }

    double length() {
        return sqrt(x*x + y*y);
    }

};

vec2 operator*(double lhs, const vec2& rhs);
vec2 operator*(const vec2& lhs, double rhs);

}

#endif /* VEC2_H_ */
