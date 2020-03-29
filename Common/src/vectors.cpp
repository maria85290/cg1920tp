#include "Common/vectors.h"

#define _USE_MATH_DEFINES
#include <math.h>

double norm(vec3 v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

vec3 normalize(vec3 v) {
    double vnorm = norm(v);

    return {v.x / vnorm, v.y / vnorm, v.z / vnorm};
}

vec3 cross(vec3 a, vec3 b) {
    return {
        a.y * b.z - a.z * b.y,
        a.x * b.z - a.z * b.x,
        a.x * b.y - a.y * b.x
    };
}

vec3 scale(vec3 v, double factor) {
    return {v.x * factor, v.y * factor, v.z * factor};
}
